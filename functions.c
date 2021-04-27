#include "main.h"
#include "functions.h"
#include <stdio.h>

Buffer *createBuffer(int capacity){
    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->ethelDelay = 0;
    buffer->lucyDelay = 0;
    buffer->frogDelay = 0;
    buffer->escarDelay = 0;
    buffer->capacity = capacity;
    buffer->front = 0;
    buffer->size = 0;
    buffer->back = capacity-1;
    buffer->belt = calloc(buffer->capacity, sizeof(ProductType));
    buffer->OnBelt[FrogBite] = 0;
    buffer->OnBelt[Escargot] = 0;
    buffer->Produced[FrogBite] = 0;
    buffer->Produced[Escargot] = 0;
    int i = 0;
    for (i = 0; i < ConsumerTypeN; i++){
	buffer->consumed[i] = calloc(ProductTypeN, sizeof(int));
    }
    int consumedLucy[ProductTypeN] = {0,0};
    int consumedEthel[ProductTypeN] = {0,0};
    *(buffer->consumed[Lucy]) = *consumedLucy;
    *(buffer->consumed[Ethel]) = *consumedEthel;
    return buffer;
}

int isFull(Buffer *buffer){
    return (buffer->size == buffer->capacity);
}

int isEmpty(Buffer *buffer){
    return (buffer->size == 0);
}

void addItem(ProductType product, Buffer *buffer){
    buffer->back = (buffer->back + 1) % buffer->capacity;
    buffer->belt[buffer->back] = product;
    buffer->size = buffer->size + 1;
}

ProductType removeItem(Buffer *buffer){
    ProductType product = buffer->belt[buffer->front];
    buffer->front = (buffer->front+ 1) % buffer->capacity;
    buffer->size = buffer->size - 1;
    return product;	
}