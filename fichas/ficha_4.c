#include <stdio.h>
#include <stdlib.h>

#define NV 7
typedef struct aresta {
    int dest; int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];
typedef int GrafoM [NV][NV];

void printM (GrafoM g){
    int i,j;
    long value;
    for(i = 0; i < NV; i++){
        printf("%d -> ",i);
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
        printf("%d -> ",i);
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
            if (in[i][j] != -1) {
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
            new->prox = out[aux->dest];
            out[aux->dest] = new;
            aux = aux->prox;
        }
    }
}

int inDegree (GrafoL g) {
    LAdj aux;
    int m[NV+1],maior = 0;
    for (int j = 0; j < NV; j++) {
        m[j] = 0;
    }
    for (int i = 0; i < NV; i++) {
        aux = g[i];
        while (aux) {
            m[aux->dest]++;
            aux = aux->prox;
        }
    }
    for(int n = 0; n < NV; n++){
        if (m[n] > maior) maior = m[n];
    }
return maior;
}

int colorOK (GrafoL g, int cor[]){
    LAdj aux;
    for(int i = 0; i < NV; i++){
        aux = g[i];
        while(aux){
            if (cor[(aux->dest)] == cor[i]) return -1;
            aux = aux->prox;
        }
    }
    return 0;
}

int homomorfOK (GrafoL g, GrafoL h, int f[]){
    LAdj aux;
    LAdj aux2;
    for(int i = 0; i < NV; i++){
        while (aux && aux2){
            if (f[aux->dest] != f[aux2->dest]) return -1;
            aux = aux->prox;
            aux2 = aux2->prox;
        }
    }
    return 0;
}

//TRAVESSIAS-------------------------------------------------------------------

int DFRec (GrafoL g, int or,int v[],int p[],int l[]){
    int i; LAdj aux;
    i=1;
    v[or]=-1;
    for (aux=g[or];aux!=NULL;aux=aux->prox)
        if (!v[aux->dest]){
            p[aux->dest] = or;
            l[aux->dest] = 1+l[or];
            i+=DFRec(g,aux->dest,v,p,l);
        }
    v[or]=1;
    return i;
}

int DF (GrafoL g, int or,int v[],int p[],int l[]){
    int i;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    p[or] = -1; l[or] = 0;
    return DFRec (g,or,v,p,l);
}

int BF (GrafoL g, int or,int v[],int p[],int l[]){
    int i, x; LAdj a;
    int q[NV], front, end;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    front = end = 0;
    q[end] = or; //enqueue
    end++;
    v[or] = 1; p[or]=-1;l[or]=0;
    i=1;
    while (front != end){
        x = q[front]; //dequeue
        front++;
        for (a=g[x]; a!=NULL; a=a->prox)
            if (!v[a->dest]){
                i++;
                v[a->dest]=1;
                p[a->dest]=x;
                l[a->dest]=1+l[x];
                q[end]=a->dest; //enqueue
                end++;
            }
    }
    return i;
}

int maisLonga (GrafoL g, int or, int p[]){
    int v[NV],l[NV],pai[NV],i,j = 0;
    int m = BF(g,or,v,pai,l);
    for(i = 0; i < NV; i++){
        if (l[i] > l[j]) j = i;
    }
    i = j;
    p[l[j]] = j;
    for(int aux = l[j] - 1 ; pai[j] != -1; aux--){
        p[aux] = pai[j];
        j = pai[j];
    }
return i;
}

int componentes (GrafoL g, int c[]){
    int v[NV],l[NV],pai[NV],count, o = 0;
    BF(g,o,c,pai,l);
    count = 1;
    while (o < NV) {
        for (o = 0; o < NV && c[o] != 0; o++)
            ;
        if (o < NV) {
            BF(g,o,v,pai,l);
            count++;
            for(int i = 0; i < NV;i++){
                if (v[i]) c[i] = count;
            }
        }
    }
return count;
}

int ordTop (GrafoL g, int ord[]){
int vis[NV], pai[NV], l[NV],or = 0,count = 1,bk;
LAdj aux;
BF(g,or,vis,pai,l);
for(int i = 0; i < NV ;i++){
    if (pai[i] == -1) {
        ord[0] = i;
        pai[i] = -2;
    }
}
for(int m = 1; m < NV; m++){
    bk = 1;
    for(int n = 0;n < NV && bk ;n++){
        if ((pai[pai[n]]) == -2){
            pai[n] = -2;
            ord[m] = n;
            bk = 0;
        }
    }
}
return 0;
}

int main() {
    GrafoM grafom[NV][NV] = {1,-1,-1,-1,-1,-1,-1,
                             2,-1,-1,-1,-1,-1,-1,
                             3,-1,-1,-1,-1,-1,-1,
                             4,-1,-1,-1,-1,-1,-1,
                             5,-1,-1,-1,-1,-1,-1,
                             6,-1,-1,-1,-1,-1,-1,
                             -1,-1,-1,-1,-1,-1,-1};
    GrafoL grafol[NV];
    GrafoL grafol2[NV];
    int cor[NV] = {1,1,1,3};
    int p[NV];
    for(int i = 0; i < NV; i++){
        p[i] = -1;
    }
    fromMat(**grafom, *grafol);
    printL(*grafol);
    printf("\n");
    ordTop(*grafol,p);
    printf("[");
    for(int i = 0; i < NV && p[i] != -1; i++){
        printf("%d,",p[i]);
    }
    printf("]");
    return 0;
}
