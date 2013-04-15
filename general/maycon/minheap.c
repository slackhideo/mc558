#include <stdio.h>
#include <stdlib.h>

#define INF 0x7FFFFFFF

int parent(int i) {
    return i/2;
}

int left(int i) {
    return 2*i;
}

int right(int i) {
    return 2*i + 1;
}

void exchange(int* a, int* b) {
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void minheapify(int* H, int* aux, int size, int i) {
    int l, r;
    int minimum;

    l = left(i);
    r = right(i);

    if(l < size && H[l] < H[i]) {
        minimum = l;
    }
    else {
        minimum = i;
    }

    if(r < size && H[r] < H[minimum]) {
        minimum = r;
    }

    if(minimum != i) {
        exchange(&H[i], &H[minimum]);
        exchange(&aux[i], &aux[minimum]);
        minheapify(H, aux, size, minimum);
    }
}

void buildminheap(int* H, int* aux, int size) {
    int i;

    for(i = size/2; i >= 0; i--) {
        minheapify(H, aux, size, i);
    }
}

int heapminimum(int* aux) {
    return aux[0];
}

int heapextractmin(int* H, int* aux, int* size) {
    int min;

    if(*size < 1) {
        printf("Erro! Heap vazio!\n");
        exit(1);
    }

    min = aux[0];
    H[0] = H[(*size)-1];
    aux[0] = aux[(*size)-1];
    (*size)--;
    minheapify(H, aux, *size, 0);

    return min;
}

void heapdecreasekey(int* H, int* aux, int i, int key) {
    if(key > H[i]) {
        printf("Erro! Nova chave é maior que a atual!\n");
        exit(1);
    }

    H[i] = key;
    while(i > 0 && H[parent(i)] < H[i]) {
        exchange(&H[i], &H[parent(i)]);
        exchange(&aux[i], &aux[parent(i)]);
        i = parent(i);
    }
}

void minheapinsert(int* H, int* aux, int* size, int key) {
    (*size)++;
    H[(*size)-1] = INF;
    heapdecreasekey(H, aux, (*size)-1, key);
}

int heapfind(int* aux, int size, int vertex) {
    int i;

    for(i = 0; i < size; i++) {
        if(aux[i] == vertex) {
            return i;
        }
    }

    return -1;
}
