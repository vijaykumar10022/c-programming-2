#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** getCharArrFile(char * filename, size_t * count) {
    FILE * work_file = fopen(filename, "r");
    if (work_file == NULL) {
        return NULL;
    }
    char * line = NULL;
    size_t sz = 0;

    char ** line_array = NULL;
    while (getline(&line, &sz, work_file) >= 0) {
        if (line[strlen(line) - 1] != '\n'){
            return NULL;
        }
        line_array = realloc(line_array, (*count + 1)*sizeof(*line_array));
        line_array[*count] = line;
        line = NULL;
        (*count)++;
    }
    free(line);
    fclose(work_file);
    return line_array;
}

char ** getCharArrInp(size_t * count) {
    char * line = NULL;
    size_t sz = 0;
    ssize_t size = 0; 
    char ** line_array = NULL;
    while ((size = getline(&line, &sz, stdin)) > 1) {
        line_array = realloc(line_array, (*count + 1)*sizeof(*line_array));
        line_array[*count] = line;
        line = NULL;
        (*count)++;
    }
    if (*count == 0) {
	return NULL;
    }
    free(line);
    return line_array;
}

int printArrayFree(char ** line_array, size_t count) {
    if (count > 1) {
        sortData(line_array, count);
    }
    if (count < 2) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < count; i++) {
        printf("%s", line_array[i]);
    }
    
    for (size_t i = 0; i < count; i++) {
        free(line_array[i]);
    }
    free(line_array);
    return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
    size_t count = 0;
    if (argc == 1) {
        char ** arr = getCharArrInp(&count);
        if (arr == NULL) {
            printf("Input error");
            return EXIT_FAILURE;
        }
        int suc = printArrayFree(arr, count);
        if (suc == EXIT_FAILURE) {
            printf("Print fail");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    char * file_in;
    for (int i = 1; i < argc; i++) {
        file_in = argv[i];
        char ** arr = getCharArrFile(file_in, &count);
        if (arr == NULL) {
            printf("Error in file");
            return EXIT_FAILURE;
        }
        int suc = printArrayFree(arr, count);
        if (suc == EXIT_FAILURE) {
            printf("Print fail");
            return EXIT_FAILURE;
        }
        count = 0;
    }

  
    return EXIT_SUCCESS;
}
