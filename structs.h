/***********************************************************
* Structs for ADTs
*
*
************************************************************/

#ifndef STRUCTS_H
#define STRUCTS_H 1

/*
Store potions or ingredients
*/
struct items
{
	char* name;
};

struct enemy
{
	int hp;
	int difficulty;
	char* name;
};

#endif