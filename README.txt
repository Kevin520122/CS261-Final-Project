Group Members: 
    Garrett Scott
    Jerred Shifflett
    Shelby Westerberg
    Shilong Zhao

Description:
    Battle monsters (stored in Queue) with potions (stored Binary Search Tree)
    crafted by ingredients(stored in Binary Search Tree).

	ADT Choice
		Queue - Allowed monsters to be battled sequentially with FIFO property
		Binary Search Tree - Fast searching for ingredients/potions

Game Menu:
    1. Battle
    2. Pick up Ingredients
    3. Make Potions
    4. Display Ingredients Bag
    5. Display Portions Bag
    6. Quit

COMPILE: make
RUN: ./start


Projct Outline:
    Abstract Data Types:
        bst.c
        bst.h
            compare.c

        queue.c
        queue.h

        Structs handled by bst or queue:
            structs.h
                items
                enemy

    Game:
        game.h
        game.c
            Additional Structs:
                player
                game

    Run the game:
        start.c



game.h & game.c
    Interface and implementation for the game.
    Where everything comes together.


start.c
    Only starts the game.

