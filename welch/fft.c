// functions for computing the discrete fourier transform
#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // this is for malloc and free

#ifndef M_PI
#define M_PI = 3.14159265358979323846
#endif

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

int main() {
    double dt = 0.001;  // f = 1 kHz
    double duration = 10;  // s
    int npts = duration/dt;

    // define the complex data struct
    dat_c_arr data;
    data.size = npts;

    // malloc
    // data.real_ptr = ();
    // dat_c_arr dat_arr = {.real_ptr = float}

    // understand this code:

    // 2. Allocate memory on the HEAP
    // Since npts can be large, malloc is safer than stack arrays
    // data.real_ptr = (double*)malloc(sizeof(double) * npts);
    // data.imag_ptr = (double*)malloc(sizeof(double) * npts);

    // // Check if memory allocation succeeded
    // if (data.real_ptr == NULL || data.imag_ptr == NULL) {
        // fprintf(stderr, "Memory allocation failed!\n");
        // return 1;
    // }

    // // 3. Initialize with a sample sine wave
    // for (int i = 0; i < npts; i++) {
        // double t = i * dt;
        // data.real_ptr[i] = sin(2 * M_PI * 10 * t); // 10Hz signal
        // data.imag_ptr[i] = 0.0;                   // Imaginary part starts at 0
    // }

    // printf("Struct initialized with %d points.\n", data.size);

    // // DON'T FORGET: Free the memory when done
    // free(data.real_ptr);
    // free(data.imag_ptr);




    return 0;
}