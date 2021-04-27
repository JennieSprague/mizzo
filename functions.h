#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*
    this function initializes all of the variables
    of the buffer structure
*/
Buffer *createBuffer(int capacity);

int isFull(Buffer *buffer);

int isEmpty(Buffer *buffer);

/*
    this function rearranges the buffer belt to add an
    item to the back and increment the size
*/
void addItem(ProductType product, Buffer *buffer);

/*
    this function rearranges the buffer belt to remove an
    item from the front and decrement the size
*/
ProductType removeItem(Buffer *buffer);

#endif