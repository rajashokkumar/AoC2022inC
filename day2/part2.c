#include <stdio.h>
#include<string.h>

#define STR_MAX 256
//#define INPUT_FILE "day3_input_sample.txt"
#define INPUT_FILE "day3_input.txt"

#define WIN_SCORE 6
#define DRAW_SCORE 3
#define LOSS_SCORE 0

int find_score (char *input)
{
  char op, own;
  int score = 0;

  sscanf(input, "%c %c", &op, &own);
//  printf("\n[%c %c]",op, own);

  //For win
  if(own == 'X')
  {
    if(op == 'A')
      own = 'C';
    else if (op == 'B')
      own = 'A';
    else if (op == 'C')
      own = 'B';
  }  else if(own == 'Y')
  {
     own = op;
  } else if (own == 'Z')
  {
    if(op == 'A')
      own = 'B';
    else if (op == 'B')
      own = 'C';
    else if (op == 'C')
      own = 'A';
  }

 // printf("\nNew [%c %c]",op, own);

   if(own == 'A')
     score = 1;
   else if(own == 'B')
     score = 2;
   else if(own == 'C')
     score = 3;
   else
   {
      return 0;
   }

   //Find tie
   if( op == own)
   {
      score = score + DRAW_SCORE;
      return score;
   }

   //Find win
   if ( ((op == 'A') && (own == 'C')) ||
        ((op == 'C') && (own == 'B')) ||
        ((op == 'B') && (own == 'A')))
   {
      //score = score + WIN_SCORE;
      score = score + LOSS_SCORE;
   } else {
      //score = score + LOSS_SCORE;
      score = score + WIN_SCORE;
   }

   return score;
}
int main(int argc, char *argv[])
{
   FILE *fp;
   int   totalScore = 0;
   int   score = 0;
   char  game[STR_MAX];

   if (argc != 2)
   {
      printf("Usage : ./a.out <input_file>\n");
      return -1;

   }

   fp = fopen(argv[1], "r");
   if(fp == NULL)
   {
      printf("Unable to open input file.\n");
      return -1;
   }

   memset((void *)game,'\0',STR_MAX);

   while (fgets(game, STR_MAX, fp) != NULL)
   {
     score = find_score(game);
     totalScore = totalScore + score;
//     printf("[%s : score : %d total score : %d]",game, score, totalScore);
     memset((void *)game,'\0',STR_MAX);
   }

   printf("Total Score : %d\n", totalScore);

   fclose(fp);
   return 0;
}
