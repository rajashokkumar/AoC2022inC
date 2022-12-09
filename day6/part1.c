#include <stdio.h>
#include<string.h>

#define STR_MAX 5000

int isUnique(char a, char b, char c, char d)
{

  if ( (a != b) && (a !=c) && (a != d) && (b !=c) && (b!= d) && (c !=d))
  {
      return 1;
  }

  return 0;
}

int find_start(char *input)
{
   int slow = 0;
   int fast = 4;
   int len = strlen(input);

   while(fast < len)
   {
      if(isUnique(input[slow], input[slow+1], input[slow+2], input[slow+3]))
        return fast;

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
