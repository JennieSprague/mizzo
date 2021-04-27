#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "io.h"


typedef struct Buffer {
    sem_t unconsumed;
    sem_t availableSlots;
    sem_t cfbAvailable;
    sem_t mutex;
    sem_t barrier;
    int ethelDelay;
    int lucyDelay;
    int frogDelay;
    int escarDelay;
    int capacity;
    int front, back, size;
    ProductType* belt; 
    int OnBelt[ProductTypeN];
    int Produced[ProductTypeN];
    int *consumed[ConsumerTypeN];
    //int consumedArr[ProductTypeN];
    int numConsumed;
    pthread_t *threadLucy;
    pthread_t *threadEthel;
    pthread_t *threadCFB;
    pthread_t *threadEES;
    struct timespec frogTime;
    struct timespec escargotTime;
    struct timespec lucyTime;
    struct timespec ethelTime;
    struct timespec rem;
}Buffer;

/* createBuffer(int capacity)
 * Create a FIFO queue of the specified capacity
 * Initialize the empty queue
 * 
 * Expects:
 * capacity: number of products allowed on belt at a time
 * (will always be 10 for this problem)
 * */
Buffer *createBuffer(int capacity);

/* isFull(*Buffer buffer)
 * check if the buffer is full by seeing if the 
 * current size is the same as the capacity
 *
 * Expects:
 * buffer: pass in pointer to the buffer structure
 * containing information about the candies on the belt
 * waiting to be consumed
 * */
int isFull(Buffer *buffer);

/* isEmpty(*Buffer buffer)
 * checks if the buffer is empty by seeing if the
 * current size is zero */
int isEmpty(Buffer *buffer);

/* addItem(ProductType product, *Buffer buffer)
 * adds an item to the end of the buffer
 * updates the back and the size of the buffer
 * */
void addItem(ProductType product, Buffer *buffer);

/* removeItem(*Buffer buffer)
 * removes and item from the front of the buffer
 * updates the front and the size of the buffer
 * */
ProductType removeItem(Buffer *buffer);

#endif