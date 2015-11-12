#include "input.h"
#include "grid.h"

int grid(SDL_Simplewin *sw)
{
  srand(time(NULL));
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
      free(grid[HCnt][WCnt].foreground);
      free(grid[HCnt][WCnt].background);
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

void newBulb(cell grid[H][W], int x, int y)
{
  grid[y][x].background = newEntity(passable,'0',x,y);
  grid[y+3][x].background = newEntity(passable,'-',x,y+3);
  grid[y+3][x].background->pointsto = grid[y][x].background;
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
    for(WCnt=0; WCnt<H; WCnt++){

      /* logic for lighbulbs and switches */
      if (grid[HCnt][WCnt].background != NULL /*is there an object */
      &&  grid[HCnt][WCnt].background->pointsto != NULL) { /*is switch connected */
        /*is the object an off switch */
        if (grid[HCnt][WCnt].background->type == '+') {
          changeEntity(grid[HCnt][WCnt].background->pointsto,'1');
        }
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


void testGrid(SDL_Simplewin *sw) {
  /* these vars are only for the tests */
  int i, in, rc, rp;
  cell *tmp;
  entity *player;

  /* this is the grid */
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
