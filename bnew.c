/* This is the binary game's integration with the grid.  */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"

#define BYTE_L 8

int binResult(entity *byte[BYTE_L]);
/* creates a new bulb-switch pair */
entity *newBulb(cell grid[H][W], int x, int y);

int bgame (SDL_Simplewin *sw)
{
  cell grid[H][W];
  entity *player, *byte[BYTE_L];
  int in;
  int goal,res;

  initGrid(grid);
  /* place player */
  player = grid[6][6].foreground = newEntity(passable,'@',6,6);
  /* 8 lightbytes and 8 switches */
  byte[7] = newBulb(grid, 2, 1);
  byte[6] = newBulb(grid, 3, 1);
  byte[5] = newBulb(grid, 4, 1);
  byte[4] = newBulb(grid, 5, 1);
  byte[3] = newBulb(grid, 6, 1);
  byte[2] = newBulb(grid, 7, 1);
  byte[1] = newBulb(grid, 8, 1);
  byte[0] = newBulb(grid, 9, 1);
  /*layer of floortiles */
  fillGrid(grid);

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
      }
	  else if( grid[player->y][player->x].background != NULL
      &&  grid[player->y][player->x].background->type == '+') {
        changeEntity(grid[player->y][player->x].background,'-');
        updateEntities(grid);
        printGrid(grid);
      }
    }
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
  grid[y][x].background = newEntity(passable,'0',x,y);
  grid[y+3][x].background = newEntity(passable,'-',x,y+3);
  grid[y+3][x].background->pointsto = grid[y][x].background;

  return grid[y][x].background;
}
