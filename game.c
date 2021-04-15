
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "structs.h"
#include "bst.h"
#include "queue.h"
#include "game.h"

void startGame()
{
    gameLoop();
}

/***********************************************************
* Internal Game Functions
************************************************************/
void info_turn() {
	printf("You can choose the events below: \n");
	printf("\n1. Battle\n2. Pick up Ingredients\n3. Make Potions\n");
	printf("4. Display Ingredients Bag\n5. Display Portions Bag\n6. Quit\n");
}

int check_win(struct Queue* q_enemy) {
	if (listQueueIsEmpty(q_enemy) == 1) { return 1; }
	{return 0;}
}

int scanNum(int min, int max){
	char ing[25];
	scanf("%s", ing);
	while(min > atoi(ing) || atoi(ing) > max){
		printf("\nPlease enter a number between %d and %d: ", min, max);
		scanf("%s", ing);
	}
	return atoi(ing);
}

void gameLoop()
{
    struct game* newGame = initGame();
	printf("Starting game...\n");
	int choice = 1;
    while(newGame->player->hp > 0 && (choice >= 1 && choice <= 5))
    {
		info_turn();
		printf("Choice: ");
		choice = scanNum(1,6);
		//suggested gameplay loop:
		//battle if applicable
		if (choice == 1) {
			if(isEmptyBSTree(newGame->player->potionsBag))
			{
				printf("You need potions to battle!\n");
				continue;
			}
			struct enemy* cur = listQueueFront(newGame->enemies);
			battle(cur, newGame->player);
			if (cur->hp <= 0) { killEnemey(newGame->enemies); }
			
		}
		//pick up ingredient if applicable
		else if (choice == 2) {
			set_Ingredients_Bag(newGame->player->ingredientsBag);
		}
		//player can make potions if desired
		else if(choice == 3)
		{
			makePotions(newGame->player->ingredientsBag, newGame->player->potionsBag);
		}
		else if (choice == 4) {
			printBSTree(newGame->player->ingredientsBag);
		}
		else if (choice == 5) {
			printBSTree(newGame->player->potionsBag);
		}
		//Every turn check if the user wins(kill all the enemies)
		if (check_win(newGame->enemies) == 1) {
			printf("\033c");
			printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
			printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
			printf("Congratulations! You win the game!\n");

printf("       .''.      .        *''*    :_\\/_:     .\n"); 
printf("      :_\\/_:   _\\(/_  .:.*_\\/_*   : /\\ :  .'.:.'.\n");
printf("  .''.: /\\ :   ./)\\   ':'* /\\ * :  '..'.  -=:o:=-\n");
printf(" :_\\/_:'.:::.    ' *''*    * '.\'/.' _\\(/_'.':'.'\n");
printf(" : /\\ : :::::     *_\\/_*     -= o =-  /)\\    '  *\n");
printf("  '..'  ':::'     * /\\ *     .'/.\'.   '\n");
printf("      *            *..*         :\n");
printf("       *\n");
printf("        *\n");




			break;
		};
    }
	if (newGame->player->hp <= 0) { printf("You lose the game!\n"); }
    deleteGame(newGame);
}
/**
	PotionsBag
**/
void addPotions(struct BSTree* potBag, char *value) {
	struct items newPot;
	newPot.name = value;
	printf("Adding %s to potions bag...\n", newPot.name);
	addBSTree(potBag, &newPot);
}
void removePotions(struct BSTree* potBag, char*value) {
	struct items newPot;
	newPot.name = value;
	removeBSTree(potBag, &newPot);
}
void init_Potions_Bag(struct BSTree* potBag) {
	addPotions(potBag, "fire");
}

void castIngredient(int* num, struct items* ingredient) {
	
	if (*num == 1) {
		ingredient->name = "Magic herbs";
	}
	else if (*num == 2) {
		ingredient->name = "Butterfly wings";
	}
	else if (*num == 3) {
		ingredient->name = "Suspicious mushrooms";
	}
	else {
		ingredient->name = "Useless sludge";
	}
}

void scanIng(int* ing_index, struct BSTree* ingBag) {
	struct items* ingredient = malloc(sizeof(struct items));
	printf("Please type the first/second ingredients number: ");
	*ing_index = scanNum(1,3);
	castIngredient(ing_index, ingredient);
	while (containsBSTree(ingBag, ingredient) == 0) {
		printf("\nYou don't have that ingredient! Choose another: ");
		printf("Please type the first/second ingredients number: ");
		scanf("%d", &(*ing_index));
		castIngredient(ing_index, ingredient);
	}
	removeBSTree(ingBag, ingredient);
	free(ingredient);
}
/**
	Crafting System Functions???
**/
//Assuming 2 ingredients can generate a kind of portion
void makePotions(struct BSTree* ingBag, struct BSTree* potBag) {
	int ing1 = 0, ing2 = 0, sum = 0;
	if (sizeBBSTree(ingBag) < 2) {
		printf("You need to collect more ingredients first!\n");
		return;
	}
	printf("Your ingredients bag: \n");
	//printBST(ingBag->root, 1);	//Print IngridentsBag
	printBSTree(ingBag);
	printRecipes();

	//Set the ing1 and ing2 value and check if it's valid
	scanIng(&ing1, ingBag);
	scanIng(&ing2, ingBag);

	sum = ing1 + ing2;
	if (sum == 3) { addPotions(potBag, "fire"); }
	else if (sum == 4) { addPotions(potBag, "Ice"); }
	//More cases if there're more kinds of ingredients
	else { addPotions(potBag, "health"); }
	printf("\nNow your Potions Bag: \n");
	//printBST(potBag->root, 1);		//Print Potions Bag
	printBSTree(potBag);
	
	
	
	/**Old potion making - does not check bag or remove
	int ing1, ing2, sum;
	printf("Your ingredients bag: \n");
	//printBST(ingBag->root, 1);	//Print IngridentsBag
	printBSTree(ingBag);
	printRecipes();
	printf("Please type the first ingredients number: ");
	ing1 = scanNum(1,3);
	printf("\nPlease type the second ingredients number: ");
	ing2 = scanNum(1,3);
	sum = ing1 + ing2;
	if (sum == 3) { addPotions(potBag, "fire"); }
	else if (sum == 4) { addPotions(potBag, "Ice"); }
	//More cases if there're more kinds of ingredients
	else { addPotions(potBag, "health"); }
	printf("\nNow your Potions Bag: \n");
	//printBST(potBag->root, 1);		//Print Potions Bag
	printBSTree(potBag);**/
}
void printRecipes(){
	//show all recipes?
	printf("Here is the recipe to synthesis the potions: \n");
	printf("Magic herbs: 1\nButterfly wings: 2\nSuspicious Mushrooms: 3\n\n");
	printf("1+2 => fire\n");
	printf("1+3 => Ice\n");
	printf("2+3 => health\n");
	//More cases if there're more kinds of ingredients
	

}


/**
	IngredientsBag
**/
//Display the ingredients bag and potions bag
 void displayBag(struct Node* currentNode, int index){
// 	//print a list of all ingredients in player's inventory
	
 	//BaseCase
 	if (currentNode == NULL) { return; }
 	displayBag(currentNode->left, ++index);
 	printf("\033c");
 	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
 	printf("xxxxxxxxx        YOUR INVENTORY                    \n");
 	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
 	printf("%d. %s\n", index, (char*)currentNode->value);
 	displayBag(currentNode->right, ++index);
 	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
 }

//some other functions to actually make potions, use potions, & collect ingredients
void addIngredients(struct BSTree* ingBag, char*name) {
	struct items newIng;
	newIng.name = name;
	addBSTree(ingBag, &newIng);
}



//Assuming once the ingredients put the bag, the number of ingredients is infinite
//In other words, we don't have to remove the ingredients.
void set_Ingredients_Bag(struct BSTree* ingBag) {
	int ing1, choice = 0, ctr = 0; //Ingredients
	printf("\033c");
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("In the game world, it exists 3 types of ingredients: \n");
	printf("...................................................\n");
	printf("    1.Magic herbs\n");

	    printf("   2.  Butterfly wings\n");
printf("            _\n");
printf("        /> //  __\n");
printf("    ___/ \\// _/ /\n");
printf("  ,' , \\_/ \\/ _/__\n");
printf(" /    _/ |--\\  `  `~,\n");
printf("' , ,/  /`\\ / `  `   `,\n");
printf("|    |  |  \\> `  `  ` |\n");
printf("|  ,  \\/ ' '    `  `  /\n");
printf("`,   '  '    ' `  '  /\n");
printf("  \\ `      '  ' ,  ,'\n");
printf("   \\ ` ` '    ,  ,/\n");
printf("    `,  `  '  , ,'\n");
printf("      \\ `  ,   /\n");        
printf("       `~----~'\n");
printf("\n\n");
	    printf("  3. Suspicious mushrooms\n");
printf("	   ------------\n");
printf("     /  (_)_   _    \\\n");
printf("  /)      (_) (_)      \\\n");
printf(" |       _          _   |\n");
printf("| _     (_)   _    (_) _ |\n");
printf("|(_)  _      (_)  _   (_)|\n");
printf("|____(_)_________(_)_____|\n");
printf(" \\\\\\\\\\||||||||///////\n");
printf("          |      |\n");
printf("          |      |\n");
printf("          |      |\n");
printf("           \\____/\n");
printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	do {
			printf("Will you continue to pick up ingredients?(Type 0 to quit, 1 to continue): ");
			choice = scanNum(0,1);
			if (choice == 0) { break; }
			if (ctr >= 3) { break; }  //The player can pick up 
								//at most 3 ingredients every turn
			printf("Please type the ingredients number: ");
			ing1 = scanNum(1,3);
			if (ing1 == 1) { addIngredients(ingBag, "Magic herbs"); }
			else if (ing1 == 2) { addIngredients(ingBag, "Butterfly wings"); }
		//More else if, if there're more types of ingredients
			else { addIngredients(ingBag, "Suspicious mushrooms"); }
			
		} while (ing1 >= 1 && ing1 <= 3);
}
	

/**
	Combat System Functions
**/
void battle(struct enemy * enem, struct player* player){
	/*neither the enemy nor the player is dead*/
	char potions_choice[100];
	int enemy_hurt, player_hurt;
	
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
	printf("\nA dangerous %s suddenly approaches you.\n", enem->name);

    if(strcmp(enem->name, "Titan Dragon")==0){   

    printf("                                                      \n");
    printf("                                                      \n");
    printf("                                                      \n");
printf("                    \\||/\n");
printf("                |  @___oo\n");
printf("      /\\  /\\   / (__,,,,|\n");
printf("     ) /^\\) ^\\/ _)\n");
printf("     )   /^\\/   _)\n");
printf("     )   _ /  / _)\n");
printf(" /\\  )/\\/ ||  | )_)\n");
printf("<  >      |(,,) )__)\n");
printf(" ||      /    \\)___)\n");
printf(" | \\____(      )___) )___\n");
printf("  \\______(_______;;; __;;;\n");
    }

    if(strcmp(enem->name, "Angry Bear")==0){
    printf("                                                      \n");
    printf("                                                      \n");
    printf("                                                      \n");
printf("     !!!!\n");
printf("  !!!!!!!!\n");
printf("!!!!!!!!!!!   O_O\n");
printf("!!!  !!!!!!! /@ @\\\n");
printf("      !!!!!! \\ x /\n");
printf("      !!!!!!/ m  !m\n");
printf("       !!!!|/  \\__\n");
printf("        !!!\\______\\\n");
    }




    if(strcmp(enem->name, "Tiny Slime")==0){
    printf("                                                      \n");
    printf("                                                      \n");
    printf("                                                      \n");
printf("     .      .\n");
printf("     |\\____/|\n");
printf("    (\\|----|/)\n");
printf("     \\ 0  0 /\n");
printf("      |    |\n");
printf("   ___/\\../\\____\n");
printf("  /     --       \\\n");
printf(" /  \\         /   \\\n");
printf("|    \\___/___/(   |\n");
printf("\\   /|  }{   | \\  )\n");
printf(" \\  ||__}{__|  |  |\n");
printf("  \\  |;;;;;;;\\  \\ / \\_______\n");
printf("   \\ /;;;;;;;;| [,,[|======'\n");
printf("     |;;;;;;/ |     /\n");
printf("     ||;;|\\   |\n");
printf("     ||;;/|   /\n");
printf("     \\_|:||__|\n");
printf("      \\ ;||  /\n");
printf("      |= || =|\n");
printf("      |= /\\ =|\n");
printf("      /_/  \\_\\\n");

    }
    
	while(enem->hp >0 && player->hp > 0){
		//do combat
		//Player Attack
		printf("Choose the potions to attack with below: \n");
		printf(".......................................................\n");
		printBSTree(player->potionsBag);
		printf("\nPlease type the potions name: \n");
		scanf("%s", potions_choice);
		if (strcmp(potions_choice, "fire") == 0) { 
			enemy_hurt = 50;
			enem->hp -= 50;
printf(".    _.-^^---....,,--\n");       
printf(" _--                  --_\n");  
printf("<                        >)\n");
printf("|                         |\n");
printf(" \\._                   _./\n");
printf("    ```--. . , ; .--'''\n");       
printf("          | |   |\n");             
printf("       .-=||  | |=-.\n");   
printf("       `-=#$%&%$#=-'\n");   
printf(" _____.,-#%&$@%#&#~,._____\n");
			printf("\nEnemy HP -%d\n Now the enemy HP: %d\n", enemy_hurt, enem->hp);
		}else if (strcmp(potions_choice, "Ice")==0){ 
			enemy_hurt = 30;
			enem->hp -= 30; 
printf("                ()\n");
printf("                /\\\n");
printf("               //\\\\n");
printf("              <<  >>\n");
printf("          ()   \\//   ()\n");
printf("()._____   /\\   \\   /\\   _____.()\n");
printf("   \\.--.\\ //\\ //\\ //\\ /.--./\n");
printf("    \\__\\/__\\//__\\//__\\/__//\n");
printf("        \\\\///\\//\\\\////\n");
printf("    ()-= >>\\< <\\> >\\<< =-()\n");
printf("        ////\\\\//\\///\\\\\n");
printf("    .--\\/--\\//--\\//--\\//--.\n");
printf("    //""/\\""//\\""//\"/\\""\\\n");
printf("   \'--'/ \\// \\/ \\// \'--'\\\n");
printf(" ()`''   /\\   //   \\/   `""""`()\n");
printf("          ()   //\\   ()\n");
printf("              <<  >>\n");
printf("              \\//\n");
printf("                \\/\n");
printf("                ()\n");			


			printf("\nEnemy HP -%d\n Now the enemy HP: %d\n", enemy_hurt, enem->hp);
		}else if(strcmp(potions_choice, "health")==0){
			player->hp += 50;
 printf("    ******       ******\n");
printf("   **********   **********\n");
printf(" ************* *************\n");
printf("*****************************\n");
printf("*****************************\n");
printf(" ***************************\n");
printf("   ***********************\n");
printf("     *******************\n");
printf("       ***************\n");
printf("         ***********\n");
printf("           *******\n");
printf("             ***\n");
printf("              *\n");
			printf("\nYour HP +50\n Now your HP: %d\n", player->hp);
		}else{ 
			printf("\nYou didn't grab a potion, but still managed to hit the enemy.\n");
			enemy_hurt = 20;
			enem->hp -= 20; 
		}
		removePotions(player->potionsBag, potions_choice);
		
		//This process means enemy attacks if they are still alive
		if(enem->hp>0){
			player_hurt = rand() % 101;
			player->hp -= player_hurt;
			printf("Your HP -%d\n Now your HP: %d\n", player_hurt, player->hp);
		}
		else {

			printf("    .... NO! ...                  ... MNO! ...\n");
			printf("   ..... MNO!! ...................... MNNOO! ...\n");
			printf(" ..... MMNO! ......................... MNNOO!! .\n");
			printf(".... MNOONNOO!   MMMMMMMMMMPPPOII!   MNNO!!!! .\n");
			printf(" ... !O! NNO! MMMMMMMMMMMMMPPPOOOII!! NO! ....\n");
			printf("    ...... ! MMMMMMMMMMMMMPPPPOOOOIII! ! ...\n");
			printf("   ........ MMMMMMMMMMMMPPPPPOOOOOOII!! .....\n");
			printf("   ........ MMMMMOOOOOOPPPPPPPPOOOOMII! ...\n");
			printf("    ....... MMMMM..    OPPMMP    .,OMI! ....\n");
			printf("     ...... MMMM::   o.,OPMP,.o   ::I!! ...\n");
			printf("         .... NNM:::.,,OOPM!P,.::::!! ....\n");
			printf("          .. MMNNNNNOOOOPMO!!IIPPO!!O! .....\n");
			printf("         ... MMMMMNNNNOO:!!:!!IPPPPOO! ....\n");
			printf("           .. MMMMMNNOOMMNNIIIPPPOO!! ......\n");
			printf("          ...... MMMONNMMNNNIIIOO!..........\n");
			printf("      ....... MN MOMMMNNNIIIIIO! OO ..........\n");
			printf("    ......... MNO! IiiiiiiiiiiiI OOOO ...........\n");
			printf("  ...... NNN.MNO! . O!!!!!!!!!O . OONO NO! ........\n");
			printf("   .... MNNNNNO! ...OOOOOOOOOOO .  MMNNON!........\n");
			printf("   ...... MNNNNO! .. PPPPPPPPP .. MMNON!........\n");
			printf("      ...... OO! ................. ON! .......\n");
			printf("         ................................\n");

			printf("You defeated the %s!\n", enem->name);
		}
	}
	
}

/***********************************************************
* Initialize Structs
************************************************************/
struct game* initGame()
{
    struct game* newGame = (struct game *)malloc(sizeof(struct game));
    newGame->enemies = initEnemies();
    newGame->player = initPlayer();
	//newGame->map = initMap();
	return newGame;
}
struct player* initPlayer()
{
	//Allocate and initialize player pointers
	struct player* newPlayer = (struct player*)malloc(sizeof(struct player));
	assert(newPlayer != NULL);

	newPlayer->hp = 100;

	newPlayer->ingredientsBag = newBSTree();
	assert(newPlayer->ingredientsBag != NULL);
	
	newPlayer->potionsBag = newBSTree();
	assert(newPlayer->potionsBag != NULL);

	init_Potions_Bag(newPlayer->potionsBag);
	
	return newPlayer;
}
//Enemies
struct Queue* initEnemies()
{
	struct Queue* newEnemyQueue = listQueueCreate();
	assert(newEnemyQueue != NULL);

	/* Add enemies here or add them later*/	
	setEnemies(newEnemyQueue);
	return newEnemyQueue;
}
struct enemy * createEnemy(int hp, int diff, char *name)
{
	struct enemy *newEnemy = (struct enemy*)malloc(sizeof(struct enemy));
	newEnemy->hp = hp;
	newEnemy->difficulty = diff;
	newEnemy->name = name;
	return newEnemy;
}
void setEnemies(struct Queue* q_enemy) {
	struct enemy* groups[3];

	groups[0] = createEnemy(30, 1, "Tiny Slime");
	groups[1] = createEnemy(50, 2, "Angry Bear");	
	groups[2] = createEnemy(100, 3, "Titan Dragon");
	
	for (int i = 0; i < 3; ++i) {
		printf("Adding enemy ");
		printf("%s \n", groups[i]->name);
		listQueueAddBack(q_enemy, groups[i]);
	}
}
void killEnemey(struct Queue* q_enemy) {
	free(listQueueRemoveFront(q_enemy));
}

/***********************************************************
* Deallocate Structs
************************************************************/
void deleteGame(struct game * newGame)
{
	deletePlayer(newGame->player);
	deleteEnemies(newGame->enemies);

	free(newGame);
	newGame = NULL;
}

void deletePlayer(struct player* playerIn)
{
	assert(playerIn != NULL);

	deleteBSTree(playerIn->ingredientsBag);
	deleteBSTree(playerIn->potionsBag);
	
	free(playerIn);
	playerIn = NULL;
}

void deleteEnemies(struct Queue* enemies)
{
	assert(enemies != NULL);
	while(listQueueIsEmpty(enemies) == 0)
		killEnemey(enemies);
	listQueueDestroy(enemies);
}