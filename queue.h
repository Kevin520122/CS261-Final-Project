//Linked List Queue interface

#ifndef QUEUE_H
#define QUEUE_H 1

#include "structs.h"

# ifndef TYPE2
# define TYPE2 struct enemy*
# endif

// Single link
struct Link {
	TYPE2 value;
	struct Link* next;
};

// Single linked list with head and tail pointers
struct Queue {
	struct Link* head;
	struct Link* tail;
};


/* ************************************************************************
	Queue Interface
************************************************************************ */
void listQueueInit(struct Queue* queue);
struct Queue* listQueueCreate();
void listQueueDestroy(struct Queue* queue);

void listQueueAddBack(struct Queue* queue, TYPE2 value);

TYPE2 listQueueFront(struct Queue* queue);
TYPE2 listQueueRemoveFront(struct Queue* queue);

int listQueueIsEmpty(struct Queue* queue);
#endif