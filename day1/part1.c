#include<string.h>
#include <stdlib.h>
#include <stdio.h>

int mostCalories = 0;
int leastCalories = 0;

#define STR_MAX 256

void updateMostAndLeastCalories(int calories)
{
    if (leastCalories == 0)
       leastCalories = calories;

    if(calories > mostCalories)
        mostCalories = calories;
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

   printf("Elf with most calories : %d\n", mostCalories);
   printf("Elf with least calories : %d\n", leastCalories);

   fclose(fp);
   return 0;
}
