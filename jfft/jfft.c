#include <stdio.h>

#include "file_handler.c"

// TODO: you should allow a command line argument to be the relative or full
// file path of the csv file containing the function

// TODO: figure out if we only ever plot the real part of an FFT?

// TODO: your code initially won't actually compute the FFT because that's a
// specific fourier transform algorithm. yours will just be a DFT at first.

int main() {
    char f_path[] = "/home/jfeltman/data/test_funcs/10hz_3amp_10s.csv";
    read_csv(f_path);
    return 0;
}