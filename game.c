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
   loadPhoto(d, "images/chars/a.bmp", 'a');
   loadPhoto(d, "images/chars/b.bmp", 'b');
   loadPhoto(d, "images/chars/c.bmp", 'c');
   loadPhoto(d, "images/chars/d.bmp", 'd');
   loadPhoto(d, "images/chars/e.bmp", 'e');
   loadPhoto(d, "images/chars/f.bmp", 'f');
   loadPhoto(d, "images/chars/g.bmp", 'g');
   loadPhoto(d, "images/chars/h.bmp", 'h');
   loadPhoto(d, "images/chars/i.bmp", 'i');
   loadPhoto(d, "images/chars/j.bmp", 'j');
   loadPhoto(d, "images/chars/k.bmp", 'k');
   loadPhoto(d, "images/chars/l.bmp", 'l');
   loadPhoto(d, "images/chars/m.bmp", 'm');
   loadPhoto(d, "images/chars/n.bmp", 'n');
   loadPhoto(d, "images/chars/o.bmp", 'o');
   loadPhoto(d, "images/chars/p.bmp", 'p');
   loadPhoto(d, "images/chars/q.bmp", 'q');
   loadPhoto(d, "images/chars/r.bmp", 'r');
   loadPhoto(d, "images/chars/s.bmp", 's');
   loadPhoto(d, "images/chars/t.bmp", 't');
   loadPhoto(d, "images/chars/v.bmp", 'v');
   loadPhoto(d, "images/chars/u.bmp", 'u');
   loadPhoto(d, "images/chars/w.bmp", 'w');
   loadPhoto(d, "images/chars/x.bmp", 'x');
   loadPhoto(d, "images/chars/y.bmp", 'y');
   loadPhoto(d, "images/chars/z.bmp", 'z');
   loadPhoto(d, "images/RArrow.bmp", '>');
   loadPhoto(d, "images/LArrow.bmp", '<');
   loadPhoto(d, "images/DArrow.bmp", '$');
   loadPhoto(d, "images/UArrow.bmp", '^');
   loadPhoto(d, "images/onlight.bmp", '&');





   int select;
   if(argc==2){
      select = atoi(argv[1]);
   }
   else{
  //  printf("1.Binary Game\n");
   printf("2.Encryption Game\n");
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
   case 2:
      if(encryptionNew(d)==0){printf("everything OK\n");}
      else{printf("ERROR \n");}
      break;
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
