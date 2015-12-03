#include <stdio.h>
#include "game.h"

int main(int argc, char **argv)
{
   Display *d = newDisplay();
   loadPhoto(d, "images/floor.bmp", '.');
   loadPhoto(d, "images/offlight.bmp", '0');
   loadPhoto(d, "images/onlight.bmp", '1');
   loadPhoto(d, "images/offswitch.bmp", '-');
   loadPhoto(d, "images/onswitch.bmp", '+');
   loadPhoto(d, "images/Red_Elf_Front.bmp", '@');

   int select;
   if(argc==2){
      select = atoi(argv[1]);
   }
   else{
  //  printf("1.Binary Game\n");
  //  printf("2.Encryption Game\n");
  //  printf("3.Test Grid\n");
   printf("4.Test input\n");
   printf("5.Binary game/grid integration\n");
   scanf("%d", &select );
   }
switch (select) {
  // case 1:
  //    if(binaryGame()==1){printf("everything OK\n");}
  //    else{printf("ERROR \n");}
  //    break;
  // case 2:
  //    if(encryption()==0){printf("everything OK\n");}
  //    else{printf("ERROR \n");}
  //    break;
  // case 3:
  //    if(gridmain(swin)==0){printf("everything OK\n");}
  //    else{printf("ERROR \n");}
  //    break;
  case 4:
     if(input(d)!=0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;
  case 5:
     if(bgame(d)!=0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;

}

closeDisplay(d);
printf("\n\n");
return(0);
}
