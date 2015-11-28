#include <stdio.h>
#include "game.h"

SDL_Simplewin sw;
SDL_Simplewin *swin;

int main(int argc, char **argv)
{
  Nikos_SDL_Init(&sw);
   int select;
   if(argc==2){
      select = atoi(argv[1]);
   }
   else{
   printf("1.Binary Game\n");
   printf("2.Encryption Game\n");
   printf("3.Test Grid\n");
   printf("4.Test input\n");
   printf("5.Binary game/grid integration\n");
   }
   select=2;
   swin=&sw;
switch (select) {
  case 1:
     if(binaryGame()==1){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;
  case 2:
     if(encryptionNew(swin)==0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;
  case 3:
     if(gridmain(swin)==0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;
  case 4:
     if(input(swin)!=0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;
  case 5:
     if(bgame(swin)!=0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;

}

SDL_Quit();
printf("\n\n");
return(0);
}
