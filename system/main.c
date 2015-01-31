/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
//#include <stdlib.h>
/*create a circular buffer maybe */
/*
typedef struct
{
	int32 head;
	int32 tail;
	int32 maxsize;
	int32* arr;
}  cqueue;

cqueue* newcqueue()
{
	cqueue* cq = malloc(sizeof(cqueue));
    cq->head = 0;
    cq->tail = 0;
    cq->arr = (int32 *)malloc(sizeof(int32)*1000);
    cq->maxsize = 1000;
    return cq;
}
int32 getSize(cqueue* c)
{
    return c->tail - c->head;
}
bool8 isFull(cqueue* c)
{
    return c->tail - c->head == c->maxsize;
}
bool8 isEmpty(cqueue* c)
{
    return c->tail == c->head;
}
void cenqueue(int32 data, cqueue* c)
{
    if (!isFull(c))
    {
        *(c->arr+c->tail%c->maxsize) = data;
        ++c->tail;
    }
}
int cdequeue(cqueue* c)
{
    if (!isEmpty(c))
    {
        int32 element = *(c->arr+c->head%c->maxsize);
        *(c->arr+c->head%c->maxsize) = 0;
        ++c->head;
        return element;
    }
    return 0;
}
//create new queue
cqueue* c;
*/
/*global variable for forks?*/
void produce(sid32, sid32), consume(sid32, sid32);
int32 n = 0;
int main(int argc, char **argv)
{
	//c = newcqueue();
	/*
	 * a) The problems that arise have to do with the possible different speeds of
	 * producing and consuming. For example, if the consumer is faster than the producer,
	 * it will pass by the producer and begin consuming garbage data. If the producer is
	 * faster than the consumer, it will try and put data into a full buffer and overwrite
	 * old data.
	 */
	/*
	int i;
	for (i=0; i<500; ++i)
	{
		cenqueue(i+1, c);
	}
	for (i=0; i<500; ++i)
	{
		kprintf("%d\n", cdequeue(c));
	}
	kprintf("%d\n", getSize(c));
	free(c);
	c = NULL;
	*/
	/*
	uint32 retval;
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	// Wait for shell to exit and recreate it

	recvclr();
	while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}
	while (1);
*/
	sid32 space_left, produced;
	space_left = semcreate(1000); //start with empty buffer of 1000
	produced = semcreate(0);
	resume( create(consume, 1024, 20, "cons", 2, space_left, produced) );
	resume( create(produce, 1024, 20, "prod", 2, space_left, produced) );
	return OK;
}
/*------------------------------------------------------------------------
* produce -
*------------------------------------------------------------------------
*/
void produce(sid32 space_left, sid32 produced)
{
	while(1)
	{
		wait(space_left);
		n++;
		int32 tmp = n;
		kprintf("Producing %d \n", tmp);
		signal(produced);
	}
}
/*------------------------------------------------------------------------
* consume -
*------------------------------------------------------------------------
*/
void consume(sid32 space_left, sid32 produced)
{
	while(1)
	{
		wait(produced);
		n--;
		int32 tmp = n;
		kprintf("Consuming %d \n", tmp);
		signal(space_left);
	}
}
