#include "binaryGame.h"

int result(int byte[8]);

int binaryGame(void)
{
   int goal;
   int byte[8] = {1,0,1,0,0,0,1,0};
   srand((unsigned) time(&t));
   goal =rand()%255;
   printf("try summing %d\n", goal );
   printf("result%d\n", result(byte) );
   return(1);
}
int result(int byte[8])
{
   int i;
   float result=0.0;
   for(i=0;i<8;i++){
      result += pow( byte[i]*2, i);
   }
   return((int)result);
}
pull:
	git pull "https://github.com/ProjectElves/SoftwareEngineering" master
