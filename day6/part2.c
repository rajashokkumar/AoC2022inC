#include <stdio.h>
#include<string.h>

#define STR_MAX 5000

#define FIND_LEN 14

int found_flag[27];

int isUnique(char *input)
{
  int i =0;
  int index = 0;

  //Reset flag
  for(i = 0; i< 26; i++)
  {
     found_flag[i] = 0;
  }

  for(i =0; i < FIND_LEN; i++)
  {
     index = input[i] - 'a';
     if(found_flag[index])
       return 0;
     else
        found_flag[index] = 1;
  }

  return 1;
}

int find_start(char *input)
{
   int slow = 0;
   int fast = FIND_LEN;
   int len = strlen(input);
   char temp[FIND_LEN+1];

   memset((void *)temp,'\0',FIND_LEN+1);

   while(fast < len)
   {
      strncpy(temp, &input[slow], FIND_LEN);
//      printf("[%s]\n",temp);
      if(isUnique(temp))
      {
        return fast;
      }
      memset((void *)temp,'\0',FIND_LEN+1);

      slow++;
      fast++;
   }
   return 0;
}

int main(int argc, char *argv[])
{
   FILE *fp;
   char input[STR_MAX];
   int len = 0;
   int startOfPacket = 0;


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
     startOfPacket = find_start(input);
     printf("Stream [%s]\n", input);
     printf("Start of packet is at : [%d]\n", startOfPacket);
     memset((void *)input,'\0',STR_MAX);
   }

   fclose(fp);
   return 0;
}
