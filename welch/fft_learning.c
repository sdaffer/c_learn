// functions for computing the discrete fourier transform
#include <stdio.h>
#include <stdlib.h>  // this is for malloc and free
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
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
    double freq = 10;  // Hz
    double duration = 10;  // s
    int npts = duration/dt;

    // define the complex data struct
    dat_c_arr data;
    data.size = npts;


    // we need to malloc enough memory for all of the real and imaginary
    // pointers. we can do this in two ways, but one is more clear than the
    // other, but requires some knowledge about malloc.
    // this is the first way:
    // data.real_ptr = (double*)malloc(npts*sizeof(*data.real_ptr));
    // data.imag_ptr = (double*)malloc(npts*sizeof(*data.imag_ptr));
    // malloc returns a void* type--or a pointer to ONE location in memory of
    // unkown type. a void* can be cast to any other * type, so the (double*)
    // syntax casts the void* to a double* which is allowed. apparently, old
    // compilers might assume that malloc returns an int instead of a void* if
    // we don't include stdlib.h, so it's better to do it this way:
    data.real_ptr = malloc(npts*sizeof(*data.real_ptr));
    data.imag_ptr = malloc(npts*sizeof(*data.imag_ptr));
    // c apparently allows implicit conversion from void to any other type, so
    // we are implicity going from void* to the type of data.real_ptr and
    // data.imag_ptr which is double* which is allowed. also note that we are
    // allocating npts*sizeof(*data.XXXX_ptr) which in english means:
    // the number of pointers times the memory size of whatever data.XXXX_ptr
    // points to. that happens to be a double, so i could have said
    // sizeof(double), but my way prevents refactoring bugs if i changed to a
    // different type and forgot to change the type in all places.

    // apparently checking for memory allocation success is critical because
    // it can certainly fail and the behavior after failure can be incredibly
    // difficult to diagnose. malloc will return NULL on failure.
    if (data.real_ptr == NULL || data.imag_ptr == NULL) {
        // notice we are using fprintf(). fprintf() works like printf but you
        // choose the output stream. there are three standard output streams in
        // c: stdin (usually keyboard input), stdout (output terminal, file,
        // pipe), and std error (terminal only). stdout is the stream that
        // printf() uses, but we want our error messages to be in the stderr
        // stream because we don't want them to get mixed in with regular
        // output. if we piped the output of our program into a file and used
        // regular old printf(), then the error messages would be mixed into the
        // file. error messages should use the stderr stream.
        fprintf(stderr, "memory allocation failed\n");
        return 1;
    }

    // now we need to fill our memory with something
    for (int i = 0; i < npts; i++) {
        double t = dt*i;
        // remember that ptr[i] is exactly the same as *(ptr + i), so there's
        // no need to dereference here because the [] operator already does it.
        // i think there's no such thing as an array without pointers, so that's
        // why you should always see [] as a dereference--anything that can be
        // indexed with [] always a pointer.
        data.real_ptr[i] = sin(2*M_PI*freq*t);
        data.imag_ptr[i] = 0.0;
    }

    // do FFT stuff

    // and we need to free the memory at the end
    free(data.real_ptr);
    free(data.imag_ptr);

    printf("success!\n");

    return 0;
}