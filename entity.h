#include "grid.h"

typedef enum ispassable { passable, impassable } ispassable;

struct entity {
  int x, y;
  int ispassable; /* walls cannot be walked through - floors can */
  char type; /* for display when printing grid to terminal */
  struct entity *pointsto; /* this allows for connections between entities -
  such as from a switch to a lightbulb */
};

/* changes the type of an entity (a char).  this type is used to check in
the action loop what actions to take*/
void changeEntity(entity *e, char newtype);

/* moves the foreground entity in direction dir */
// doesnt check passability yet - 22/11/15
void move(cell *c, int x, int y, direction dir, cell grid[H][W]);

/* call this to create a new entity.  uses malloc */
entity *newEntity(int ispassable, char type, int x, int y);

/* checks conditions and changes entities which need changing */
void updateEntities(cell grid[H][W]);

/* placeholder function to fill grid with floor entities */
void fillGrid(cell grid[H][W]);

/* frees the memory used by malloc in the newEntity() function*/
void freeEntityMem(cell grid[H][W]);

/* placeholder function to print grid to terminal.
only prints one layer of the grid */
void printGrid(cell grid[H][W]);

entity *newWall(cell grid[H][W], int x, int y);

void createBoundingWalls(cell grid[H][W]);
