#ifndef PRODUCER_H
#define PRODUCER_H
#include "main.h"
#include "functions.h"

/*
 * void * producerCFB(void *VoidPtr)
 * this function is used for the production thread of 
 * the crunchy frog bites
 * when there is room, it will add a CFB to the buffer
 * to be consumed, using a critical section
 * */
void *producerCFB(void *VoidPtr);

/*
 * void * producerEES (void *VoidPtr)
 * this function is used for the production thread of 
 * the Everlasting Excargot Suckers
 * when there is room, it will add an EES to the buffer
 * to be consumed, using a critical section
 * */
void * producerEES(void *VoidPtr);
#endif