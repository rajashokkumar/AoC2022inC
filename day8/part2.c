
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#define STR_MAX 256
#define MAX_ROW 100
#define MAX_COL 100

int flags[MAX_ROW+1][MAX_COL+1];
int data[MAX_ROW+1][MAX_COL+1];
int actRow = 0;
int actCol = 0;

void resetFlags(int row, int col)
{
   int i =0;
   int j =0;
   for(i=0; i<= MAX_ROW; i++)
   {
      for(j=0; j <= MAX_COL; j++)
      {
         flags[i][j] = 0;
      }
   }

   i = 0;
   for(j=0; j < col; j++)
   {
      flags[i][j] = 1;
   }
   i = row-1;
   for(j=0; j < col; j++)
   {
      flags[i][j] = 1;
   }

   j = 0;
   for(i=0; i < row; i++)
   {
      flags[i][j] = 1;
   }

   j = col-1;
   for(i=0; i < row; i++)
   {
      flags[i][j] = 1;
   }
}

int countFlags()
{
   int i =0;
   int j =0;
   int count = 0;
   for(i=0; i< MAX_ROW; i++)
   {
      for(j=0; j < MAX_COL; j++)
      {
         if(flags[i][j])
            count++;
      }
   }
   return count;
}

void printFlags(int row, int col)
{
   int i =0;
   int j =0;
   printf("==Start==\n");
   for(i=0; i< MAX_ROW; i++)
   {
      for(j=0; j < MAX_COL; j++)
      {
         printf("%d,",flags[i][j]);
      }
      printf("\n");
   }
   printf("==End==\n");

}

void fillData(char *col, int row)
{
   int i;
   int j;
   int value;
   int len;
   len = strlen(col);

   for(i=0; i < len; i++)
   {
      value = col[i] - '0';
      data[row][i] = value;
   }
}

void printData()
{
   int i =0;
   int j =0;
   printf("==Start==\n");
   for(i=0; i< MAX_ROW; i++)
   {
      for(j=0; j < MAX_COL; j++)
      {
         printf("%d,",data[i][j]);
      }
      printf("\n");
   }
   printf("==End==\n");
  
}

void setVisible()
{
   int i;
   int j;
   int high = 0;

   //First left to right
   for(i=1;i< (actRow)-1;i++)
   {
      high = data[i][0];
      for(j=1; j < (actCol-1);j++)
      {
         if(data[i][j] > high)
         {
            flags[i][j] = 1;
            high = data[i][j];
         }
      }
   }

   //Now right to left
   for(i=1;i< (actRow)-1;i++)
   {
      high = data[i][actCol-1];
      for(j=actCol-2; j >= 0;j--)
      {
         if(data[i][j] > high)
         {
            flags[i][j] = 1;
            high = data[i][j];
         }
      }
   }

   //Now top to bottom
   for(i=1;i< (actCol)-1;i++)
   {
      high = data[0][i];
      for(j=1; j < (actRow-1);j++)
      {
         if(data[j][i] > high)
         {
            flags[j][i] = 1;
            high = data[j][i];
         }
      }
   }

   //Now bottom to top
   for(i=1;i< (actCol)-1;i++)
   {
      high = data[actRow-1][i];
      for(j=actRow-2; j >= 0;j--)
      {
         if(data[j][i] > high)
         {
            flags[j][i] = 1;
            high = data[j][i];
         }
      }
   }

}

int findScore(int row, int col)
{
   int leftScore = 0;
   int rightScore = 0;
   int topScore = 0;
   int bottomScore =0;
   int totalScore = 0;
   int i;
   int j;
   

   //Right Score
   i = row;
   j = col;
   
  // printf("row:%d col:%d value is[%d]\n", row, col, data[row][col]);

   j++;
   for(;j<actCol;j++)
   {
      if( data[i][j] < data[row][col])
      {
         rightScore++;
      }
      else
      {
         rightScore++;
         break;
      }
   }
   //printf("Right score is [%d]\n", rightScore);

   //Left Score
   i = row;
   j = col;
   
      j--;
   for(;j >= 0;j--)
   {
      if( data[i][j] < data[row][col])
      {
         leftScore++;
      }
      else
      {
         leftScore++;
         break;
      }
   }

   //printf("Left score is [%d]\n", leftScore);

   //Top score
   i = row;
   j = col;
   i--;
   for(; i>=0; i--)
   {
      if(data[i][j] < data[row][col])
      {
         topScore++;
      } 
      else
      {
         topScore++;
         break;
      }
   }
   //printf("Top score is [%d]\n", topScore);

   //Bottom score
   i = row;
   j = col;
   i++;
   for(; i<actRow; i++)
   {
      if(data[i][j] < data[row][col])
      {
         bottomScore++;
      } 
      else
      {
         bottomScore++;
         break;
      }
   }
   //printf("bottom score is [%d]\n", bottomScore);


   totalScore = rightScore * leftScore * topScore * bottomScore;

   return totalScore;
}



int highScore()
{

   int i =0;
   int j = 0;
   int highScore = 0;
   int score = 0;
   for(i=1; i < actRow-1; i++)
   {
      for (j=1; j< actCol-1; j++)
      {
         score = findScore(i,j);
         if(score > highScore)
         {
            highScore = score;
         }
      }
   }
   return highScore;
}
int main(int argc, char *argv[])
{
   FILE *fp;
   char input[STR_MAX];
   int len = 0;
   int count = 0;
   int col = 0;
   int row = 0;
   int visibleCount = 0;


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
     if (input[len-1] == '\n')
          len--;
     input[len] = '\0';
     fillData(input, row);
     col = len;
     row++;
   }
   actRow = row;
   actCol = col;
   fclose(fp);

   resetFlags(row, col);
   setVisible();

   visibleCount = countFlags();

   //printFlags(row, col);
   //printData();
   printf("Part 1:  visible : %d\n", visibleCount);
   printf("Row:[%d] Col:[%d]\n", actRow, actCol);
   printf("Part 2: High score : %d\n", highScore());

   return 0;
}
