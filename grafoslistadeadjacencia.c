#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef bool int;


//Struct das arestas
typedef struct s{
    int adj;
    struct s* prox;
}No;

//Struct do vértice
typedef struct{
    No* inicio;
}VERTICE; 

//Função para inicializar o grafo
void inicializar(VERTICE* g, int v){
    for(int i = 0; i < v; i++) 
        g[i].inicio = NULL; //Aponta para nulo todos os vértices
}

//Função para verificar se uma relação entre dois vértices existe
bool arestaExiste(VERTICE *g, int v1, int v2){
    No* p = g[v1].inicio; //Parte do vértice inicial
    while(p){ //Itera pelos adjacentes
        if(p->adj == v2) //Se um adjacente do vértice v1 for o v2, então eles são adjacentes
            return TRUE;
        p = p->prox; //Passa para o próximo vértice
    }
    return FALSE;
}

bool inserirAresta(VERTICE* g, int v1, int v2){

}
int main(){
    int v; //Número de vértices do grafo
    scanf("%d", &v);

    VERTICE *g = (VERTICE*) malloc(v*sizeof(VERTICE)); //Alocando o grafo
    inicializar(g, v);
    return 0;
}