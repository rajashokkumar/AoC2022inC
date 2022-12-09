#include<stdio.h>
#include<string.h>
#include <stdlib.h>


int most1Calories = 0;
int most2Calories = 0;
int most3Calories = 0;
int leastCalories = 0;

#define STR_MAX 256

void updateMostAndLeastCalories(int calories)
{
    if (leastCalories == 0)
    {
       leastCalories = calories;
    }

    if(calories >= most1Calories)
    {
        most3Calories = most2Calories;
        most2Calories = most1Calories;
        most1Calories = calories;
    } else if ( calories >= most2Calories) {
        most3Calories = most2Calories;
        most2Calories = calories;
    } else if ( calories >= most3Calories) {
        most3Calories = calories;
    }


    if(calories < leastCalories)
        leastCalories = calories;
    return;
}

int main()
{
   FILE *fp;
   int   calories = 0;
   int   totalCalories = 0;
   char   strCalories[STR_MAX];

   fp = fopen("part1_input.txt", "r");
   if(fp == NULL)
   {
      printf("Unable to open file.\n");
      return -1;
   }

   memset((void *)strCalories,'\0',STR_MAX);

   while (fgets(strCalories, STR_MAX, fp) != NULL)
   {

     calories = atoi(strCalories);
     if  (calories)
     {
         totalCalories = totalCalories + calories;
     } else {
          printf("totalCalories before reset : %d\n", totalCalories);
          if (totalCalories)
          {
             updateMostAndLeastCalories(totalCalories);
             totalCalories = 0;
          }
     }

//     printf("[str=%s][len = %ld][atoi=%d]", strCalories, strlen(strCalories), atoi(strCalories));
     memset((void *)strCalories,'\0',STR_MAX);
   }

   printf("Elf with 1st most calories : %d\n", most1Calories);
   printf("Elf with 2nd most calories : %d\n", most2Calories);
   printf("Elf with 3rd most calories : %d\n", most3Calories);
   printf("Elf with top 3 total calories : %d\n", most1Calories + most2Calories + most3Calories);
   printf("Elf with least calories : %d\n", leastCalories);

   fclose(fp);
   return 0;
}
