/*Basic Score system*/
/*These codes will be the basics of other alterations, so NO TOUCHIE!!!!*/

#include <stdio.h>
#include <stdlib.h>

#define GAMESCORE 2000      /*Basic score whcih pleyers earn regardless of clear time*/
#define GAMETIME 110        /*Time taken to complete the game(in seconds)*/
#define MULTIPLIER 1        /*Multiplier is added for every game completed within benchmark time*/
#define BENCHMARK_TIME 180  /*Benchmark time(in seconds)*/
#define HINTS_USED 2        /*No. of time hints have been used*/
#define DEDUCTION 100       /*Amount of points deducted when using the hint.*/

void printscore(int game_score, int final_multiplier, int total_score, int hints, int minus);

int main(void)
{

  int game, multi, totalscore, hints, deduct, minus;

  game = GAMESCORE;
  multi = MULTIPLIER;
  totalscore = game * multi;
  hints = HINTS_USED;
  deduct = DEDUCTION;

  /*if statement to determine adding Multiplier*/
  if (GAMETIME <= BENCHMARK_TIME){
    multi++;
  }

/*If hints have been used, points will be deducted.*/
  if (HINTS_USED > 0){
    minus = hints*deduct;
    totalscore = totalscore - minus;
  }

  printscore(game, multi, totalscore, hints, minus);

  return 0;
}

void printscore(int game_score, int final_multiplier, int total_score, int hints, int minus){

  int final_score;

  total_score = final_multiplier * game_score;
  final_score = total_score - minus;

  printf("\n\t-------SUMMARY--------\n\n");
  printf("Game Score:\t\t%d\n", game_score);
  printf("Final Multiplier:\t%d\n", final_multiplier);
  printf("Total Score:\t\t%d\n\n", total_score);

  printf("No. of hints used:\t%d\n", hints);
  printf("Final Deduction:\t%d\n\n", minus);

  printf("Final Score: \t\t%d\n", final_score);
}
