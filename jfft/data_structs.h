#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H


#include <stddef.h>


typedef struct dat_arr {
    double* real_ptr;
    size_t len;  // int can overflow for large numbers. size_t avoids this
    size_t cap;  // allocation capacity
} dat_arr;


#endif // DATA_STRUCTS_H