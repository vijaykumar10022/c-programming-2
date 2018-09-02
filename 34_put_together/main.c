#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t *countFrFile(FILE *work_file, kvarray_t *kvPairs) {
    char *line = NULL;
    size_t size = 0;
    char *read_key = NULL;
    char *read_val = NULL;
    int len = 0;
    counts_t *ret_counts = createCounts();
    if (ret_counts == NULL) {
        return NULL;
    }
    while (getline(&line, &size, work_file) >= 0) {
        len = strlen(line);
        if (line[len - 1] == '\n') {
            read_key = realloc(read_key, len*sizeof(*read_key));
            strncpy(read_key, line, len - 1);
            read_key[len - 1] = '\0';
        }
        else {
            read_key = realloc(read_key, (len + 1)*sizeof(*read_key));
            strncpy(read_key, line, len);
            read_key[len] = '\0';
        }
        read_val = lookupValue(kvPairs, read_key);
        addCount(ret_counts, read_val);
    }
    free(line);
    free(read_key);
    return ret_counts;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
    FILE *work_file = fopen(filename, "r");
    if (work_file == NULL) {
        return NULL;
    }
    counts_t *ret_counts = countFrFile(work_file, kvPairs);
    if (ret_counts == NULL) {
        return NULL;
    }
    fclose(work_file);
    return ret_counts;
}
int main(int argc, char ** argv) {
    //WRITE ME (plus add appropriate error checking!)
    if (argc < 3) {
        fprintf(stderr, "Not enough arguments\n");
        return EXIT_FAILURE;
    }
    //read the key/value pairs from the file named by argv[1] (call the result kv)
    kvarray_t *pairs = readKVs(argv[1]);
    if (pairs == NULL) {
        fprintf(stderr, "Error reading KVpairs\n");
        return EXIT_FAILURE;
    }
    //count from 2 to argc (call the number you count i)
    for (int i = 2; i < argc; i++) {
        //count the values that appear in the file named by argv[i], using kv as the key/value pair
        counts_t *c = countFile(argv[i], pairs);
        //   (call this result c)
        //compute the output file name from argv[i] (call this outName)
        char *outName = computeOutputFileName(argv[i]);
        //open the file named by outName (call that f)
        FILE *f = fopen(outName, "w");
        if (f == NULL) {
            fprintf(stderr, "Error in file\n");
            return EXIT_FAILURE;
        }
        //print the counts from c into the FILE f
        printCounts(c, f);
        //close f
        fclose(f);
        //free the memory for outName and c
        free(outName);
        freeCounts(c);
    }
    //free the memory for kv
    freeKVs(pairs);
    return EXIT_SUCCESS;
}
