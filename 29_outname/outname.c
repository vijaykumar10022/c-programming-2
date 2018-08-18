#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
    char *outputName = malloc((strlen(inputName) + 8)*sizeof(*outputName));
    outputName = strcpy(outputName, inputName);
    outputName = strcat(outputName, ".counts\0");
    return outputName;
}
