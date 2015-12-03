#include "base.h"

typedef enum direction { LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 } direction;
typedef enum layer { background, foreground } layer;

struct cell {
  /* i have simplified the cells of the grid to just contain 2 possible
  entities - one at the front and one at the back.
  this should make it much simpler to add a new object*/
  entity *foreground; /*this is the foreground object - eg, the player, walls */
  entity *background; /*this is the background object - eg, the floor, a switch, a lightbulb, a wire */
};

void directionsTrans(direction dir, int *x, int *y);

/* sets listmax to zero in all cells - i.e. makes them empty */
void initGrid(cell grid[H][W]);

/* returns a pointer to the neighbouring cell in direction dir */
cell *getNeighbour(int x, int y, direction dir,  cell grid[H][W]);
