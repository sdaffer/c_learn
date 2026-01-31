#include <stdio.h>
#include <stdlib.h>

#include "file_handler.h"
#include "data_structs.h"

// TODO: you should allow a command line argument to be the relative or full
// file path of the csv file containing the function

// TODO: figure out if we only ever plot the real part of an FFT?

// TODO: your code initially won't actually compute the FFT because that's a
// specific fourier transform algorithm. yours will just be a DFT at first.

void free_null_data_arr_mem(void** ptr_ptr) {
    free(*ptr_ptr);
    *ptr_ptr = NULL;
}

int main() {
    char f_path[] = "/home/jfeltman/data/test_funcs/10hz_3amp_10s.csv";
    dat_arr data = read_csv(f_path);  // free the array when done;
    free_null_data_arr_mem((void**) &data.real_ptr);
    return 0;
}