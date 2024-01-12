#pragma once

#define LOG(msg) log_error(msg, __FILE__, __LINE__, __FUNCTION__);

typedef enum Errors
{
    E_INDEX_OUT_OF_BOUNDS,
    E_OBJECT_UNINITIALIZED,
    E_SEGMENTATION_FAULT
} Errors;

void log_error(Errors err, char* file, int line, const char* func);