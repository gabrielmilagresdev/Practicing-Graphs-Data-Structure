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
}VERTICE;

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


int main(){
    //Tamanho da matriz quadrada
    int v = 5;

    //Alocando a matriz
    int** m = (int**) malloc(v * sizeof(int*));
    for(int i = 0; i < v; i++){
        m[i] = (int*) malloc(v* sizeof(int));
    }

    inicializar(m,v);
    inserirAresta(m,v,1,3);
    inserirAresta(m,v,0,1);
    inserirAresta(m,v,2,2);
    inserirAresta(m,v,3,2);
    imprimirGrafo(m,v);

    /*
    VERTICE* g = (VERTICE*) malloc(v * sizeof(VERTICE));
    for(int i = 0; i < v; i++)
        g[i].inicio = NULL;

    g = matrizParaLista(m,v);
    imprimirGrafoLA(g,v);
    */

}