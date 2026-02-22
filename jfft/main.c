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

// int main() {
int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        printf("usage: ./jfft input.csv output.csv");
        return 1;
    }

    // TODO: need to properly set these. remember argv is a char**. see the
    // cl_args.c code in this repo to learn about this and you'll be able to
    // figure it out.
    char f_path_read[] = argv[1];
    char f_path_write[] = argv[2];
    // char f_path_read[] = "/home/jfeltman/data/test_funcs/10hz_3amp_10s.csv";
    // char f_path_write[] = "/home/jfeltman/data/test_funcs/10hz_3amp_10s_o.csv";

    // load data array from csv
    dat_c_arr data = read_csv_dat_c_arr(f_path_read);

    // calculate fourier transform
    dat_c_arr dft = calc_dft(&data);

    // write the fourier transform
    write_dat_c_arr_csv(&dft, f_path_write);

    // free the allocated memory
    free_null_dat_c_arr_mem(&data);
    free_null_dat_c_arr_mem(&dft);
    return 0;
}