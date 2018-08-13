#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
    int array1[] = {0, 1, -1, 1};
    int array2[] = {0, 2, 5, 7, 8};
    int array3[] = {-1, -2, -3};
//    int array4[0] = {};
    int array5[] = {1, 1, 1, 1, 1};
    int array6[] = {1, 6, 10, 1, -3, 4, 5, 10};
    if (maxSeq(array1, 4) != 2){
        return EXIT_FAILURE;
    }
    if (maxSeq(array2, 5) != 5){
        return EXIT_FAILURE;
    }
    if (maxSeq(array3, 3) != 1){
        return EXIT_FAILURE;
    }
//    if (maxSeq(array4, 0) != 0){
//        return EXIT_FAILURE;
//    }
    if (maxSeq(array5, 5) != 1){
        return EXIT_FAILURE;
    }
    if (maxSeq(array6, 8) != 4){
	return EXIT_FAILURE;
    }
    printf("Success");
    return EXIT_SUCCESS;
}
