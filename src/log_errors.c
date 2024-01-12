#include <stdio.h>
#include <stdlib.h>

#include "../include/log_errors.h"

void log_error(Errors err, char* file, int line, const char* func) {
    switch (err)
    {   
        case E_INDEX_OUT_OF_BOUNDS:
            fprintf(stderr, "%s:%d error: Index out of bounds.\n\t\t~> function:%s\n", file, line, func);
            break;
        case E_OBJECT_UNINITIALIZED:
            fprintf(stderr, "%s:%d error: Object uninitialized / destroyed.\n\t\t~> function:%s\n", file, line, func);
            break;
        case E_SEGMENTATION_FAULT:
            fprintf(stderr, "%s:%d error: Segmentation fault: Accessing memory outside the given memory of the program.\n\t\t~> function:%s\n", file, line, func);
            break;
    }
    exit(EXIT_FAILURE);
}