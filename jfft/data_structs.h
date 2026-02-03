#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H


#include <stddef.h>


typedef struct dat_c_arr {
    // double* real_ptr;
    // double* imag_ptr;
    double* data_ptr;  // 0: real 0, 1: imag 0, 2: real 1, 3: imag 1, ...
    size_t len;  // int can overflow for large numbers. size_t avoids this
    size_t cap;  // allocation capacity
} dat_c_arr;

#endif // DATA_STRUCTS_H