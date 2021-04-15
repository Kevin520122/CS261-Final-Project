#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bst.h"
#include "structs.h"


/*
   Return value:
	-1 if left < right return
	 1 if left > right return
	 0 if left = right return
*/

//Need to figure out how to compare types of potions and enemies too 
int compare(TYPE left, TYPE right)
{
   //struct items* leftData = (struct items *)left;
   //struct items* rightData = (struct items *)right;

    char* lData, *rData;
    lData = ((struct items*)left)->name;
    rData = ((struct items*)right)->name;

   if(strcmp(lData, rData) < 0) return -1;
   if(strcmp(lData, rData) > 0) return 1;
	return 0;
}
void print_type(TYPE value)
{
   //struct items *myData = (struct items*)value; Error here
   //Should be like this:
   printf("Item: %s\n", ((struct items*)value)->name);
}