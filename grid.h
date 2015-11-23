#include <stdlib.h>
#include <stdio.h>
#include <time.h>

<<<<<<< HEAD
#define H 14
=======
#define H 12
>>>>>>> 87d4ce69c445bfe7316a1e37f08adf18640762a1
#define W 12

typedef enum direction { LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 } direction;
typedef enum layer { background, foreground } layer;
typedef enum ispassable { passable, impassable } ispassable;

typedef struct entity {
  int x, y;
  int ispassable; /* walls cannot be walked through - floors can */
  char type; /* for display when printing grid to terminal */
  struct entity *pointsto; /* this allows for connections between entities -
  such as from a switch to a lightbulb */
} entity;

/* this and other entity-related stuff could probably be moved
to an entity.c file */

typedef struct cell {
  /* i have simplified the cells of the grid to just contain 2 possible
  entities - one at the front and one at the back.
  this should make it much simpler to add a new object*/
  entity *foreground; /*this is the foreground object - eg, the player, walls */
  entity *background; /*this is the background object - eg, the floor, a switch, a lightbulb, a wire */
} cell;

void directionsTrans(direction dir, int *x, int *y);

/* changes the type of an entity (a char).  this type is used to check in
the action loop what actions to take*/
void changeEntity(entity *e, char newtype);

/* returns a pointer to the neighbouring cell in direction dir */
cell *getNeighbour(int x, int y, direction dir,  cell grid[H][W]);

/* moves the foreground entity in direction dir */
void move(cell *c, int x, int y, direction dir, cell grid[H][W]);

/* sets listmax to zero in all cells - i.e. makes them empty */
void initGrid(cell grid[H][W]);

/* call this to create a new entity.  uses malloc */
entity *newEntity(int ispassable, char type, int x, int y);

/* creates a new bulb-switch pair */
<<<<<<< HEAD
entity *newBulb(cell grid[H][W], int x, int y);
=======
void newBulb(cell grid[H][W], int x, int y);
>>>>>>> 87d4ce69c445bfe7316a1e37f08adf18640762a1

/* placeholder function to fill grid with floor entities */
void fillGrid(cell grid[H][W]);

/* placeholder function to print grid to terminal.
only prints one layer of the grid */
void printGrid(cell grid[H][W]);

/* frees the memory used by malloc in the newEntity() function*/
void freeEntityMem(cell grid[H][W]);

<<<<<<< HEAD
/* checks conditions and changes entities which need changing */
void updateEntities(cell grid[H][W]);

=======
void testGrid(SDL_Simplewin *sw);
>>>>>>> 87d4ce69c445bfe7316a1e37f08adf18640762a1
