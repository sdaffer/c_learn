#include "calc.h"

#include <math.h>
#include <stdio.h>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


dat_c_arr calc_dft(dat_c_arr* data) {
    dat_c_arr dft = {NULL, data->len, data->cap};
    dft.data_ptr = malloc(dft.cap*sizeof(*dft.data_ptr));
    for (size_t k = 0; k < dft.len; k += 2) {
        double sum_real = 0.0;
        double sum_imag = 0.0;
        for (size_t n = 0; n < dft.len; n += 2) {
            double xn = data->data_ptr[n];
            double arg = (M_PI*k*n)/dft.len;
            sum_real += xn*cos(arg);
            sum_imag += xn*sin(arg);
        }
        dft.data_ptr[k] = sum_real;
        dft.data_ptr[k+1] = sum_imag;
    }
    return dft;
}