// functions for computing the discrete fourier transform

// struct for containing real and imaginary parts of the data and the size
typedef struct dat_c_arr {
    // apparently we can't define an array in the struct without specifying the
    // size:
    // double real_arr[]  // this is not allowed.
    // we could do it if the array was the last one specified in the struct. i
    // think this is because of how the stack vs. heap memory works. we wouldn't
    // be able to do this if we are using two arrays in the struct (one for real
    // and one for imaginary) because then we would have 2 flexible arrays
    // defined. we could do the interleaved data case where both parts are
    // in the same array in some structure, usually alternating.
    double* real_ptr;
    double* imag_ptr;
    int size;
} dat_c_arr;