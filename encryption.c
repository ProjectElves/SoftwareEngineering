/*next steps
1. implemnet the grid
2. implement key presses with SDL
3. test if everything works*/
#include "encryption.h"

#define GRIDSIZE 10

void enc_shufle(char word[LENGTH], int size);
int enc_isenc_vowel(char c);
char enc_vowel();
char enc_constant();
void enc_changeRow(char word[LENGTH], int size);
void enc_change(char word[LENGTH], int size, int game);
void enc_printGrid(char grid[GRIDSIZE][GRIDSIZE]);
void enc_gridInit(char grid[GRIDSIZE][GRIDSIZE]);
void enc_wordInsert(char grid[GRIDSIZE][GRIDSIZE], char word[LENGTH],
                    int size, int row);
void enc_compare(char word[LENGTH]);
int enc_play(char grid[GRIDSIZE][GRIDSIZE], char avatar, int wordLength, int wordStart, char word[LENGTH]);
int enc_gridCheck(char grid[GRIDSIZE][GRIDSIZE], int y, int x,
int yPlus, int xPlus);
char enc_alphabetCheck(char letter);
int enc_winCheck(char grid[GRIDSIZE][GRIDSIZE], int wordLength, int wordStart, char word[LENGTH]);

int encryption(void)
{

  char *list[] = {"frondo", "gandalf","elrond", "legolas", "gimli", "aragorn","saouron"};
  char rand_word[LENGTH], shuffle_word[LENGTH];
  int i, word_size;
  char grid[GRIDSIZE][GRIDSIZE], avatar = '@';

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
  enc_gridInit(grid);
  enc_shufle(shuffle_word, word_size);
  enc_wordInsert(grid, shuffle_word, word_size, 2);
  printf("%s\n", shuffle_word);
  enc_printGrid(grid);
  enc_play(grid, avatar, word_size, 2, rand_word);
  //enc_compare(rand_word);
  return 0;
}

int enc_play(char grid[GRIDSIZE][GRIDSIZE], char avatar, int wordLength, int wordStart, char Word[LENGTH]){

  char move;
  int x_ava=5, y_ava=5;
  grid[5][5] = avatar;
  while(scanf("%c",&move)==1){
    switch (move) {
      case 'i': // move up
      if(enc_gridCheck(grid, y_ava, x_ava, -1, 0)==1){
        printf("yay!\n");
        break;
      }
      else{
        grid[y_ava][x_ava] = ' ';
        y_ava--;
        grid[y_ava][x_ava] = avatar;
        //printf("yay!\n");
        break;
      }
      case 'j': // move left
        grid[y_ava][x_ava] = ' ';
        x_ava--;
        grid[y_ava][x_ava] = avatar;
        break;
      case 'l' : // move right
        grid[y_ava][x_ava] = ' ';
        x_ava++;
        grid[y_ava][x_ava] = avatar;
        break;
      case 'k': // move down
        grid[y_ava][x_ava] = ' ';
        y_ava++;
        grid[y_ava][x_ava] = avatar;
        break;
      }
      enc_printGrid(grid);
      if (enc_winCheck(grid, wordLength, wordStart, Word)==1){
        printf("you have won!!\n");
        return 1;
      }
    }
    /*res=BinResult(byte);
    printf("result %d\n",res );
    if(res==goal){
      break;
    }*/
    return 0;
}

int enc_winCheck(char grid[GRIDSIZE][GRIDSIZE], int wordLength, int wordStart, char word[LENGTH]){
  int cnt;
  wordLength=wordLength-2;
  //printf("wordLength=%d wordStart=%d word=%s\n", wordLength, wordStart, word);
  for(cnt=0; cnt<wordLength+wordStart; cnt++){
    //printf("grid %c secret %c ", grid[2][cnt+wordStart-1], word[cnt]);
    if(grid[2][cnt+wordStart-1]!=word[cnt]){
      return 0;
    }
  }
  return 1;
}

/*checks whether there is a letter, if there is a letter
then it increments the letter by one*/
int enc_gridCheck(char grid[GRIDSIZE][GRIDSIZE], int y, int x,
int yPlus, int xPlus){
  if(grid[y+yPlus][x+xPlus]>='a' && grid[y+yPlus][x+xPlus]<='z'){
    grid[y+yPlus][x+xPlus]=enc_alphabetCheck(grid[y+yPlus][x+xPlus]);
    return 1;
  }
  else{
    return 0;
  }
}

char enc_alphabetCheck(char letter){ // function to make sure that letter wraps around
  if(letter=='z'){
    return 'a';
  }
  else{
    return letter+1;
  }
}

void enc_compare(char word[LENGTH]){
  char user_word[LENGTH];
  int condition = FALSE;
  while(condition == FALSE){
    printf("\nTry to find the correct word\n");
    scanf("%s",user_word);
    if (strcmp(user_word,word) == 0){
      printf("Congrats you have found the hidden word\n");
      condition = TRUE;
    }
  }
}

void enc_wordInsert(char grid[GRIDSIZE][GRIDSIZE], char word[LENGTH],
                    int size, int row){
  int cnt;

  for(cnt=0; cnt<size; cnt++){
    grid[row][cnt+1]=word[cnt];
  }
}

void enc_gridInit(char grid[GRIDSIZE][GRIDSIZE]){
  int cntW, cntH;
  for (cntH=0; cntH<GRIDSIZE; cntH++){
    for (cntW=0; cntW<GRIDSIZE; cntW++){
      if ((cntH == 0) || (cntH == (GRIDSIZE-1))){
          grid[cntH][cntW] = '_';
      }
      else if ((cntW==0) || (cntW == (GRIDSIZE-1))){
        grid[cntH][cntW] = '|';
      }
      else{
          grid[cntH][cntW]=' ';
      }
    }
  }
}

void enc_printGrid(char grid[GRIDSIZE][GRIDSIZE]){
  int cntW, cntH;
  for (cntH=0; cntH<GRIDSIZE; cntH++){
    for (cntW=0; cntW<GRIDSIZE; cntW++){
      printf("%c", grid[cntH][cntW]);
      }
    printf("\n");
    }
}

void enc_shufle(char word[LENGTH], int size){
  int game ;

  game = rand()%3;
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
