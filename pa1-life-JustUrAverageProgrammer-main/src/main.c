#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "life.h"

/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argumentq (which is required) is a starting state in one of the Life
 * formats squpported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 */

//Checks if cell is alive or dead
bool dead_or_live(char c){
    bool isDead;
    if (c == LIVE){
        isDead = false;
        return isDead;
    }else{
        isDead = true;
        return isDead;
    }
}

//If cell is live return 1, 0 otherwise
int updateCount(char c){
    if (dead_or_live(c) == false){
        return 1;
    }else{
        return 0;
    }
}

void compute_generations(int genNum, char grid[][GRIDY+2][GRIDX+2]){
       int liveCount = 0;
       char nextStateOfCell = ' ';
       for (int c = 0; c < genNum; c++){
           for (int i = 1; i < GRIDY+1; i++){
               for (int j = 1; j < GRIDX+1; j++){
                   char currentCell = grid[c][i][j];

                   char nRight = grid[c][i][j+1];
                   char nLeft = grid[c][i][j-1];
                   char nTop = grid[c][i-1][j];
                   char nBot = grid[c][i+1][j];
                   char nD1 = grid[c][i+1][j+1];
                   char nD2 = grid[c][i-1][j+1];
                   char nD3 = grid[c][i+1][j-1];
                   char nD4 = grid[c][i-1][j-1];

                   liveCount += updateCount(nRight);
                   liveCount += updateCount(nLeft);
                   liveCount += updateCount(nTop);
                   liveCount += updateCount(nBot);
                   liveCount += updateCount(nD1);
                   liveCount += updateCount(nD2);
                   liveCount += updateCount(nD3);
                   liveCount += updateCount(nD4);

                   
                   if ((dead_or_live(currentCell) == false) && (liveCount < 2)){
                       nextStateOfCell = DEAD;
                   }
                   if ((dead_or_live(currentCell) == false) && (liveCount > 3)){
                       nextStateOfCell = DEAD;
                   }
                   if ((dead_or_live(currentCell) == false) && ((liveCount == 2) || (liveCount == 3))){
                       nextStateOfCell = LIVE;
                   }
                   if ((dead_or_live(currentCell) == true) && (liveCount == 3)){
                       nextStateOfCell = LIVE;
                   }
                   
                   grid[c+1][i][j] = nextStateOfCell;
                   nextStateOfCell = ' ';
                   liveCount = 0;
               }
           }
       }
}

void print_matrix(int genNum, char grid[][GRIDY+2][GRIDX+2]){
    if (genNum == 0){
           for (int i = 0; i < GRIDY; i++){
               for (int j = 0; j < GRIDX; j++){
                   printf("%c", grid[0][i+1][j+1]);
               }
               printf("\n");
           }
       }else{
           compute_generations(genNum, grid);
           for (int i = 0; i < GRIDY; i++){
               for (int j = 0; j < GRIDX; j++){
                   printf("%c", grid[genNum][i+1][j+1]);
               }
               printf("\n");
           }
       }
   }



int main(int argc, char *argv[])
{
    if (argc != 3){
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    
    
  int genNum = atoi(argv[2]);
  char gridGenerations[genNum+1][GRIDY+2][GRIDX+2];
  char **startingMatrix = parse_life(argv[1]);//returns desired gen 0 matrix
  
  //Copy over parser matrix our matrix(gridGenerations) gen0
  for (int i = 0; i < GRIDY; i++){
      for (int j = 0; j < GRIDX; j++){
          char currentCell = startingMatrix[i][j];
          gridGenerations[0][i+1][j+1] = currentCell;
      }
  }
  
  print_matrix(genNum, gridGenerations);
 
  return 0;
}
