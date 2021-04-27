#include "consumer.h"
#include "main.h" 
#include <stdio.h>
void * consumer(void *VoidPtr){
    //printf("entered consumer thread\n");
    fflush(stdout);
    Buffer *buffer = (Buffer*)VoidPtr;
    ProductType product;
    pthread_t consumerThread = pthread_self(); 
    ConsumerType currConsumer;
    if (pthread_equal(consumerThread, *buffer->threadLucy) == 0){
	currConsumer = Lucy;
    }
    else if (pthread_equal(currConsumer, *buffer->threadEthel) == 0){
	currConsumer = Ethel;
    }
    else {
	printf("unidentified consumer thread\n");
	fflush(stdout);
	exit(3);
    }
    //use currConsumer to identify needed delay
    if (currConsumer == Lucy){
	if (buffer->lucyDelay > 0){
	    buffer->lucyTime.tv_sec = 0;
	    buffer->lucyTime.tv_nsec = buffer->lucyDelay;
	}
    }
    else if (currConsumer == Ethel){
	if (buffer->ethelDelay > 0){
	    buffer->ethelTime.tv_sec = 0;
	    buffer->ethelTime.tv_nsec = buffer->ethelDelay;
	}
    }
    while(buffer->numConsumed < 100){
	//block until there is something to consume
	sem_wait(&buffer->unconsumed);
	//access buffer exclusively
	//enter critical section
	sem_wait(&buffer->mutex);
	 if(buffer->numConsumed >= 100) {
	     sem_post(&buffer->mutex);
	     sem_post(&buffer->unconsumed);
	     if (currConsumer == Lucy) pthread_kill(*buffer->threadEthel);
	     else if (currConsumer == Ethel) pthread_kill(*buffer->threadLucy);
	     pthread_exit(NULL);
	     break;
	 }
	 product= removeItem(buffer);
	 //if product consumed is EES, up EES available
	 if (product == FrogBite){
	     sem_post(&buffer->cfbAvailable);
	     buffer->OnBelt[FrogBite]--;
	 }	
	 else buffer->OnBelt[Escargot]--;
	 
	 if (currConsumer == Lucy) {
	     buffer->consumed[Lucy][product]++;
	     io_remove_type(currConsumer, product, buffer->OnBelt, buffer->consumed[Lucy]);

	 } 
	 else if (currConsumer == Ethel) {
	     buffer->consumed[Ethel][product]++;
	     io_remove_type(currConsumer, product, buffer->OnBelt, buffer->consumed[Ethel]);
	 } 
	 //availableSlots.up();
	 sem_post(&buffer->availableSlots);
	 //exit critical section
	 buffer->numConsumed++; 
	sem_post(&buffer->mutex);
	if ((currConsumer == Lucy) && (buffer->lucyDelay >0)){
	    if (nanosleep(&buffer->lucyTime, &buffer->rem) != 0){
		printf("error in delay\n");
		exit(5);
	    }
	}
	else if((currConsumer == Ethel) && (buffer->ethelDelay > 0)){
	    if (nanosleep(&buffer->ethelTime, &buffer->rem) != 0){
		printf("error in delay\n");
		exit(5);
	    }
	}
    }
    sem_post(&buffer->barrier);
    pthread_exit(NULL);
}