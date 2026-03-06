#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Bool;

typedef struct s{
    int adj;
    struct s* prox;
}No;

typedef struct{
    No* inicio;
}VERTICE;

void inicializarGrafo(VERTICE* g, int v){
    for(int i = 0; i < v; i++)
        g[i].inicio = NULL;
}

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

Bool adicionarAresta(VERTICE* g, int v1, int v2){
    if(arestaExiste(g, v1, v2))
        return FALSE;
    No* novo = (No*) malloc(sizeof(No));
    novo->adj = v2;
    novo->prox = g[v1].inicio;
    g[v1].inicio = novo;

    return TRUE;
}

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

int main(){
    int v;
    scanf("%d",&v);
    VERTICE* g = (VERTICE*) malloc(v * sizeof(VERTICE));
    VERTICE* gt = (VERTICE*)malloc(v * sizeof(VERTICE));

    inicializarGrafo(g, v);
    //adicionarAresta(g, x, y);
    //removerAresta(g, x, y);
    //imprimirGrafo(g, v);

    adicionarAresta(g, 0 , 3);
    adicionarAresta(g, 0 , 2);
    adicionarAresta(g, 0 , 1);
    adicionarAresta(g, 1 , 1);
    adicionarAresta(g, 1 , 2);
    adicionarAresta(g, 1 , 3);
    adicionarAresta(g, 2 , 0);
    adicionarAresta(g, 3 , 1);
    adicionarAresta(g, 3 , 0);

    imprimirGrafo(g, v);

    printf("\n\n");

    gt = grafoTransposto(g, v);
    imprimirGrafo(gt,v);

    return 0;
}


