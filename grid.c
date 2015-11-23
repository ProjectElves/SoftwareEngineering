#include "grid.h"

void testGrid();

int gridmain()
{
  // testGrid();
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

// void testGrid() {
//   /* these vars are only for the tests */
//   int i, in, rc, rp;
//   cell *tmp;
//   entity *player;
//
//   srand(time(NULL));
//
//   cell grid[H][W];
//   initGrid(grid);
//   /* foreground layer test */
//   player = grid[6][6].foreground = newEntity(passable,'@',6,6);
//   /* lightbulbs and switches */
//   newBulb(grid, 2, 1);
//   newBulb(grid, 3, 1);
//   newBulb(grid, 4, 1);
//   newBulb(grid, 5, 1);
//   newBulb(grid, 6, 1);
//   newBulb(grid, 7, 1);
//   newBulb(grid, 8, 1);
//   newBulb(grid, 9, 1);
//
//   fillGrid(grid);
//
//   printGrid(grid);
//
//   /* test for switches and connectivity with objects */
//   for(i = 0; i < 10; i++) {
//     rp = rand()%2;
//     rc = (rand()%8) + 2;
//
//     grid[4][rc].background->pointsto = grid[1][rc].background;
//     if (rp == 1) {
//       changeEntity(grid[4][rc].background,'+');
//     }
//     if (rp == 0) {
//       changeEntity(grid[4][rc].background,'-');
//     }
//
//     printf("\nNEXTEST:\n\nswitch %d has changed to %d\n", rc-1,rp);
//     grid[4][rc].background->pointsto = grid[1][rc].background;
//     updateEntities(grid);
//
//     printf("\nbulb %d has changed to %d\n", rc-1, rp);
//
//     printGrid(grid);
//   }
//
//   /*foreground test and move test */
//
//   while(!){
//     in=1;
//     if(in!=0){
//        printf("INPUT RECIEVED (GRID): %d",in);
//        move(&grid[player->y][player->x],player->x,player->y,in,grid);
//        printGrid(grid);
//     }
// }
//
//   /*getNeighbour test */
//   tmp = getNeighbour(2,6,RIGHT,grid);
//   if (tmp->foreground != NULL) {
//     printf("\n\nCHAR:%c\n\n",tmp->foreground->type);
//   }
//
//   freeEntityMem(grid);
// }
