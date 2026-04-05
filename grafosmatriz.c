#include <stdio.h>
#include <stdlib.h>

typedef int Bool;

#define TRUE 1
#define FALSE 0

//Struct da lista de adjacência (Para a função de conversão entre as estruturas)
typedef struct s{
    int adj;
    struct s* prox;
}No;

typedef struct{
    No* inicio;
    int flag;
}VERTICE;

typedef struct{
    No* ini;
    No* fim; 
}FILA;

    
//Função para imprimir um grafo em lista de adjacência (Para a função de conversão entre as estruturas)
void imprimirGrafoLA(VERTICE *g, int v){
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

//Função para inicializar a matriz completamente zerada
void inicializar(int **m, int v){
    for(int i = 0; i < v; i++)
        for(int j = 0; j < v; j++)
            m[i][j] = 0;
}

//Função para imprimir o grafo em matriz
void imprimirGrafo(int **m, int v){
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

//Função para verificar se uma aresta existe
Bool arestaExiste(int **m, int v, int a, int b){
    if(a >= v || a < 0 || b>=v || b<0){
        printf("Posicao invalida\n");
        return FALSE;
    }
    if(m[a][b] == 1){
        printf("A aresta %d -> %d existe\n",a,b);
        return TRUE;
    }
    printf("A aresta %d -> %d nao existe\n",a,b);
    return FALSE;
}

//Função para inserir uma aresta
Bool inserirAresta(int **m, int v, int a, int b){
    if(a >= v || a < 0 || b>=v || b<0){
        printf("Posicao invalida\n");
        return FALSE;
    }
    m[a][b] = 1;
    /*
    Caso não dirigido
    m[a][b] = 1;
    m[b][a] = 1;
    */
    return TRUE;
}

//Função para remover uma aresta
Bool removerAresta(int **m, int v, int a, int b){
    if(!m || m[a][b] == 0)
        return FALSE;
    m[a][b] = 0;
    /*
    Caso não dirigido
    m[a][b] = 0;
    m[b][a] = 0;
    */
    return TRUE;
}

//Função para converter uma matriz em uma lista de adjacências
VERTICE* matrizParaLista(int **m, int v){
    if(!m)
        return NULL;

    //Inicializando a lista de adjacência
    VERTICE* g = (VERTICE*) malloc(v * sizeof(VERTICE));
    for(int i = 0; i < v; i++)
        g[i].inicio = NULL;

    //Iterando pela matriz e fazendo a cópia para a matriz de adjacência
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            if(m[i][j] == 1){
                No* novo = (No*) malloc(sizeof(No));
                novo->adj = j;
                novo->prox = g[i].inicio;
                g[i].inicio = novo;
            }    
        }
    }
    return g;
}

//Função para zerar as flags antes da busca em profundidade
void zerarFlags(int* vetorFlags, int v){
    if(!vetorFlags)
        return;
    for(int i = 0; i < v; i++){
        vetorFlags[i] = 0;
    }
}

//Função para imprimir as flags 
void imprimirFlags(int* vetorFlags, int v){
    if(!vetorFlags)
        return;
    for(int i = 0; i < v; i++){
        printf("G[%d] : %d\n",i,vetorFlags[i]);
    }
}

//Função para fazer uma busca em profundidade em um grafo em matriz a partir de um vértice "a"
Bool prof(int**m, int v, int a, int* vetorFlags){
    if(!m || !vetorFlags || vetorFlags[a] != 0)
        return FALSE;
    vetorFlags[a] = 1;
    for(int i = 0; i < v; i++){
        if(m[a][i] != 0 && vetorFlags[i] == 0)
            prof(m,v,i,vetorFlags);
    }
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
int sairFila(FILA* f){
    if(!f || f->ini == NULL)
        return;

    No* p = f->ini;
    f->ini = p->prox;

    if(f->ini == NULL) //Fila ficou vazia
        f->fim = NULL;

    int valor = f->ini->adj;

    free(p);

    return valor;
}

//Busca em largura em matriz
Bool largura(int** m, int v, int i){
    if(!m)
        return FALSE;

    int* vetorFlags = (int*)malloc(sizeof(vetorFlags));
    zerarFlags(vetorFlags, v);

    FILA* f = (FILA*)malloc(sizeof(FILA));
    inicializar(f);

    vetorFlags[i] = 1;
    entrarFila(f,i);

    while(f->ini){
        int j = sairFila(f);

        for(int w = 0; w < v; w++){
            if(m[j][w] == 1 && vetorFlags[w] == 0){
                vetorFlags[w] = 1;
                entrarFila(f,w);
            }
        }
        vetorFlags[j] = 2;
    }
}

//Ex4: Qual o custo do caminho mais curto de i para os demais vértices? (PRECISA DE AJUSTES)
void custo(int** m, int v, int i, int* custos){
    for(int j = 0; j < v; j++){
        if(j == i)
            custos[j] = 0
        else
            custos[j] = INFINITY;
    }

    int* flag = (int*) malloc(v * sizeof(int));
    FILA* f = (FILA*) malloc(sizeof(Fila));
    inicializarFila(f);
    zerarFlags(flag, v);

    flag[i] = 1;

    while(f->ini){
        int j = sairFila(f);

        for(int w = 0; w < v; w++){
            if(flag[j] == 0 && m[j][w] > 0){
                flag[j] = 1;
                custos[w] = custos[j] + m[j][w]; 
            }
        }
        flag[j] = 2;
    }
}

int main(){
    //Tamanho da matriz quadrada
    int v = 8;

    //Alocando a matriz
    int** m = (int**) malloc(v * sizeof(int*));
    for(int i = 0; i < v; i++){
        m[i] = (int*) malloc(v* sizeof(int));
    }

    inicializar(m,v);
    inserirAresta(m,v, 0 , 1);
    inserirAresta(m,v, 0 , 3);
    inserirAresta(m,v, 1 , 3);
    inserirAresta(m,v, 2 , 3);
    inserirAresta(m,v, 2 , 1);
    inserirAresta(m,v, 2 , 7);
    inserirAresta(m,v, 3 , 4);
    inserirAresta(m,v, 4 , 2);
    inserirAresta(m,v, 5 , 6);
    inserirAresta(m,v, 6 , 5);

    /*
    VERTICE* g = (VERTICE*) malloc(v * sizeof(VERTICE));
    for(int i = 0; i < v; i++)
        g[i].inicio = NULL;

    g = matrizParaLista(m,v);
    imprimirGrafoLA(g,v);
    */
    int* vetorFlags = (int*) malloc(sizeof(int));
    zerarFlags(vetorFlags,v);
    prof(m,v,1,vetorFlags);
    imprimirFlags(vetorFlags,v);

}