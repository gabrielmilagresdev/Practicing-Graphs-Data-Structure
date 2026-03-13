#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Bool;

//Struct da lista de adjacência
typedef struct s{
    int adj;
    struct s* prox;
}No;

typedef struct{
    No* inicio;
    int flag;
}VERTICE;

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
Bool adicionarAresta(VERTICE* g, int v1, int v2){
    if(arestaExiste(g, v1, v2))
        return FALSE;
    No* novo = (No*) malloc(sizeof(No));
    novo->adj = v2;
    novo->prox = g[v1].inicio;
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

int main(){
    int v = 8;
    VERTICE* g = (VERTICE*) malloc(v * sizeof(VERTICE));
    VERTICE* gt = (VERTICE*)malloc(v * sizeof(VERTICE));

    inicializarGrafo(g, v);
    //adicionarAresta(g, x, y);
    //removerAresta(g, x, y);
    //imprimirGrafo(g, v);

    adicionarAresta(g, 0 , 1);
    adicionarAresta(g, 0 , 3);
    adicionarAresta(g, 1 , 3);
    adicionarAresta(g, 2 , 3);
    adicionarAresta(g, 2 , 1);
    adicionarAresta(g, 2 , 7);
    adicionarAresta(g, 3 , 4);
    adicionarAresta(g, 4 , 2);
    adicionarAresta(g, 5 , 6);
    adicionarAresta(g, 6 , 5);

    imprimirGrafo(g, v);

    printf("\n\n");

    //gt = grafoTransposto(g, v);
    //imprimirGrafo(gt,v);

    /*
    int** m = (int**) malloc(v * sizeof(int*));
    for(int i = 0; i < v; i++){
        m[i] = (int*) malloc (v *sizeof(int));
    }
    m = listaParaMatriz(g,v);
    imprimirGrafoM(m,v);
    */
   zerarFlags(g,v);
   prof(g,v,0);
   imprimirFlags(g,v);
   

    return 0;
}


