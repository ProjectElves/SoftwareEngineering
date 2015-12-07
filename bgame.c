/* This is the binary game's integration with the grid.  */
#include "bgame.h"

int bgame (Display *sw)
{
  cell grid[H][W];
  entity *player, *byte[BYTE_L];
  int in, i, j;
  int goal,res;

  initGrid(grid);
  /* place player */
  player = grid[6][6].foreground = newEntity(passable,'@',6,6);
  /* 8 lightbytes and 8 switches */

  for (i = BYTE_L, j = (W / 2) - (BYTE_L / 2); i > 0; i--, j++) {
    byte[i-1] = newBulb(grid, j, 1);
  }

  // Dividing wall
  for (i = 1; i < W - 1; i++) {
    newWall(grid, i, 3);
  }

  // Creates the boundary walls
  createBoundingWalls(grid);

  /* layer of floortiles */
  fillGrid(grid);

  drawEntities(sw, grid);
  drawFrame(sw, 20);

  goal = rand()%255;
  printf("try summing %d\n", goal );
  printf("result: %d\n", binResult(byte) );

  /* MAIN LOOP */
	while(!sw->finished){
    in=input(sw);

    if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
      move(&grid[player->y][player->x],player->x,player->y,in,grid);
      printGrid(grid);
    }
    if (in == 9) { /*checks for spacebar */
      if( grid[player->y][player->x].background != NULL
      &&  grid[player->y][player->x].background->type == '-') {
        changeEntity(grid[player->y][player->x].background,'+');
        updateEntities(grid);
        printGrid(grid);
        //Mix_PlayChannel( -1, sw->zap, 0 );
      }
	  else if( grid[player->y][player->x].background != NULL
      &&  grid[player->y][player->x].background->type == '+') {
        changeEntity(grid[player->y][player->x].background,'-');
        updateEntities(grid);
        printGrid(grid);
        //Mix_PlayChannel( -1, sw->zap, 0 );
      }
    }
    drawEntities(sw, grid);
    drawFrame(sw, 20);
    res=binResult(byte);
    printf("result %d\n",res);
    if(res==goal){
      break;
    }
  }

  printf("you win\n");
	freeEntityMem(grid);  /* free memory */
  return 0;
}

int binResult(entity *byte[BYTE_L])
{
  int i;
  float result=0.0;
  for( i = 0; i < BYTE_L; i++){
    /*Exception for first bit 0=0*/
    if(i==0 && byte[0]->type=='0'){
      result=0;
    }
    else if (byte[i]->type == '1') {
      result += pow( 2, i);
    }
  }
  return((int)result);
}

entity *newBulb(cell grid[H][W], int x, int y)
{
  grid[y][x].background = newEntity(impassable,'0',x,y);
  grid[y+3][x].background = newEntity(passable,'-',x,y+3);
  grid[y+3][x].background->pointsto = grid[y][x].background;

  return grid[y][x].background;
}
