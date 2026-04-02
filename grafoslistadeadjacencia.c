#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Bool;

//Struct da lista de adjacência
typedef struct s{
    int adj;
    struct s* prox;
    int companhia;
}No;

typedef struct{
    No* inicio;
    int flag;
}VERTICE;

typedef struct{
    No* inicio;
    int flag;
    int tipo;
}VERTICE_TIPO;

typedef struct{
    No* ini;
    No* fim; 
}FILA;

//Função para imprimir um grafo em matriz (Usada para a função de conversão)
void imprimirGrafoM(int **m, int v){
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

//Função para inicializar um grafo da maneira correta
void inicializarGrafo(VERTICE* g, int v){
    for(int i = 0; i < v; i++)
        g[i].inicio = NULL;
}

//Função para verificar a existência de uma aresta em um grafo
Bool arestaExiste(VERTICE* g, int v1, int v2){
    No* p = g[v1].inicio;
    while(p){
        if(p->adj == v2){
            free(p);
            return TRUE;
        }
        p = p->prox;
    }
    return FALSE;
}

//Função para adicionar arestas em um grafo
Bool adicionarAresta(VERTICE* g, int v1, int v2, int c){
    if(arestaExiste(g, v1, v2))
        return FALSE;
    No* novo = (No*) malloc(sizeof(No));
    novo->adj = v2;
    novo->prox = g[v1].inicio;
    novo->companhia = c;
    g[v1].inicio = novo;

    return TRUE;
}

//Função para remover arestas de um grafo
Bool removerAresta(VERTICE* g, int v1, int v2){
    No* p = g[v1].inicio;
    No* ant;
    if(p->adj == v2){
        g[v1].inicio = p->prox;
        free(p);
        return TRUE;
    }
    ant = p;
    p = p->prox;
    while(p){
        if(p->adj == v2){
            ant->prox = p->prox;
            free(p);
            return TRUE;
        }
        ant = p;
        p = p->prox;
    }
    return FALSE;
}

//Função para imprimir o grafo
void imprimirGrafo(VERTICE *g, int v){
    No* p;
    for(int i = 0; i < v; i++){
        printf("G[%d]: ", i);
        p = g[i].inicio;
        while(p){
            printf("%d -> ",p->adj);
            p = p->prox;
        }
        printf("\\");
        printf("\n");
    }
    free(p);
}

//Função para transpor um grafo
VERTICE* grafoTransposto(VERTICE* g, int v){
    VERTICE* gt = (VERTICE*)malloc(v * sizeof(VERTICE));
    inicializarGrafo(gt, v);

    for(int i = 0; i < v; i++){
        No* p = g[i].inicio;
        while(p){
            No* novo = (No*)malloc(sizeof(No));
            novo->adj = i;
            novo->prox = gt[p->adj].inicio;
            gt[p->adj].inicio = novo;

            p = p->prox;
        }   
    }
    return gt;
}

//Função para converter uma lista de adjacência em matriz
int** listaParaMatriz(VERTICE* g, int v){
    if(!g)
        return NULL;
    //Inicializando a matriz
    int** m = (int**) malloc(v * sizeof(int*));
    for(int i = 0; i < v; i++){
        m[i] = (int*) malloc (v *sizeof(int));
    }
    for(int i = 0; i < v; i++)
        for(int j = 0; j < v; j++)
            m[i][j] = 0;
    //Iterando pela lista e copiando os valores para a matriz
    for(int i = 0; i < v; i++){
        No* p;
        p = g[i].inicio;
        while(p){
            m[i][p->adj] = 1;
            p = p->prox;
        }
    }
    return m;
}


//Função para zerar as flags antes de uma busca em profundidade
Bool zerarFlags(VERTICE* g, int v){
    if(!g)
        return FALSE;
    for(int i = 0; i < v; i++){
        g[i].flag = 0;
    }
    return TRUE;
}

//Função para imprimir as flags de um grafo
void imprimirFlags(VERTICE* g, int v){
    for(int i = 0; i < v; i++){
        printf("G[%d]: %d", i,g[i].flag);
        printf("\n");
    }
}

//Problema: Encontre o maior grupo de elementos conectados em grafo não dirigido e retornar um de seus vértices

Bool profMaiorGrupo(VERTICE* g, int v, int a, int* cont){ 
    if(!g)
        return FALSE;

    g[a].flag = 1;

    No* p = g[a].inicio;

    while(p){  
        if(g[p->adj].flag == 0){
            profMaiorGrupo(g,v,p->adj, cont);
            (*cont)++;
        }
        p = p->prox;
    }
    g[a].flag = 2;
    return TRUE;
}

int verticeMaiorGrupo(VERTICE* g, int v){
    if(!g)
        return -1;

    int verticeMaiorGrupo = -1;
    int numGrupo = -1;
    int contadorVertices = 1;
    int maiorContadorVertice = -1;

    for(int i = 0; i < v; i++){
        if(g[i].flag == 0){
            numGrupo++;
            profMaiorGrupo(g,v,i,&contadorVertices);
            printf("Grupo %d: %d\n",numGrupo,contadorVertices);

            if(contadorVertices > maiorContadorVertice){
                verticeMaiorGrupo = i;
                maiorContadorVertice = contadorVertices;
            }


            contadorVertices = 1;
        }
    }

    return verticeMaiorGrupo;
}

//Função da busca em profundidade em listas de adjacência a partir de um vértice "a"
Bool prof(VERTICE* g, int v, int a){
    if(!g)
        return FALSE;
    g[a].flag = 1;
    No* p = g[a].inicio;
    while(p){
        if(g[p->adj].flag == 0)
            prof(g,v,p->adj);
        p = p->prox;
    }
    g[a].flag = 2;
    return TRUE;
}

//Problema: Verificar se existe uma rota de i até f usando apenas a companhia x
Bool existeRota(VERTICE* g, int v, int i, int f, int x, Bool* achou){
    if(!g)
        return FALSE;
    if((*achou))
        return TRUE;

    g[i].flag = 1;
    No* p = g[i].inicio;
    while(p){
        if(p->adj == f){
            (*achou) = TRUE;
            return TRUE;
        }
        if(g[p->adj].flag == 0 && p->companhia == x)
            existeRota(g,v,p->adj, f, x, achou);
        p = p->prox;
    }
    g[i].flag = 2;
    return TRUE;
}

//Problema: Verifique se há caminho de i até f passando por m
Bool profComBool(VERTICE* g, int v, int i, int f, Bool* achou){
    if(!g)
        return FALSE;
    No* p = g[i].inicio;
    g[i].flag = 1;

    while(p){
        if(p->adj == f)
            (*achou) = TRUE;
        if(*achou)
            break;    
        if(g[p->adj].flag == 0)
            profComBool(g,v,p->adj,f,achou);
        p = p->prox;
    }
    g[i].flag = 2;
    return *achou;
}


Bool caminhoCondicionado(VERTICE* g, int v, int i, int f, int m, Bool* achou){
    if(!g)
        return FALSE;
    
    *achou = profComBool(g,v,i,m,achou);

    if(*achou){
        zerarFlags(g,v);
        *achou = FALSE;
        *achou = profComBool(g,v,m,f,achou);
    }

    return *achou;
}

//Problema: Encontrar todos os vértices não alcançáveis a partir de i
//e liga-los a i com uma nova aresta

Bool novasArestas(VERTICE *g, int v, int i){
    if(!g)
        return FALSE;
    prof(g,v,i);


    for(int j = 0; j < v; j++){
        if(g[j].flag == 0){
            No* p = (No*) malloc(sizeof(No));
            p->adj = j;
            p->prox = g[i].inicio;
            g[i].inicio = p;
        }
    }
    return TRUE;
}

//Problema: A partir de i, exibir até N salas do tipo X
Bool exibirN(VERTICE_TIPO* g, int v, int i, int* N, int tipox){
    if(!g)
        return FALSE;

    if((*N) == 0)
        return TRUE;

    if(g[i].tipo == tipox){
        (*N) = (*N) - 1;
        printf("G[%d] ", i);
    }

    g[i].flag = 1;
    No* p = g[i].inicio;

    while(p){
        if((*N) == 0)
            return TRUE;

        if(g[p->adj].flag == 0)
            exibirN(g,v,p->adj,N,tipox);
        p = p->prox;
    }
    g[i].flag = 2;

    return TRUE;
}

//Função para inicializar a fila
Bool inicializarFila(FILA* f){
    if(!f)
        return FALSE;

    f->ini = NULL;
    f->fim = NULL;

    return TRUE;
}

//Função para entrar um valor na fila
Bool entrarFila(FILA* f, int i){
    if(!f)
        return FALSE;

    No* p = (No*) malloc(sizeof(No));
    p->prox = NULL;
    p->adj = i;

    if(f->fim == NULL){ //Fila vazia
        f->ini = p;
        f->fim = p;
    }else{
        f->fim->prox = p;
        f->fim = p;
    }

    return TRUE;
}

//Função para tirar um valor da fila
Bool sairFila(FILA* f){
    if(!f || f->ini == NULL)
        return FALSE;

    No* p = f->ini;
    f->ini = p->prox;

    if(f->ini == NULL) //Fila ficou vazia
        f->fim = NULL;

    free(p);

    return TRUE;
}

Bool largura(VERTICE* g, int v, int i){
    if(!g)
        return FALSE;

    zerarFlags(g,v);
    FILA* f;
    inicializarFila(f);

    g[i].flag = 1;
    entrarFila(f,i);

    No* p = g[i].inicio;

    while(f->ini){         
        if(p == NULL){
            sairFila(f);
            g[f->ini].flag = 2;
            p = g[f->ini].inicio;
        }

        if(g[p->adj].flag == 0){
            g[p->adj].flag = 1;
            entrarFila(f,p->adj);
        }
        p = p->prox;
    }

    return TRUE;
}

int main(){
    int v = 17;
    VERTICE* g = (VERTICE*) malloc(v * sizeof(VERTICE));

    inicializarGrafo(g, v);

    adicionarAresta(g, 1 , 6, 0);
    adicionarAresta(g, 1 , 8, 0);
    adicionarAresta(g, 1 , 4, 0);
    adicionarAresta(g, 1 , 5, 1);
    adicionarAresta(g, 2 , 3, 1);
    adicionarAresta(g, 4 , 2, 0);
    adicionarAresta(g, 4 , 3, 1);
    adicionarAresta(g, 6 , 7, 0);
    adicionarAresta(g, 6 , 8, 0);
    adicionarAresta(g, 7 , 11, 1);
    adicionarAresta(g, 8 , 1, 1);
    adicionarAresta(g, 8 , 10, 0);
    adicionarAresta(g, 8 , 9, 1);
    adicionarAresta(g, 9 , 16, 1);
    adicionarAresta(g, 10 , 11, 1);
    adicionarAresta(g, 11 , 10, 1);
    adicionarAresta(g, 11 , 12, 0);
    adicionarAresta(g, 12 , 13, 1);
    adicionarAresta(g, 12 , 14, 0);
    adicionarAresta(g, 14 , 15, 0);


    imprimirGrafo(g, v);

    printf("\n\n");
    zerarFlags(g,v);


    novasArestas(g,v,0);

    imprimirGrafo(g, v);


    return 0;
}


