#include "util.h"

#include <stdio.h>


double rmax_dat_c_arr(dat_c_arr* data) {
    double val = data->data_ptr[0];
    for (size_t i = 2; i < (data->len); i += 2) {
        if (data->data_ptr[i] > val) val = data->data_ptr[i];
    }
    return val;
}

double imax_dat_c_arr(dat_c_arr* data) {
    double val = data->data_ptr[1];
    for (size_t i = 3; i < (data->len); i += 2) {
        if (data->data_ptr[i] > val) val = data->data_ptr[i];
    }
    return val;
}