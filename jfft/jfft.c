#include <stdio.h>
#include <stdlib.h>

#include "calc.h"
#include "data_structs.h"
#include "file_handler.h"
#include "util.h"

// TODO: you should allow a command line argument to be the relative or full
// file path of the csv file containing the function

// TODO: figure out if we only ever plot the real part of an FFT?

// TODO: your code initially won't actually compute the FFT because that's a
// specific fourier transform algorithm. yours will just be a DFT at first.


void free_null_dat_c_arr_mem(dat_c_arr* data) {
    // is this the way to do this?
    free(data->data_ptr);
    data->data_ptr = NULL;
}

int main() {
    char f_path_read[] = "/home/jfeltman/data/test_funcs/10hz_3amp_10s.csv";
    char f_path_write[] = "/home/jfeltman/data/test_funcs/10hz_3amp_10s_o.csv";

    // load data array from csv
    dat_c_arr data = read_csv_dat_c_arr(f_path_read);

    // testing
    double max = rmax_dat_c_arr(&data);
    printf("max = %f\n", max);

    // calculate fourier transform
    dat_c_arr dft = calc_fourier_transform(&data);

    // testing
    double max_a = rmax_dat_c_arr(&dft);
    printf("max_a = %f\n", max_a);

    // write the fourier transfaorm
    // write_dat_c_arr_csv(&data, f_path_write);
    write_dat_c_arr_csv(&dft, f_path_write);

    // free the allocated memory
    free_null_dat_c_arr_mem(&data);
    free_null_dat_c_arr_mem(&dft);
    return 0;
}