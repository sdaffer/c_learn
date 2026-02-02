#include <stdio.h>
#include <stdlib.h>

#include "file_handler.h"
#include "data_structs.h"

// TODO: you should allow a command line argument to be the relative or full
// file path of the csv file containing the function

// TODO: figure out if we only ever plot the real part of an FFT?

// TODO: your code initially won't actually compute the FFT because that's a
// specific fourier transform algorithm. yours will just be a DFT at first.

// TODO: make this work by passing in data_c_arr
// void free_null_data_arr_mem(void** ptr_ptr) {
//     free(*ptr_ptr);
//     *ptr_ptr = NULL;
// }

void free_null_dat_c_arr_mem(dat_c_arr* data) {
    // is this the way to do this?
    free(data->real_ptr);
    free(data->imag_ptr);
    data->real_ptr = NULL;
    data->imag_ptr = NULL;
}

int main() {
    char f_path_read[] = "/home/jfeltman/data/test_funcs/10hz_3amp_10s.csv";
    char f_path_write[] = "/home/jfeltman/data/test_funcs/10hz_3amp_10s_o.csv";
    dat_c_arr data = read_csv_dat_c_arr(f_path_read);  // free the array when done;
    write_dat_c_arr_csv(&data, f_path_write);
    free_null_dat_c_arr_mem(&data);
    return 0;
}