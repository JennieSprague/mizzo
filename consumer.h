#ifndef CONSUMER_H
#define CONSUMER_H
#include "main.h"
#include "functions.h"

/*
 * void * consumer(void *VoidPtr)
 * this function is user for the consumer
 * thread 
 * when there is a product on the belt,
 * it will remove it from the buffer/queue
 *
 * */
void * consumer(void *VoidPtr);

#endif