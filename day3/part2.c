#include <stdio.h>
#include<string.h>

#define STR_MAX 256

int small_flag[26];
int cap_flag[26];

int find_priorities(char *first, char *second, char *third)
{
     int i, len;
     int index = 0;
     int priorities = 0;

//     printf("[first=%s, second=%s, third=%s]\n", first, second, third);

    for(i = 0; i < 27 ; i++)
    {
        small_flag[i] = 0;
        cap_flag[i] = 0;
     }

     len = strlen(first);
     for (i = 0; i< len; i++)
     {
         if ( (first[i] >= 'A') && (first[i] <= 'Z'))
         {
             index = first[i] - 'A';
             cap_flag[index] = 1;
         }
         if ( (first[i] >= 'a') && (first[i] <= 'z'))
         {
            index = first[i] - 'a';
            small_flag[index] = 1;
         }
     }

     len = strlen(second);
     for (i = 0; i< len; i++)
     {
         if ( (second[i] >= 'A') && (second[i] <= 'Z'))
         {
             index = second[i] - 'A';
             if( cap_flag[index] == 1)
                cap_flag[index] = 2;
         }
         if ( (second[i] >= 'a') && (second[i] <= 'z'))
         {
            index = second[i] - 'a';
            if(small_flag[index] == 1)
                small_flag[index] = 2;
         }
     }

     len = strlen(third);
     for (i = 0; i< len; i++)
     {
         if ( (third[i] >= 'A') && (third[i] <= 'Z'))
         {
             index = third[i] - 'A';
             if(cap_flag[index] == 2)
             {
                priorities = 27 + third[i] - 'A' ;
//            printf("\nFound letter: %c priorities=%d\n",third[i], priorities);
                return priorities;
             }
         }
         if ( (third[i] >= 'a') && (third[i] <= 'z'))
         {
            index = third[i] - 'a';
            if(small_flag[index] == 2)
            {
                priorities = 1 + third[i] - 'a' ;
//            printf("\nFound letter: %c priorities=%d\n",third[i], priorities);
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
   char elves[3][STR_MAX];
   int  count  = 0;
   int len = 0;


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
     len = strlen(input);
     len--;
     input[len] = '\0';
     strcpy(&elves[count][0], input);
     count++;
     if(count == 3)
     {
         priorities = find_priorities(&elves[0][0], &elves[1][0] , &elves[2][0]);
         totalPriorities += priorities;
         count = 0;
     }
   }

   printf("Total Priorities= %d\n", totalPriorities);

   fclose(fp);
   return 0;
}
