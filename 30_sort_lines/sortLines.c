#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


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

char ** getCharArrFile(char ** line_array, char * filename, size_t * count) {
    errno = 0;
    
    char *line = NULL;
    size_t sz = 0;
    ssize_t size = 0;
   
    FILE * work_file = fopen(filename, "r");
    if (work_file == NULL) {
        return NULL;
    }
    while ((size = getline(&line, &sz, work_file)) >= 0) {
        if (line == NULL) {
            return NULL;
        }
        line_array = realloc(line_array, (*count + 1)*sizeof(*line_array));
        if (line_array == NULL) {
            return NULL;
        }
        line_array[*count] = line;
        line = NULL;
        sz = 0;
        (*count)++;
    }
    free(line);
    int cls = fclose(work_file);
    if (cls != 0) {
        return NULL;
    }
    if (errno != 0) {
        return NULL;
    }
    return line_array;

}

char ** getCharArrInp(char **line_array, size_t * count) {
    errno = 0;
    char * line = NULL;
    size_t sz = 0;
    ssize_t size = 0; 
    
    while ((size = getline(&line, &sz, stdin)) > 1) {
        if (line == NULL) {
            return NULL;
        }
        line_array = realloc(line_array, (*count + 1)*sizeof(*line_array));
        if (line_array == NULL) {
            return NULL;
        }
        line_array[*count] = line;
        line = NULL;
        sz = 0;
        (*count)++;
    }
    if (*count == 0) {
	return NULL;
    }
    free(line);
    if (errno != 0) {
        return NULL;
    }
    return line_array;
}

int printArrayFree(char ** line_array, size_t count) {
    errno = 0;
    if (count > 1) {
        sortData(line_array, count);
    }
    if (count < 1) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < count; i++) {
        printf("%s", line_array[i]);
    }
    
    for (size_t i = 0; i < count; i++) {
        free(line_array[i]);
    }
    free(line_array);
    if (errno != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
    size_t count = 0;
    int suc = 0;
    char ** arr = NULL;
    if (argc == 1) {
        arr = getCharArrInp(arr, &count);
        if (arr == NULL) {
            printf("Input error\n");
            return EXIT_FAILURE;
        }
        suc = printArrayFree(arr, count);
        if (suc == EXIT_FAILURE) {
            printf("Print fail\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    char * file_in = NULL;
    for (int i = 1; i < argc; i++) {
        file_in = argv[i];
        FILE * f = fopen(file_in, "r");
        if (f == NULL) {
            printf("Error in file\n");
            return EXIT_FAILURE;
        }
        else {
            fclose(f);
        }
    }
    file_in = NULL;
    for (int i = 1; i < argc; i++) {
        file_in = argv[i];
        arr = getCharArrFile(arr, file_in, &count);
        if (arr == NULL) {
            printf("Error in file\n");
            return EXIT_FAILURE;
        }
        suc = printArrayFree(arr, count);
        if (suc == EXIT_FAILURE) {
            printf("Print fail\n");
            return EXIT_FAILURE;
        }
        count = 0;
        file_in = NULL;
        arr = NULL;
    }
    return EXIT_SUCCESS;
}
