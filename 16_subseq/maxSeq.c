#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n){
    if (n == 0){
        return 0;
    }
    int maxSeqLen = 1;
    int curSeqLen = 1;
    int curVal = *array;
    int lastVal = *array;
    for (int i = 1; i < n; i++){
        curVal = *(array + i);
        if (curVal > lastVal || curSeqLen == 0){
            curSeqLen++;
            if (curSeqLen > maxSeqLen){
                maxSeqLen = curSeqLen;
            }
        }
        else {
            curSeqLen = 0;
        }
        lastVal = curVal;
    }
    return maxSeqLen;
}
