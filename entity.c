#include "entity.h"

entity *newEntity(int ispassable, char type, int x, int y)
{
  entity *e = (entity *)malloc(sizeof(entity));
  e-> x = x;
  e-> y = y;
  e->type = type;
  e->ispassable = ispassable;
  return e;
}

void changeEntity(entity *e, char newtype)
{
  e->type = newtype;
}

void changePassable(entity *e, int ispassable) {
  e->ispassable = ispassable;
}


void delEntity(entity *e)
{
  free(e);
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

  if (cnew->background->ispassable == impassable) {
    return;
  }
  int px, py;

  px = x;
  py = y;
  
  if (isEdge(px,py)) {
    return;
  }
  directionsTrans(dir,&px,&py);
  c->foreground->x = px;
  c->foreground->y = py;

  cnew->foreground = c->foreground;
  c->foreground = NULL;
}

int isEdge(int x, int y) {
  if ( x > (w - 1)) {
    return 1;
  }
  if ( x < 0) {
    return 1;
  }
  if ( y > (W - 1)) {
    return 1;
  }
  if ( y < 0) {
    return 1;
  }
  return 0;
}

int next_movment(int count, int *in_prev, int in){

   if( in == *in_prev){// same arrow key
      count++;
   }// we are going to use 'count' for moving animation inside the updatePlayerfacing function
   else if( in != *in_prev ){// different arrow key
      *in_prev = in;
      count = 0;
   }
   return count;
}

void updatePlayerfacing(entity *player, direction in, int count)
{
  switch(in){
    case LEFT:
       if (count % 3 == 0){  changeEntity(player,'L'); }
       if (count % 3 == 1){  changeEntity(player,'{'); }
       if (count % 3 == 2){  changeEntity(player,'('); }
       break;
    case RIGHT:
      if (count % 3 == 0){  changeEntity(player,'R'); }
      if (count % 3 == 1){  changeEntity(player,'}'); }
      if (count % 3 == 2){  changeEntity(player,')'); }
      break;
    case UP:
       if (count % 3 == 0){  changeEntity(player,'U'); }
       if (count % 3 == 1){  changeEntity(player,';'); }
       if (count % 3 == 2){  changeEntity(player,':'); }
       break;
    case DOWN:
       if (count % 3 == 0){  changeEntity(player,'D'); }
       if (count % 3 == 1){  changeEntity(player,'/'); }
       if (count % 3 == 2){  changeEntity(player,'?'); }
       break;
  }
}

void freeEntityMem(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
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


entity *newWall(cell grid[H][W], int x, int y)
{
  grid[y][x].background = newEntity(impassable,'#',x,y);
  return grid[y][x].background;
}
entity *newLimit(cell grid[H][W], int x, int y)
{
  grid[y][x].background = newEntity(impassable,'.',x,y);
  return grid[y][x].background;
}


void createBoundingWalls(cell grid[H][W])
{
  int i;
  // Outside walls
  for (i = 0; i < W; i++) {
    newWall(grid, i, 0);
  }
  for (i = 0; i < W; i++) {
    newWall(grid, i, H-1);
  }
  for (i = 1; i < H-1; i++) {
    newWall(grid, 0, i);
  }
  for (i = 1; i < H-1; i++) {
    newWall(grid, W-1, i);
  }
}
