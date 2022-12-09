#include <stdio.h>
#include<string.h>

#define STR_MAX 256

int small_flag[26];
int cap_flag[26];


int find_priorities(char *input)
{
   int len = 0;
   int half = 0;
   char first_half[256];
   char second_half[256];
   int i;
   int priorities = 0;
   int index = 0;

   memset((void *)first_half,'\0',STR_MAX);
   memset((void *)second_half,'\0',STR_MAX);
   len = strlen(input);
   len--;
   input[len] = '\0';
   half = len/2;
   strncpy(first_half, input, half);
   first_half[half] = '\0';
   strncpy(second_half, input+half, half);
   second_half[len] = '\0';

   for(i = 0; i < 27 ; i++)
   {
     small_flag[i] = 0;
     cap_flag[i] = 0;
   }

   for(i = 0; i < half; i++)
   {
     if ( (first_half[i] >= 'A') && (first_half[i] <= 'Z'))
     {
        index = first_half[i] - 'A';
        cap_flag[index] = 1;
     }

     if ( (first_half[i] >= 'a') && (first_half[i] <= 'z'))
     {
        index = first_half[i] - 'a';
        small_flag[index] = 1;
     }
   }

   for(i = 0; i < half; i++)
   {
     if ( (second_half[i] >= 'A') && (second_half[i] <= 'Z'))
     {
        index = second_half[i] - 'A';
        if(cap_flag[index])
        {
             priorities = 27 + second_half[i] - 'A' ;
 //            printf("\nFound letter: %c priorities=%d\n",second_half[i], priorities);
             return priorities;
        }
     }

     if ( (second_half[i] >= 'a') && (second_half[i] <= 'z'))
     {
        index = second_half[i] - 'a';
        if(small_flag[index])
        {
            priorities = 1 + second_half[i] - 'a' ;
//            printf("\nFound letter: %c priorities=%d\n",second_half[i], priorities);
            return priorities;
        }
     }
   }

   return 0;
}

int main(int argc, char *argv[])
{
   FILE *fp;
   char  input[STR_MAX];
   int priorities = 0;
   int totalPriorities = 0;


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

   memset((void *)input,'\0',STR_MAX);
   while (fgets(input, STR_MAX, fp) != NULL)
   {
     priorities = find_priorities(input);
     totalPriorities = totalPriorities + priorities;
     memset((void *)input,'\0',STR_MAX);
   }

   printf("Total Priorities= %d\n", totalPriorities);

   fclose(fp);
   return 0;
}
