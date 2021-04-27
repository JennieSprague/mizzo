#include "producer.h"
#include "main.h"
#include <stdio.h>

void * producerCFB(void * VoidPtr){
    Buffer *buffer = (Buffer *)VoidPtr;
    ProductType CFB = FrogBite;
    int totalProduced = buffer->Produced[FrogBite] + buffer->Produced[Escargot];
    if (buffer->frogDelay > 0){
	buffer->frogTime.tv_sec = 0;
	buffer->frogTime.tv_nsec = buffer->frogDelay;	
    }
    while (totalProduced < 100){
	
	//make sure there is room
	sem_wait(&buffer->cfbAvailable);
	sem_wait(&buffer->availableSlots);
	//check for delay, sleep for specified time
	if (buffer->frogDelay > 0){
	    if(nanosleep(&buffer->frogTime, &buffer->rem) != 0){
		printf("error in delay\n");
		exit(5);
	    }
	}
	//access buffer exclusively
	sem_wait(&buffer->mutex);
	 totalProduced = buffer->Produced[FrogBite] + buffer->Produced[Escargot];
	 if (totalProduced >= 100){
	     sem_post(&buffer->mutex);
	     sem_post(&buffer->cfbAvailable);
	     sem_post(&buffer->availableSlots);
	     break;
	 }
	 addItem(CFB, buffer);
	 buffer->Produced[FrogBite]++;
	 buffer->OnBelt[FrogBite]++;
	 io_add_type(CFB, buffer->OnBelt, buffer->Produced);
	 //inform customer
	 sem_post(&buffer->unconsumed);
	 totalProduced = buffer->Produced[FrogBite] + buffer->Produced[Escargot];
	sem_post(&buffer->mutex);
    }
}

void * producerEES(void * VoidPtr){
    Buffer *buffer = (Buffer*)VoidPtr;
    ProductType EES = Escargot;
    if (buffer->escarDelay > 0){
	buffer->escargotTime.tv_sec = 0;
	buffer->escargotTime.tv_nsec = buffer->ethelDelay;
    }
    int totalProduced = buffer->Produced[FrogBite] + buffer->Produced[Escargot];
    while(totalProduced < 100){
	//make sure we have room
	sem_wait(&buffer->availableSlots);
	if (buffer->escarDelay > 0){
	    if(nanosleep(&buffer->escargotTime, &buffer->rem) !=0){
		printf("error in delay\n");
		exit(5);
	    }
	}
	//access buffer exclusively
	sem_wait(&buffer->mutex);
	 totalProduced = buffer->Produced[FrogBite] + buffer->Produced[Escargot];
	 if (totalProduced >= 100){
	     sem_post(&buffer->mutex);
	     sem_post(&buffer->availableSlots);
	     break;
	 }
	 buffer->Produced[Escargot]++;
	 buffer->OnBelt[Escargot]++;
	 io_add_type(EES, buffer->OnBelt, buffer->Produced);
	 addItem(EES, buffer);
	 //inform consumer
	 sem_post(&buffer->unconsumed);
	 totalProduced = buffer->Produced[FrogBite] + buffer->Produced[Escargot];
	sem_post(&buffer->mutex);
    }
}