#include <stdio.h>

//Questão 1
/*
 * BU -> BubbleUp
 * BD -> BubbleDown
 [30]
 [30,20] -> BU -> [20,30]
 [20,30,10,-] -> BU -> [10,20,30,-]
 [10,20,30,100]
 [10,20,30,100,90,-,-,-]
 [10,20,30,100,90,80,-,-]
 [80,20,30,100,90,-,-,-] -> BD -> [20,30,80,100,90,-,-,-]
 [90,30,80,100,-,-,-,-] -> BD -> [30,90,80,100,-,-,-,-]
 [30,90,80,100,40,-,-,-] -> BU -> [30,40,80,100,90,-,-,-]
 [30,90,80,100,40,50,-,-] -> BU -> [30,40,50,100,90,80,-,-]
 [30,40,50,100,90,80,60,-]
 [30,40,50,100,90,80,60,20] -> BU -> [20,30,50,40,90,80,60,100]
 [20,30,50,40,90,80,60,100,10,-,-,-,-,-,-,-] -> BU -> [10,20,50,30,90,80,60,100,40,-,-,-,-,-,-,-]
 [40,20,50,30,90,80,60,100,-,-,-,-,-,-,-,-] -> BD -> [20,30,50,40,90,80,60,100,-,-,-,-,-,-,-,-]
 [100,30,50,40,90,80,60,-,-,-,-,-,-,-,-,-] -> BD -> [30,40,50,100,90,80,60,-,-,-,-,-,-,-,-,-]
 */

//Questão 3
/*
Tabela de hash
 Inserção: 1
 Teste: 1
 Rank: N

 ou

Array Ordenado
 Inserção: Melhor caso - 1
           Pior caso - N
 Teste: Melhor caso - 1
        Pior caso - log(N)
 Rank: Melhor caso - 1
       Pior caso - log(N)
*/


typedef int WEIGHT;

#define MAX 10
#define NE -1

typedef WEIGHT GraphM[MAX][MAX];

struct edge {
    int dest;
    WEIGHT weight;
    struct edge *next;
};

typedef struct edge *GraphL[MAX];

//Questão 4

int pesoC (GraphM g, int v[], int k){
    int pesot = 0,a,b;
    for(int i = 0; i < k - 1;i++){
        a = v[i];
        b = v[i+1];
        if (g[a][b] != -1) pesot+=g[a][b];
        else return -1;
    }
    return pesot;
}

//Questão 5

void DF(GraphL g,int comp[],int noc,int orig){
    struct edge *aux;
    comp[orig] = noc;
    for(aux = g[orig]; aux; aux = aux->next)
        if(comp[aux->dest] == -1) DF(g,comp,noc,aux->dest);
}

void componentes(GraphL g, int comp[]){
    int noc = 0;
    for(int j = 0; j < MAX; j++){
        comp[j] = -1;
    }
    for(int i = 0; i < MAX; i++){
        if (comp[i] == -1){
            DF(g,comp,noc,i);
            noc++;
        }
    }
}
