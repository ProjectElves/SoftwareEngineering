<<<<<<< HEAD
#include "game.h"
=======
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "input.h"

#define H 12
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
void newBulb(cell grid[H][W], int x, int y);

/* placeholder function to fill grid with floor entities */
void fillGrid(cell grid[H][W]);

/* placeholder function to print grid to terminal.
only prints one layer of the grid */
void printGrid(cell grid[H][W]);

/* frees the memory used by malloc in the newEntity() function*/
void freeEntityMem(cell grid[H][W]);
>>>>>>> 87d4ce69c445bfe7316a1e37f08adf18640762a1

void testGrid(SDL_Simplewin *sw);

int gridmain(SDL_Simplewin *sw)
{
  testGrid(sw);
  return 0;
}

void initGrid(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<H; WCnt++){
      grid[HCnt][WCnt].foreground = NULL;
      grid[HCnt][WCnt].background = NULL;
      /* initialise the grid cells to contain no entities */
    }
  }
}

void freeEntityMem(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<H; WCnt++){
      if (grid[HCnt][WCnt].foreground != NULL) {
        free(grid[HCnt][WCnt].foreground);
      }
      if (grid[HCnt][WCnt].background != NULL) {
        free(grid[HCnt][WCnt].background);
      }
    }
  }
  initGrid(grid);
}

entity *newEntity(int ispassable, char type, int x, int y)
{
  entity *e = malloc(sizeof(entity));
  e-> x = x;
  e-> y = y;
  e->type = type;
  e->ispassable = ispassable;
  return e;
}

entity *newBulb(cell grid[H][W], int x, int y)
{
  grid[y][x].background = newEntity(passable,'0',x,y);
  grid[y+3][x].background = newEntity(passable,'-',x,y+3);
  grid[y+3][x].background->pointsto = grid[y][x].background;
  
  return grid[y][x].background;
}

cell *getNeighbour(int x, int y, direction dir, cell grid[H][W])
{
  int px, py;
  cell *c;

  px = x;
  py = y;

  directionsTrans(dir,&px,&py);
  c = &grid[py][px];

  return c;
}

void directionsTrans(direction dir, int *x, int *y)
{
  switch(dir){
    case LEFT:
      (*x)--;
      break;
    case RIGHT:
      (*x)++;
      break;
    case UP:
      (*y)--;
      break;
    case DOWN:
      (*y)++;
      break;
  }
}

void changeEntity(entity *e, char newtype)
{
  e->type = newtype;
}

void updateEntities(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){

      /* logic for lighbulbs and switches */
      if (grid[HCnt][WCnt].background != NULL /*is there an object */
      &&  grid[HCnt][WCnt].background->pointsto != NULL) { /*is switch connected */
        /*is the object an on switch */
        if (grid[HCnt][WCnt].background->type == '+') {
          changeEntity(grid[HCnt][WCnt].background->pointsto,'1');
        }
        /*is the object an off switch */
        if (grid[HCnt][WCnt].background->type == '-') {
          changeEntity(grid[HCnt][WCnt].background->pointsto,'0');
        }
      }
    }
  }
}

void move(cell *c, int x, int y, direction dir, cell grid[H][W]) {
  cell *cnew = getNeighbour(x,y,dir,grid);
  int px, py;

  px = x;
  py = y;

  directionsTrans(dir,&px,&py);
  c->foreground->x = px;
  c->foreground->y = py;

  cnew->foreground = c->foreground;
  c->foreground = NULL;
}


void printGrid(cell grid[H][W])
{
  int HCnt, WCnt;
  
  printf("\n");
  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      if (grid[HCnt][WCnt].foreground != NULL) {
        printf("%c ", grid[HCnt][WCnt].foreground->type);
      }
      else if (grid[HCnt][WCnt].background != NULL) {
        printf("%c ", grid[HCnt][WCnt].background->type);
      }
    }
    printf("\n");
  }
}

void fillGrid(cell grid[H][W])
{
  int HCnt, WCnt;
  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      if (grid[HCnt][WCnt].background == NULL) {
        grid[HCnt][WCnt].background = newEntity(0,'.',WCnt,HCnt);
      }
    }
  }
}


void testGrid(SDL_Simplewin *sw) {
  /* these vars are only for the tests */
  int i, in, rc, rp;
  cell *tmp;
  entity *player;

  srand(time(NULL));

  cell grid[H][W];
  initGrid(grid);
  /* foreground layer test */
  player = grid[6][6].foreground = newEntity(passable,'@',6,6);
  /* lightbulbs and switches */
  newBulb(grid, 2, 1);
  newBulb(grid, 3, 1);
  newBulb(grid, 4, 1);
  newBulb(grid, 5, 1);
  newBulb(grid, 6, 1);
  newBulb(grid, 7, 1);
  newBulb(grid, 8, 1);
  newBulb(grid, 9, 1);

  fillGrid(grid);

  printGrid(grid);

  /* test for switches and connectivity with objects */
  for(i = 0; i < 10; i++) {
    rp = rand()%2;
    rc = (rand()%8) + 2;

    grid[4][rc].background->pointsto = grid[1][rc].background;
    if (rp == 1) {
      changeEntity(grid[4][rc].background,'+');
    }
    if (rp == 0) {
      changeEntity(grid[4][rc].background,'-');
    }

    printf("\nNEXTEST:\n\nswitch %d has changed to %d\n", rc-1,rp);
    grid[4][rc].background->pointsto = grid[1][rc].background;
    updateEntities(grid);

    printf("\nbulb %d has changed to %d\n", rc-1, rp);

    printGrid(grid);
  }

  /*foreground test and move test */

  while(!sw->finished){
    in=input(sw);
    if(in!=0){
       printf("INPUT RECIEVED (GRID): %d",in);
       move(&grid[player->y][player->x],player->x,player->y,in,grid);
       printGrid(grid);
    }
}

  /*getNeighbour test */
  tmp = getNeighbour(2,6,RIGHT,grid);
  if (tmp->foreground != NULL) {
    printf("\n\nCHAR:%c\n\n",tmp->foreground->type);
  }

  freeEntityMem(grid);
}


