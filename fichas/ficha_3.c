#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1 - MIN-HEAPS

#define Max 100
#define left(i) (2*i+1)
#define right(i) (2*i+2)
#define pai(i) ((i - 1)/2)

void swap(int h[],int i,int m){
    int temp = h[m];
    h[m] = h[i];
    h[i] = temp;
}

//2.
void bubbleUp (int i, int h[]){
    int m;
    while (i > 0 && h[i] < h[pai(i)]){
        swap(h,i,pai(i));
        i = pai(i);
    }
}

//3.
void bubbleDown (int i, int h[], int N){
    int m;
    while (left(i) < N){
        m = left(i);
        if ((h[right(i)] < h[i]) && (h[right(i)] < h[left(i)])){
            m = right(i);
        }
        if (h[m] > h[i]) break;
        swap(h,i,m);
        i = m;
    }
}

void printmh(int minheap[]){
    int j = 0;
    while (minheap[j] != -1){
        printf("%d ", minheap[j]);
        j++;
    }
}

typedef struct pQueue {
    int valores [Max];
    int tamanho;
} PriorityQueue;

//4.

void empty (PriorityQueue *q){
    q->tamanho = 0;
}

int isEmpty (PriorityQueue *q){
    return (q->tamanho == 0);
}

int add (int x, PriorityQueue *q){
    if (q->tamanho == Max) return 1;
    q->valores[q->tamanho] = x;
    bubbleUp(q->tamanho,q->valores);
    (q->tamanho)++;
    return 0;
}

int remv (PriorityQueue *q, int *rem){
    if (isEmpty(q)) return 1;
    *rem = q->valores[0];
    (q->tamanho)--;
    int temp = q->valores[q->tamanho];
    q->valores[0] = temp;
    bubbleDown(0,q->valores,q->tamanho);
    return 0;
}
//5.
void heapSort(PriorityQueue *q, int N){  

}


//2 - TABELAS DE HASH


unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

//2.1 - CHAINING

#define Size 100
typedef struct nodo {
    char *chave; int ocorr;
    struct nodo *prox;
} Nodo, *THash [Size];

//1.
void initEmpty (THash t){
    for(int i = 0; i < Size; i++) t[i] = NULL;
}

//2.
void addH1 (char *s, THash t){
    int h = hash(s) % Size;
    Nodo *temp = t[h];
    while (temp && strcmp(s,temp->chave)){
        temp = temp->prox;
    }
    if (temp) temp->ocorr++;
    else {
        temp = malloc(sizeof(Nodo));
        temp->chave = s;
        temp->ocorr = 1;
        temp->prox = t[h];
        t[h] = temp;
    }
}

//3.
int lookup (char *s, THash t){
    int h = hash(s) % Size;
    Nodo *temp = t[h];
    while(temp && strcmp(s,temp->chave)){
        temp = temp->prox;
    }
    if (!temp) return 0;
    else return temp->ocorr;
}

//4.
int removeH1 (char *s, THash t){
    int h = hash(s) % Size;
    Nodo *temp = t[h], *ant = NULL;
    while (temp && strcmp(s,temp->chave)){
        ant = temp;
        temp = temp->prox;
    }
    if (!temp) return 1;
    else{
        if (temp->ocorr > 1) return temp->ocorr--;
        else {
            if(ant) ant->prox = temp->prox;
            else t[h] = temp->prox;
            free(temp);
        }
    }
    return 0;
}


//2.2 - OPEN ADDRESSING

#define Size 100
#define Free 0
#define Used 1
#define Del 2
typedef struct bucket {
    int status; // Free | Used | Del
    char *chave; int ocorr;
} THash [Size];

//1.

int where (char *s, THash t){
    int h = hash(s) % Size;
    int i = 0;
    int del = -1;
    while((i < Size) && ((t[h].status == 1 && strcmp(s,t[h].chave)) || t[h].status == 2)){
        if (t[h].status == 2) del = h;
        h = (h + 1) % Size;i++;
    }
    if (t[h].status == 1) return h;
    else {
        if (del >= 0) return del;
        else return h;
    }
}

void initEmpty (THash t){
    for(int i = 0; i < Size; i++){
        t[i].status == 0;
    }
}

int addH (char *s, THash t){
    int h = where(s,t);
    if (t[h].status == 1 && !strcmp(s,t[h].chave)) {t[h].ocorr++;return 0;}
    if (t[h].status == 1) return 1;
    t[h].status = 1;
    t[h].ocorr = 1;
    t[h].chave = strdup(s);
return 0;
}

int lookup (char *s, THash t){
    int h = where(s,t);
    if (t[h].status == 1 && strcmp(s,t[h].chave)) return 0;
    return t[h].ocorr;
}

int removeH (char *s, THash t){
    int h = where(s,t);
    if (t[h].status == 1 && strcmp(s,t[h].chave)) return 1;
    t[h].status = 2;
    return 0;
}


// MAIN -------------------------------------------------------

int main(){

    int minheap[Max];
    int i = 0;
    int x;
    while (x != -1){
        printf("input:");
        scanf("%d",&x);
        minheap[i] = x;
        i++;
    }

    /*----------TESTE BUBBLEUP-----------
    minheap[i - 1] = 13;
    minheap[i] = -1;
    i++;
    bubbleUp(i-2,minheap);
    */
    /*----------TESTE BUBBLEDOWN----------
    bubbleDown(2,minheap,17);
    */
    /*----------TESTE ADD---------------
    PriorityQueue heap;
    heap.tamanho = 17;
    for(int f = 0; f < heap.tamanho; f++) heap.valores[f] = minheap[f];
    heap.valores[heap.tamanho + 1] = -1;
    add(12,&heap);
    */
    /*----------TESTE REMOVE------------
    PriorityQueue heap;
    heap.tamanho = 17;
    for(int f = 0; f < heap.tamanho; f++) heap.valores[f] = minheap[f];
    heap.valores[heap.tamanho] = -1;
    int r;
    remv(&heap, &r);
     */
    /*----------TESTE HEAPSORT------------

    */
}
