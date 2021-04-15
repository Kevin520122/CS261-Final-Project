/***********************************************************
* Game Interface
*
*
************************************************************/
 

#ifndef GAME_H
#define GAME_H 1

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "structs.h"
#include "bst.h"
#include "queue.h"

struct player
{
	int hp;
	struct BSTree* ingredientsBag;
	struct BSTree* potionsBag;
};

struct game
{
	struct player* player;
    struct Queue* enemies;
};

//Game Functions
void startGame();
void gameLoop();
struct game* initGame();

//Info
void info_turn();
int check_win(struct Queue* q_enemy);
int scanNum(int min, int max);

//Potions
void addPotions(struct BSTree* potBag, char *value);
void removePotions(struct BSTree* potBag, char* value);
void init_Potions_Bag(struct BSTree* potBag);
void scanIng(int* ing_index, struct BSTree* ingBag);

//Crafting
void makePotions(struct BSTree* ingBag, struct BSTree* potBag);
void printRecipes();
void castIngredient(int* num, struct items* ingredient);
//void printBST(struct Node* currentNode, int index);

void addIngredients(struct BSTree* ingBag, char* name);
void set_Ingredients_Bag(struct BSTree* ingBag);

//Player
void battle(struct enemy * enem, struct player* player);
struct player* initPlayer();

//Enemy
struct Queue* initEnemies();
struct enemy * createEnemy(int hp, int diff, char *name);
void setEnemies(struct Queue* q_enemy);
void killEnemey(struct Queue* q_enemy);

//Deallocation
void deleteGame(struct game * newGame);
void deletePlayer(struct player* playerIn);
void deleteEnemies(struct Queue* enemies);
#endif