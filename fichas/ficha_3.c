#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int folha(int h[], int i){
    while(h[left(i)] && h[right(i)]){
        i++;
    }
return i;
}

//2-----------------------------
void bubbleUp (int i, int h[]){
    while(h[pai(i)] > h[i] && h[pai(i)]){
        swap(h,i,pai(i));
        i = pai(i);
    }
}

//3-------------------------------------
void bubbleDown (int i, int h[], int N){
    while(left(i) < N){
        if (h[i] > h[left(i)] && h[left(i)] < h[right(i)]) {
            swap(h,i,left(i));
            i = left(i);
        }
        else if (h[i] > h[right(i)] && h[left(i)] > h[right(i)]){
            swap(h,i,right(i));
            i = right(i);
        }
        else break;
    }
}

void printmh(int minheap[],int N){
    int j = 0;
    while (j < N){
        printf("%d ", minheap[j]);
        j++;
    }
}

#define Max 100
typedef struct pQueue {
    int valores [Max];
    int tamanho;
} PriorityQueue;

//4---------------------------
void empty (PriorityQueue *q){
    q->tamanho = 0;
}

int isEmpty (PriorityQueue *q){
    return(!q->tamanho);
}

int add (int x, PriorityQueue *q){
    if (q->tamanho == Max) return 1;
    q->valores[q->tamanho] = x;
    bubbleUp(q->tamanho,q->valores);
    q->tamanho++;
    return 0;
}

int removepq (PriorityQueue *q, int *rem){
    if (!q->tamanho) return 1;
    *rem = q->valores[0];
    q->valores[0] = q->valores[q->tamanho - 1];
    q->tamanho--;
    bubbleDown(0,q->valores,q->tamanho);
    return 0;
}

//5-----------------------------
void heapifyTD (int v[], int N){
    for(int i = 0; i < N; i++){
        bubbleUp(i,v);
    }
}

void heapifyBU (int v[], int N){
    for(int i = N -1; i >= 0; i--){
        bubbleDown(i,v,N);
    }
}

//6------------------------------
void ordenaHeap (int h[], int N){
    swap(h,0,N - 1);
    for(int i = N - 2; i >= 0;i--){
        bubbleDown(0,h,i);
        swap(h,0,i);
    }
}

//2 - Hash

#define Size 100
typedef struct nodo {
    char *chave; int ocorr;
    struct nodo *prox;
} Nodo, *THash [Size];

unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

//1-----------------------
void initEmptyH (THash t){
    for(int i = 0; i < Size; i++){
        t[i] = NULL;
    }
}

//2--------------------------
void addH (char *s, THash t){
    int h = hash(s) % Size;
    Nodo *temp = t[h];
    while(temp && strcmp(s,temp->chave)){
        temp = temp->prox;
    }
    if (temp) temp->ocorr++;
    else{
        temp = malloc(sizeof (Nodo));
        temp->ocorr = 1;
        strcpy(temp->chave,s);
        temp->prox = t[h];
    }
    t[h] = temp;
}

//3---------------------------
int lookup (char *s, THash t){
    int h = hash(s) % Size;
    Nodo *temp = t[h];
    while(temp && strcmp(s, temp->chave)){
        temp = temp->prox;
    }
    if (temp) return temp->ocorr;
    else return 0;
}

//4----------------------------
int removeH (char *s, THash t){
    int h = hash(s) % Size;
    Nodo *temp = t[h];
    Nodo *temp0 = NULL;
    while(temp && strcmp(s,temp->chave)){
        temp0 = temp;
        temp = temp->prox;
    }
    if (!temp) return 1;
    else{
        if (temp->ocorr > 1) {
            temp->ocorr--;
            t[h] = temp;
        }
        else{
            if (temp0) {
                temp0->prox = temp->prox;
                t[h] = temp0;
            }
            else t[h] = temp->prox;
            free(temp);
        }
    }
    return 0;
}

#define Size 100
#define Free 0
#define Used 1
#define Del 2
typedef struct bucket {
    int probC;
    int status; // Free | Used | Del
    char *chave; int ocorr;
} THash [Size];

//1--------------------------
//dificil
int where (char *s, THash t){
    int h = hash(s) % Size;
    int i = 0;
    int del = -1;
    while(i < Size && ((strcmp(s,t[h].chave) && t[h].status == Used) || t[h].status == Del)){
        if (t[h].status == Del) del = h;
        h = (h + 1) % Size;
        i++;
    }
    if (del != -1) return del;
    else return h;
}

//2------------------------
void initEmptyH1 (THash t){
    for(int i = 0; i < Size; i++){
        t[i].status = Free;
    }
}

void addH1 (char *s, THash t){
    int h = where(s,t);
    if (t[h].status == Free){
        t[h].status = Used;
        strcpy(t[h].chave,s);
        t[h].ocorr = 1;
    }
    else if (t[h].status == Used && !strcmp(t[h].chave,s)){
        t[h].ocorr++;
    }
}

int lookupH1 (char *s, THash t){
    int h = where(s,t);
    if (t[h].status == Used && !strcmp(t[h].chave,s)) return t[h].ocorr;
    return 0;
}

int removeH1 (char *s, THash t){
    int h = where(s,t);
    if (t[h].status == Used && !strcmp(t[h].chave,s)){
        if (t[h].ocorr > 1) t[h].ocorr--;
        else t[h].status = Del;
        return 0;
    }
return 1;
}

//3---------------------------
int garb_collection (THash t){
    THash newt;
    char *keys[Size];
    int ocor[Size];
    int j = 0;
    for(int i = 0; i < Size; i++){
        if (t[i].status == Used){
            keys[j] = strdup(t[i].chave);
            ocor[j] = t[i].ocorr;
            j++;
        }
    }
    initEmptyH(newt);
    for(int m = 0; keys[m]; m++){
        while(ocor[m] > 0) {
            addH(keys[m], newt);
            ocor[m]--;
        }
    }
    return 0;
}



// MAIN -------------------------------------------------------

int main() {
}
