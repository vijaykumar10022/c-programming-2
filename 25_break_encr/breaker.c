#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int maxValInd(int * array, int size) {
    int maxVal = 0;
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (*(array + i) > maxVal) {
            maxVal = *(array + i);
            idx = i;
        }
    }
    return idx;
}

void getFreqArr(int *freqArr, FILE * f){
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            c = tolower(c);
            c -= 'a';
            freqArr[c] = freqArr[c] + 1;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr,"Usage: Wrong amount of Arguments\n");
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    int freqArr[26] = {0};
    getFreqArr(freqArr, f);
    int key = maxValInd(freqArr, 26);
    int val = key + 'a' - 'e';
    val = (val + 26)%26;
    printf("%d\n", val);
}
