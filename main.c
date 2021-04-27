#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "functions.h"
#include "producer.h"
#include "consumer.h"

int main(int argc, char *argv[]){
    int option;
    int ethelDelay = 0;
    int lucyDelay = 0;
    int frogDelay = 0;
    int escarDelay = 0;
    int numMutex = 1;
    int numUnconsumed = 0;
    int numAvailableSlots = 10;
    int numCFBAvailable = 3;
    int numBarrier = 0;
    while( ( option = getopt(argc, argv, "E:L:f:e:") ) != -1){
        switch (option)
        {
        case 'E':
            /* code */
            ethelDelay = atoi(optarg);
	    printf("Ethel delay: %d\n", ethelDelay);
	    fflush(stdout);
            break;
        case 'L':
            lucyDelay = atoi(optarg);
	    printf("Lucy delay: %d\n", lucyDelay);
	    fflush(stdout);
            break;
        case 'f':
            frogDelay = atoi(optarg);
	    printf("Frog delay: %d\n", frogDelay);
	    fflush(stdout);
            break;
        case 'e':
            escarDelay = atoi(optarg);
	    printf("Escargot delay: %d\n", escarDelay);
	    fflush(stdout);
            break;
        default:
            break;
        }
    }
    
    /* initialize the buffer */
    Buffer *buffer;
    buffer = createBuffer(numAvailableSlots);
    /* initialize the semaphores */
    if (sem_init(&buffer->mutex, 0, numMutex) == -1){
	printf("unable to initialize mutex\n");
	fflush(stdout);
	exit(2);
    }
    if (sem_init(&buffer->unconsumed, 0, numUnconsumed) == -1){
	printf("unable to initialize unconsumed slots\n");
	fflush(stdout);
	exit(2);
    }
    if (sem_init(&buffer->availableSlots, 0, numAvailableSlots) == -1){
	printf("unable to initialize available slots\n");
	fflush(stdout);
	exit(2);
    }
    if (sem_init(&buffer->cfbAvailable, 0, numCFBAvailable) == -1){
	printf("unable to initializes CFB available slots\n");
	fflush(stdout);
	exit(2);
    }
    if (sem_init(&buffer->barrier, 0, numBarrier) == -1){
	printf("unable to initialize barrier\n");
	fflush(stdout);
	exit(2);
    }   
    /* initialize the threads */
    pthread_attr_t pthread_attributes;
    pthread_t threadCFB, threadEES, threadLucy, threadEthel;
    buffer->threadEthel = &threadEthel;
    buffer->threadLucy = &threadLucy;
    buffer->threadCFB = &threadCFB;
    buffer->threadEES = &threadEES;
    pthread_attr_init(&pthread_attributes);

    /* produced threads */
    if (pthread_create(&threadCFB, &pthread_attributes, &producerCFB, (void *) buffer) != 0){
	printf("unable to create Crunchy Frog Bites Producer thread\n");
	fflush(stdout);
	exit(1);
    }
    if (pthread_create(&threadEES, &pthread_attributes, &producerEES, (void *) buffer) != 0){
	printf("unable to create Everlasting Escargot Sucker Producer thread\n");
	fflush(stdout);
	exit(1);
    }

    /* consumer threads*/ 
    if (pthread_create(&threadLucy, &pthread_attributes, &consumer, (void *) buffer) != 0){
	printf("unable to create Lucy consumer thread\n");
	fflush(stdout);
	exit(1);
    }
    if(pthread_create(&threadEthel, &pthread_attributes, &consumer, (void *) buffer) != 0){
	printf("unable to create Ethel consumer thread\n");
	fflush(stdout);
	exit(1);
    }
    if (pthread_join(threadCFB, NULL) != 0){
	printf("join fail cfb\n");
    }
    if (pthread_join(threadEES, NULL) != 0){
	printf("join fail ees\n");
    }
    sem_wait(&buffer->barrier);
    io_production_report(buffer->Produced, buffer->consumed);
}