#include <stdio.h>
#include<string.h>

#define STR_MAX 256

#define MAX_STACK_SIZE 100
#define MAX_CRATES 10
char crates[MAX_CRATES][MAX_STACK_SIZE];
int crates_stack_size[MAX_CRATES];

int push(int crate, char c)
{
    if(crate >= MAX_CRATES)
    {
       printf("Push Increase MAX_CRATES size\n");
        return -1;
    }

   if(crates_stack_size[crate] >= MAX_STACK_SIZE)
   {
        printf("Push Increase MAX_STACK_SIZE size\n");
        return -2;
   }

   crates[crate][crates_stack_size[crate]] = c;
   crates_stack_size[crate]++;
   return 0;
}

char pop(int crate)
{
  char ret = '\0';

    if(crate >= MAX_CRATES)
    {
       printf("Pop Increase MAX_CRATES size\n");
        return ret;
    }

   if(crates_stack_size[crate] <=  0)
   {
        printf("Empty stack\n");
        return ret;
   }

   crates_stack_size[crate]--;
   ret = crates[crate][crates_stack_size[crate]];
   return ret;
}
void stage_input_stack()
{

#if 0
/* Sample
    [D]
[N] [C]
[Z] [M] [P]
 1   2   3
*/

push(0,'Z');
push(0,'N');

push(1,'M');
push(1,'C');
push(1,'D');

push(2,'P');

#endif
/* Test input
[W] [V]     [P]
[B] [T]     [C] [B]     [G]
[G] [S]     [V] [H] [N] [T]
[Z] [B] [W] [J] [D] [M] [S]
[R] [C] [N] [N] [F] [W] [C]     [W]
[D] [F] [S] [M] [L] [T] [L] [Z] [Z]
[C] [W] [B] [G] [S] [V] [F] [D] [N]
[V] [G] [C] [Q] [T] [J] [P] [B] [M]
 1   2   3   4   5   6   7   8   9
*/
push(0,'V');
push(0,'C');
push(0,'D');
push(0,'R');
push(0,'Z');
push(0,'G');
push(0,'B');
push(0,'W');
push(1,'G');
push(1,'W');
push(1,'F');
push(1,'C');
push(1,'B');
push(1,'S');
push(1,'T');
push(1,'V');
push(2,'C');
push(2,'B');
push(2,'S');
push(2,'N');
push(2,'W');
push(3,'Q');
push(3,'G');
push(3,'M');
push(3,'N');
push(3,'J');
push(3,'V');
push(3,'C');
push(3,'P');
push(4,'T');
push(4,'S');
push(4,'L');
push(4,'F');
push(4,'D');
push(4,'H');
push(4,'B');
push(5,'J');
push(5,'V');
push(5,'T');
push(5,'W');
push(5,'M');
push(5,'N');
push(6,'P');
push(6,'F');
push(6,'L');
push(6,'C');
push(6,'S');
push(6,'T');
push(6,'G');
push(7,'B');
push(7,'D');
push(7,'Z');
push(8,'M');
push(8,'N');
push(8,'Z');
push(8,'W');
}

void print_stack()
{

int crate = 0;
int stack_size = 0;

for(crate = 0; crate < MAX_CRATES; crate++)
{
   stack_size = crates_stack_size[crate];
   if(stack_size)
   {
       printf("Stack of crates:[%d] stack_size=%d\n", crate, stack_size);

       while (stack_size >= 0)
       {
         stack_size--;
         printf("%c\t",crates[crate][stack_size]);
       }
       printf("\n");
   }
}

}


void print_crypt()
{

int crate = 0;
int stack_size = 0;

for(crate = 0; crate < MAX_CRATES; crate++)
{
   stack_size = crates_stack_size[crate];
   if(stack_size)
   {
         stack_size--;
         printf("%c",crates[crate][stack_size]);
   }
}
printf("\n");
}

void arrange_stack( int count, int src, int dst)
{
  char c;
  if( ( src >= MAX_CRATES) || (dst >= MAX_CRATES))
  {
     printf("ERROR: More than stack size\n");
     return;
  }

  if(count > crates_stack_size[src])
  {
    printf("ERROR: No elements to move\n");
    return;
  }

  while(count > 0)
  {
      c = pop(src);
      push(dst, c);
      count--;
  }

  return;
}

int main(int argc, char *argv[])
{
   FILE *fp;
   char input[STR_MAX];
   int len = 0;
   int src = -1;
   int dst = -1;
   int count = 0;


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

   stage_input_stack();
//   print_stack();

   memset((void *)input,'\0',STR_MAX);
   while (fgets(input, STR_MAX, fp) != NULL)
   {
     len = strlen(input);
     len--;
     input[len] = '\0';
     sscanf(input, "move %d from %d to %d", &count, &src, &dst);
     arrange_stack(count, src-1, dst-1);
 //    printf(" no of push/pop: %d src_crate:%d dst_crate:%d\n",count, src, dst );
  //   print_stack();
   }

   //printf("\n=====After====\n");
   //print_stack();
   print_crypt();
   fclose(fp);
   return 0;
}
