//
//  main.c
//  Lab7
//
//  Created by Thomas Chan on 2017-10-29.
//  Copyright © 2017 Thomas Chan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

int checkrow(int x,int num);
int checkcolumn(int y, int num);
int solveSudoku(int x, int y);
int matrix[9][9];


int main(int argc, char * argv[]) {
    FILE *fp;
    int x,y;
    
    if (argc >= 2){
        
        //Read sudoku
        
        fp = fopen(argv[1], "r");
        printf("Input\n");
        printf("-------------------------------\n");
        for (y =0; y <= 8; y++){
            printf("|");
            for (x = 0; x <= 8; x++){
                fscanf(fp,"%i",&matrix[y][x]);
                printf(" %i ",matrix[y][x]);
                if (((x +1)%3)==0)
                    printf("|");
            }
            printf("\n");
            if ((y+1)%3 == 0)
                printf("-------------------------------\n");
        }
        fclose(fp);
        
        printf("\n");
        printf("\n");
        
        solveSudoku(0, 0);
        
        printf("Solved\n");
        printf("-------------------------------\n");
        for (int y =0; y <= 8; y++){
            printf("|");
            for (int x = 0; x <= 8; x++){
                printf(" %i ",matrix[y][x]);
                if (((x +1)%3)==0)
                    printf("|");
            }
            printf("\n");
            if ((y+1)%3 == 0)
                printf("-------------------------------\n");
        }
        
        return EXIT_SUCCESS;
    }
}



 int checkrow(int x,int num){
     for (int i =0; i < 9; i++)
         if (matrix[x][i] == num){
             return 0;
         }
     return 1;
 }

int checkcolumn(int y, int num){
    for (int i = 0; i< 9; i++)
        if (matrix[i][y] == num){
            return 0;
        }
    return 1;
}

int checksquare(int x, int y, int num){
    int k,l,x1,x2,y1,y2;
    k = (x/3)*3;
    l = (y/3)*3;
    x1 = (x+2)%3;
    x2 = (x+4)%3;
    y1 = (y+2)%3;
    y2 = (y+4)%3;

    if (matrix[x1+k][y1+l] == num){
        return 0;
        
    }
    if (matrix[x2+k][y1+l] == num){
        return 0;
    }
    if (matrix[x1+k][y2+l] == num){
        return 0;
    }
    if (matrix[x2+k][y2+l] == num){
        return 0;
    }
    return 1;
}




int solveSudoku(int i, int j){
    
    //base case
    if (i >= 9){
        return 1;
    }
    
    
    else if (matrix[i][j] != 0){
        if ((j+1) < 9){
            return solveSudoku(i , j +1);
        }
        else if ((i+1) < 9){
            return solveSudoku(i + 1, 0);
        }
        else{
            return 1;
        }
    }
    
    
    else{
        for (int num = 0; num < 9;num ++){
            if ((checkrow(i, num+1) == 1) && (checkcolumn(j, num+1)== 1) && checksquare(i, j, num+1)== 1){
                matrix[i][j] = num+1;
                //printf("%d ", matrix[i][j]);
                if ((j+1) < 9){
                    if (solveSudoku(i , j +1)) return 1;
                    else{
                        matrix[i][j] = 0;
                    }
                }
                else if ((i+1) < 9){
                    if (solveSudoku(i + 1, 0)) return 1;
                    else{
                        matrix[i][j] = 0;
                    }
                }
                else{
                    return 1;
                }
            }
                
        }
    }

    return 0;
}

