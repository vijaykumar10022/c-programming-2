#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10]){
    char temp_mat[10][10];
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            temp_mat[row][col] = matrix[col][9 - row];
        }
    }
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            matrix[row][col] = temp_mat[row][col];
        }
    } 
}
