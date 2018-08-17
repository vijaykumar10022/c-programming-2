#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10]){
    char temp_mat[10][10];
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            temp_mat[row][col] = matrix[9 - col][row];
        }
    }
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            matrix[row][col] = temp_mat[row][col];
        }
    } 
}

int main(int argc, char ** argv){
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        return EXIT_FAILURE;
    }
    int chr;
    char to_rot_mat[10][10];
    int row_count = 0;
    int col_count = 0;
    while ((chr = fgetc(f)) != EOF) {
        if (col_count == 10) {
            col_count = 0;
            row_count++;
            if (chr != '\n') {
                return EXIT_FAILURE;
            }
        }
        else {
            if (chr == '\n') {
                return EXIT_FAILURE;
            }
            to_rot_mat[row_count][col_count] = chr;
            col_count++;
        }
    }
    if (row_count != 10) {
        return EXIT_FAILURE;
    }
    fclose(f);
    rotate(to_rot_mat);
    
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            printf("%c", to_rot_mat[row][col]);
            if (col == 9) {
                printf("%c", '\n');
            }
        }
    }
    return EXIT_SUCCESS;
}
