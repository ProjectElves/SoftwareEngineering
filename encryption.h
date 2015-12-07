#include "game.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1
#define LENGTH 30
#define LIST_SIZE 7
#define ALPHABET 26

int enc_shufle(char word[LENGTH], int size);
int enc_isenc_vowel(char c);
char enc_vowel();
char enc_constant();
void enc_changeRow(char word[LENGTH], int size, int shift);
void enc_change(char word[LENGTH], int size, int game);
void encrytionGridInit(char *shuffle_word);
void enc_newLetter(cell grid[H][W], int x, int y, char c);
void enc_updateLetter(cell grid[H][W], int y, int x);
void enc_letterDown(entity *e);
void enc_letterUp(entity *e);
void enc_updateWord(cell grid[H][W], int y, int x, char shuffle[LENGTH]);
void enc_Hint(int game);
void enc_print_ascii(char letter);
