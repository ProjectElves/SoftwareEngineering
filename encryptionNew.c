/*new encrytion game encorpoprating the grid
tasks -
1. generate single random word
2. generate the grid
3. bring word into the grid
4. bring in movement to the grid
5. make movement change the word
 */
#include "encryption.h"
#include "game.h"

void enc_shufle(char word[LENGTH], int size);
int enc_isenc_vowel(char c);
char enc_vowel();
char enc_constant();
void enc_changeRow(char word[LENGTH], int size);
void enc_change(char word[LENGTH], int size, int game);
void encrytionGridInit(char *shuffle_word);
entity *enc_newLetter(cell grid[H][W], int x, int y, char c);



int encryptionNew(SDL_Simplewin *sw)
{
  char *list[] = {"frondo", "gandalf","elrond", "legolas", "gimli", "aragorn","saouron"};
  char rand_word[LENGTH], shuffle_word[LENGTH];
  int i, word_size, j, yinit = H/2, xinit = 1;
  cell grid[H][W];
  entity *player, *byte[BYTE_L];
  int in, goal, res;
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
  printf("\nThe initial word is %s and ", shuffle_word);
  enc_shufle(shuffle_word, word_size);
  printf("%s\n", shuffle_word);

  player = grid[10][10].foreground = newEntity(passable,'@',10,10);
  /* 8 lightbytes and 8 switches */
  for (j=0; j<word_size; j++){
    byte[j] = enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
  }
  /*layer of floortiles */
  fillGrid(grid);
  goal = rand()%255;
  printf("try summing %d\n", goal );
  //printf("result: %d\n", binResult(byte) );

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
    // res=binResult(byte);
    // printf("result %d\n",res);
    if(res==goal){
      break;
    }
  }

  printf("you win\n");
  freeEntityMem(grid);  /* free memory */

  return 0;
}

entity *enc_newLetter(cell grid[H][W], int x, int y, char c){
  grid[y][x].background = newEntity(passable, c, x, y);
  grid[y-1][x].background = newEntity(passable,'^',x,y-1);
  grid[y-1][x].background->pointsto = grid[y][x].background;
  grid[y+1][x].background = newEntity(passable,'v',x,y-1);
  grid[y+1][x].background->pointsto = grid[y][x].background;
}

void enc_shufle(char word[LENGTH], int size){
  int game ;

  game = rand()%2;
  switch (game){
    case 0:
      printf("we are going to enc_change a enc_vowel\n\n");
      enc_change(word, size, game);
      break;
    case 1 :
      printf("we are going to enc_change a enc_constant\n\n" );
      enc_change(word, size, game);
      break;
    case 2 :
      printf("we are going to switch the whole row\n\n" );
      enc_changeRow(word, size);
      break;
  }
}

void enc_changeRow(char word[LENGTH], int size){
  int shift, i;

  shift = rand()%ALPHABET;
  for (i=0; i<size; i++){
    word[i] = word[i] - shift;
    if ((int)word[i] < (int) 'a'){
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
