#include <stdio.h>
#include<string.h>

#define STR_MAX 256

int small_flag[26];
int cap_flag[26];

int find_pair(char *input)
{
   int first_start = 0;
   int first_end= 0;
   int second_start = 0;
   int second_end= 0;

   int first_range = 0;
   int second_range = 0;

   sscanf(input, "%d-%d,%d-%d",&first_start, &first_end, &second_start, &second_end);


   first_range = first_end - first_start;
   second_range = second_end - second_start;

   if  ((first_start <= second_start)  && (second_start <= first_end) )
   {
      //printf("%d-%d,%d-%d\n",first_start, first_end, second_start, second_end);
      return 1;
   } else if ((first_start >= second_start)  && (first_start  <= second_end) )
   {
      //printf("%d-%d,%d-%d\n",first_start, first_end, second_start, second_end);
      return 1;
   }  else {
      //printf("%d-%d,%d-%d\n",first_start, first_end, second_start, second_end);
      return 0;
   }
    return 0;
}

int main(int argc, char *argv[])
{
   FILE *fp;
   char input[STR_MAX];
   int pair = 0;
   int totalPair = 0;
   int nonPair = 0;
   int line = 0;
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
     line++;
     len = strlen(input);
     len--;
     input[len] = '\0';
     if(find_pair(input))
       totalPair ++;
     else
       nonPair++;
   }

   printf("Total Pair = %d\n", totalPair);
   printf("Total line = %d, nonPair=%d\n", line, nonPair);

   fclose(fp);
   return 0;
}
