#include "encryption.h"



int encryptionNew(Display *sw)
{
  char *list[] = {"frondo", "gandalf","elrond", "legolas", "gimli", "aragorn","saouron"};

  char rand_word[LENGTH], shuffle_word[LENGTH], original_word[LENGTH];
  int i, word_size, j, yinit = H/2, xinit = 2, cnt=0, game;
  cell grid[H][W];
  entity *player;
  int in;
  initGrid(grid);

  srand(time(NULL));
  if (sscanf(list[(rand()%LIST_SIZE)], "%s", rand_word) != 1){
    printf("couldn't get a word from the list\n");
    return 1;
  }
  word_size = strlen(rand_word);
  for (i=0; i<word_size; i++){
    shuffle_word[i] = rand_word[i];
  }
  shuffle_word[word_size] = '\0';
  // printf("\nThe initial word is %s and ", shuffle_word);
  game = enc_shufle(shuffle_word, word_size);
  // printf("%s\n", shuffle_word);
  strcpy(original_word, shuffle_word);
  // printf("%s\n",original_word );
  player = grid[6][6].foreground = newEntity(passable,'@',6,6);
  /* place the word in the grid */
  for (j=0; j<word_size; j++){
    enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
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

  grid[yinit][xinit-1].background = newEntity(passable,'<',xinit-1,yinit);
  grid[yinit][xinit + word_size].background = newEntity(passable,'>',xinit + word_size, yinit);
  grid[8][1].background = newEntity(passable,'r',8,1);
  grid[8][9].background = newEntity(passable,'H',8,9);



  printf("try to find the correct word");

  /* MAIN LOOP */
  while(!sw->finished){
    char hint0[]="vowel(s)"; //variables have to be declared here otherwise dont work
    char hint1[]="consonant(s)";
    char hint2[]="whole row";
    char reset[]="reset";

    printf("%s", hint1);

    in=input(sw);
    for (j=0; reset[j]!='\0'; j++){ //makes reset dissappear if set
      grid[2][j].background = newEntity(passable, '.', j, 2);
    }
   if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
      move(&grid[player->y][player->x],player->x,player->y,in,grid);
      printGrid(grid);
   }
   if (in == 9) { /*checks for spacebar */
      if(grid[player->y][player->x].background->type == 'v') {
        enc_updateLetter(grid, player->y, player->x);
      }
      else if(grid[player->y][player->x].background->type == '^') {
         enc_updateLetter(grid, player->y, player->x);
      }
      else if(grid[player->y][player->x].background->type == '>') {
         enc_changeRow(shuffle_word, word_size, -1);
         for (j=0; j<word_size; j++){
           enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
         }
      }
      else if(grid[player->y][player->x].background->type == '<') {
         enc_changeRow(shuffle_word, word_size, 1);
         for (j=0; j<word_size; j++){
           enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
         }
      }
      else if(grid[player->y][player->x].background->type == 'r') {
         for (i=0; i<word_size; i++){
            enc_newLetter(grid, xinit+i, yinit, original_word[i]);
         }
         for (j=0; reset[j]!='\0'; j++){
            grid[1][j+2].background = newEntity(passable, reset[j], j, 2);
         }
      }
      else if(grid[player->y][player->x].background->type == 'H') {
        switch (game){
         case 0:
         for (j=0; hint1[j]!='\0'; j++){
           grid[2][j+2].background = newEntity(passable, hint0[j], j, 3);
           }
           break;
         case 1 :
         for (j=0; hint1[j]!='\0'; j++){
           grid[2][j+2].background = newEntity(passable, hint1[j], j, 3);
           }
           break;
         case 2 :
         for (j=0; hint1[j]!='\0'; j++){
           grid[2][j+2].background = newEntity(passable, hint2[j], j, 3);
           }
           break;
         }
      }
   }

   enc_updateWord(grid, yinit, xinit, shuffle_word);
   printGrid(grid);
   // printf("shuffle: %s\n",shuffle_word);
   // printf("original: %s\n",original_word);
   // I pass the letter of the collum I'm in
   drawEntities(sw, grid);
   drawFrame(sw, 20);
   enc_print_ascii(grid[yinit][player->x].background->type);
   if(strcmp(shuffle_word, rand_word)==0){
      break;
   }
    cnt++;
   }
  printf("you win in %d moves\n", cnt);
  freeEntityMem(grid);  /* free memory */
  return 0;
}


void enc_print_ascii(char letter){
   if ((letter < 'a') || (letter > 'z')){
      printf("ascii code: %c\n",' ' );
   }
   else{
   printf("ascii code: %d\n", letter);
   }
}

void enc_Hint(int game){
   switch (game){
     case 0:
       printf("change a vowel\n\n");
       break;
     case 1 :
       printf("change a constant\n\n" );
       break;
     case 2 :
       printf("switch the whole row\n\n" );
       break;
   }
}

void enc_updateWord(cell grid[H][W], int y, int x, char shuffle[LENGTH]){

    int i=0, size=strlen(shuffle);

   for( ; x<size; x++){
      shuffle[i++] = grid[y][x].background->type;
   }
}

void enc_updateLetter(cell grid[H][W], int y, int x){

   if ((grid[y][x].background->type == 'v') &&
      (grid[y][x].background->pointsto != NULL)) {// cause 'v' may be from the word
     enc_letterDown(grid[y][x].background->pointsto);
   }
   // we don't have && cause '^' is surely not part of the word
   if (grid[y][x].background->type == '^'){
     enc_letterUp(grid[y][x].background->pointsto);
   }
}

void enc_letterDown(entity *e){
   int letter = (int) e->type;

   if( letter == (int) 'a'){
      letter += 25;
      e->type = (char) letter;
   }
   else{
      letter--;
      e->type = (char) letter;
   }
}

void enc_letterUp(entity *e){
   int letter = (int) e->type;

   if( letter == (int) 'z'){
      letter -= 25;
      e->type = (char) letter;
   }
   else{
      letter++;
      e->type = (char) letter;
   }
}

void enc_newLetter(cell grid[H][W], int x, int y, char c){
  grid[y][x].background = newEntity(passable, c, x, y);
  grid[y-1][x].background = newEntity(passable,'^',x,y-1);
  grid[y-1][x].background->pointsto = grid[y][x].background;
  grid[y+1][x].background = newEntity(passable,'v',x,y-1);
  grid[y+1][x].background->pointsto = grid[y][x].background;
}

int enc_shufle(char word[LENGTH], int size){
  int game ;

  game = rand()%3;
  switch (game){
    case 0:
      // printf("we are going to change a vowel\n\n");
      enc_change(word, size, game);
      break;
    case 1 :
      // printf("we are going to change a constant\n\n" );
      enc_change(word, size, game);
      break;
    case 2 :
      // printf("we are going to switch the whole row\n\n" );
      enc_changeRow(word, size, 0);
      break;
  }
  return game;
}

void enc_changeRow(char word[LENGTH], int size, int shift){
  int i;
  if(shift==0){
  shift = rand()%(ALPHABET-1)+1;
  // printf("shift = %d\n", shift);
 }
  for (i=0; i<size; i++){
    word[i] = word[i] - shift;
    if ((int)word[i] > (int) 'z'){
      word[i] = word[i] - ALPHABET;
    }
    else if ((int)word[i] < (int) 'a'){
      word[i] = word[i] + ALPHABET;
    }
  }
}

void enc_change(char word[LENGTH], int size, int game){
  int condition=TRUE, letter, i;
  char c;

  do {
    if (game == 0){
      letter = rand()%size; /* pick random letter*/
      if(enc_isenc_vowel(word[letter])){ /* see if the letter is a enc_vowel*/
        if((c=enc_vowel()) != word[letter]){ /* see if the enc_vowel is different of the on I had */
          for (i=0; i<size; i++){
            if (word[i] == word[letter]){ /* I want to check if there are more */
              word[i] = c;                /* than one same letters in my initial word */
              condition = FALSE;
            }
          }
        }
      }
    }
    else if (game == 1 ){
      letter = rand()%size; /* same here  */
      if(enc_isenc_vowel(word[letter]) == 0){
        if((c=enc_constant()) != word[letter]){
          for (i=0; i<size; i++){
            if (word[i] == word[letter]){
              word[i] = c;
              condition = FALSE;
            }
          }
        }
      }
    }
  } while (condition);
}

int enc_isenc_vowel(char c){
  c=tolower(c);
  if ((c=='a') || (c=='e') || (c=='u') || (c=='o') || (c=='i')){
	return 1;
  }
  else{
    return 0;
  }
}

char enc_vowel(){
  char letter[] = {'a','e','i','o','u'};
  return letter[rand()%5];
}

char enc_constant(){
  char letter[] = {'b','c','d','f','g','h','j','k','l','m','n','p','q',
                    'r','s','t','v','w','x','y','z'};
  return letter[rand()%21];
}
