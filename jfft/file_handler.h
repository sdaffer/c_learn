#ifndef FILE_HANDLER_H  // if not already defined
#define FILE_HANDLER_H // then define this macro name


#include "data_structs.h"
#include <stddef.h>  // for size_t


#define MAX_ALLOC_SIZE 1000000000  // 1 GB


typedef enum {
    LINE_COMMENT,
    LINE_DATA,
    LINE_ERROR,
    // LINE_EMPTY,  // don't really know how to implement this right now
} line_types;


line_types line_parser(char* line, double* real_val, double* imag_val);
int handle_mem_cap(double** ptr_ptr, size_t len, size_t* cap, size_t max_cap);
dat_c_arr read_csv_dat_c_arr(const char* f_path);
int write_dat_c_arr_csv(dat_c_arr* data, char* f_path);


#endif  // end the if not defined for FILE_HANDLER_H