#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "queue.h"
#include "structs.h"

/**
	Internal func allocates the queue's sentinel. Sets sentinels' next to null,
	and queue's head and tail to the sentinel.
	param: 	queue 	struct LinkedList ptr
	pre: 	queue is not null
	post: 	queue sentinel not null
			sentinel next points to null
			head points to sentinel (always)
			tail points to sentinel (always point to last link unless empty)
 */
void listQueueInit(struct Queue* queue)
{

	assert(queue != 0);
	struct Link* link_pointer = (struct Link*)malloc(sizeof(struct Link));
	assert(link_pointer != NULL);
	link_pointer->next = NULL;
	queue->head = link_pointer;
	queue->tail = link_pointer;
}

/**
	Allocates and initializes a queue.
	pre: 	none
	post: 	memory allocated for new struct Queue ptr
			queue init (call to _initQueue func)
	return: queue
 */
struct Queue* listQueueCreate()
{

	struct Queue* queue_pointer = (struct Queue*)malloc(sizeof(struct Queue));
	listQueueInit(queue_pointer);
	return queue_pointer;
}

/**
	Adds a new link with the given value to the back of the queue.
	param: 	queue 	struct Queue ptr
	param: 	value 	TYPE
	pre: 	queue is not null
	post: 	link is created with given value
			link is added before current last link (pointed to by queue tail)
 */
void listQueueAddBack(struct Queue* queue, TYPE2 value)
{
	assert(queue != NULL);
	struct Link* link_pointer = (struct Link*)malloc(sizeof(struct Link));
	assert(link_pointer != NULL);
	link_pointer->value = value;
	link_pointer->next = NULL;
	queue->tail->next = link_pointer;
	queue->tail = link_pointer;
}

/**
	Returns the value of the link at the front of the queue.
	param: 	queue 	struct Queue ptr
	pre:	queue is not null
	pre:	queue is not empty (i.e., queue's head next pointer is not null)
	post:	none
	ret:	first link's value
 */
TYPE2 listQueueFront(struct Queue* queue)
{
	//makes sure that queue is not null and that the queue is not empty
	assert(queue != NULL);
	assert(queue->head != queue->tail);

	return queue->head->next->value;
}

/**
	Removes the link at the front of the queue and returns the value
	of the removed link.
	param: 	queue 	struct Queue ptr
	pre:	queue is not null
	pre:	queue is not empty (i.e., queue's head next pointer is not null)
	post:	first link is removed and freed (call to removeLink)
 */
TYPE2 listQueueRemoveFront(struct Queue* queue)
{
	assert(queue != NULL);
	assert(queue->head != queue->tail);
	struct Link* link_pointer = queue->head->next;
	TYPE2 x = queue->head->next->value;
	if (queue->head->next == queue->tail) {
		queue->tail = queue->head;
		queue->head->next = NULL;
	}
	else {
		queue->head->next = queue->head->next->next;
	}
	free(link_pointer);
	link_pointer = NULL;
	return x;
}

/**
	Returns 1 if the queue is empty and 0 otherwise.
	param:	queue	struct Queue ptr
	pre:	queue is not null
	post:	none
	ret:	1 if queue head next pointer is null (empty);
			otherwise 0 (not null; not empty)
 */
int listQueueIsEmpty(struct Queue* queue)
{
	//makes sure that queue is not null
	assert(queue != NULL);

	//runs if list is empty
	if (queue->head == queue->tail) {
		return 1;
	}
	//runs if list isn't empty
	else {
		return 0;
	}
}

/**
	Deallocates every link in the queue including the sentinel,
	and frees the queue itself.
	param:	queue 	struct Queue ptr
	pre: 	queue is not null
	post: 	memory allocated to each link is freed
			" " sentinel " "
			" " queue " "
 */
void listQueueDestroy(struct Queue* queue)
{
	assert(queue != NULL);
	while (!listQueueIsEmpty(queue)) {
		listQueueRemoveFront(queue);
	}
	free(queue->head);
	free(queue);
	queue = NULL;
}
