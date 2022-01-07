#include <stdio.h>
#include <stdlib.h>

#define NV 4
typedef struct aresta {
    int dest; int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];
typedef int GrafoM [NV][NV];

void printM (GrafoM g){
    int i,j;
    long value;
    for(i = 0; i < NV; i++){
        printf("%d -> ",i + 1);
        for(j = 0; j < NV;j++){
            value = g[i][j];
            printf("%ld ",value);
        }
        printf("\n");
    }
}

void printL(GrafoL g){
    LAdj aux;
    for(int i = 0; i < NV; i++){
        printf("%d -> ",i + 1);
        aux = g[i];
        while(aux){
            printf("%d ",aux->dest);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void fromMat (GrafoM in, GrafoL out){
    LAdj aux;
    for(int i = NV - 1;i >= 0; i--){
        out[i] = NULL;
        for(int j = NV - 1;j >= 0; j--){
            if (in[i][j] != 0) {
                aux = malloc(sizeof(struct aresta));
                aux->custo = 1;
                aux->dest = in[i][j];
                aux->prox = out[i];
                out[i] = aux;
            }
        }
    }
}

void inverte (GrafoL in, GrafoL out){
    LAdj aux,new;
    for(int o = 0; o < NV; o++){
        out[o] = NULL;
    }
    for(int i = 0;i < NV; i++){
        aux = in[i];
        while (aux){
            new = malloc(sizeof(struct aresta));
            new->dest = i + 1;
            new->custo = 1;
            new->prox = out[aux->dest - 1];
            out[aux->dest - 1] = new;
            aux = aux->prox;
        }
    }
}

int inDegree (GrafoL g) {
    LAdj aux;
    int m[NV+1],maior = 0;
    for (int j = 0; j < NV+1; j++) {
        m[j] = 0;
    }
    for (int i = 0; i < NV; i++) {
        aux = g[i];
        while (aux) {
            m[aux->dest]++;
            aux = aux->prox;
        }
    }
    for(int n = 1; n < NV + 1; n++){
        if (m[n] > maior) maior = m[n];
    }
return maior;
}

int main() {
    GrafoM grafom[NV][NV] = {2,0,0,0,
                             3,4,0,0,
                             4,0,0,0,
                             1,0,0,0};
    GrafoL grafol[NV];
    GrafoL grafol2[NV];
    fromMat(**grafom, *grafol);
    printL(*grafol);
    inverte(*grafol,*grafol2);
    printf("\n");
    printf("degree : %d",inDegree(*grafol));
    return 0;
}
