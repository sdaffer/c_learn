#include <stdio.h>
#include <stdlib.h>


// TODO: you need to allocate memory for dat_c_arr, but how to you do this if
// you don't know the size before reading the file? you can either do: 
//  a first pass over the file to get the number of values and then allocate
//  memory, and then loop over the file again to assign values to that memory.
// or:
//  you can keep reallocating memory thus growing the allocation dynamically. a
//  memory cheap way to do this is to double the ammount you reallocate every
//  time you reach the capacity of the current allocation.

// TODO: you'll have to deal with if the numbers in the file have too many or
// not enough digits.


typedef enum {
    LINE_COMMENT,
    LINE_DATA,
    // LINE_ERROR,  // don't really know how to implement this right now
    // LINE_EMPTY,  // don't really know how to implement this right now
} line_types;

typedef struct dat_arr {
    double* real_ptr;
    size_t len;  // int can overflow for large numbers. size_t avoids this
    size_t cap;  // allocaiton capacity
} dat_arr;

// int handle_mem_capacity(dat_c_arr** data, ) {

// }

line_types line_parser(char* line, double* val) {
    // TODO: add support for multiple columns
    // TODO: add support for LINE_ERROR and LINE_EMPTY
    if (line[0] == '#') {
        return LINE_COMMENT;
    } else {

        // we'll use the strtod() function because it's literally built to
        // parse a char* to a double. the second parameter of strtod() should be
        // a pointer to a pointer. why a pointer to a pointer? this is the only
        // way that c can modify a pointer when passing it into an argument.
        // this is exactly analogous to how we pass in a pointer to a value when
        // we want the function to modify the value. in this case, strtod()
        // wants to tell us where the next character in the first arugment
        // (a char*) after the numerical value is, and it does that by modifying
        // the pointer value of the second argument. we will need this if we
        // want to parse csv's with multiple columns to get rid of commas etc.
        // if we wanted to access the character that strtod() found at that
        // location after the numerical value and print it, we would do this:
        // printf("%c\n", *endptr);

        char* endptr;
        // TODO: strtod error checking
        *val = strtod(line, &endptr);
        return LINE_DATA;
    }
}

void read_csv(const char* f_path) {
    // TODO: implement parsing imaginary parts. currently only works for real
    // values.

    // define pointer of type FILE (from stdio.h)
    FILE* fptr;
    // fopen() on the path with read mode. it will return the pointer if
    // successful and NULL if not
    fptr = fopen(f_path, "r");
    if (fptr == NULL) {
        printf("error opening file '%s'\n", f_path);
        return;
    } else {
        char buffer[255];
        double val;
        size_t i = 0;
        dat_arr data = {NULL, 0, 1};

        // allocate for one value first
        data.real_ptr = malloc(data.cap*sizeof(*data.real_ptr));
        if (data.real_ptr == NULL) {
            fprintf(stderr, "memory allocation failed\n");
            return;
        }

        // TODO: gpt says that fgets can cause a truncation error for long lines
        // but getline() (POSIX) works with arbitrary line lengths? but it also
        // doesn't work on windows?
        while (fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), fptr)) {
            line_types type = line_parser(buffer, &val);
            if (type == LINE_DATA) {
                // printf("%f\n", val);
                // reallocate memory if we will be at or above capacity
                if (i + 1 > data.cap) {
                    data.cap = 2*data.cap;
                    double* new_ptr = realloc(data.real_ptr,
                        data.cap*sizeof(*data.real_ptr));
                    if (new_ptr == NULL) {
                        fprintf(stderr, "memory allocation failed\n");
                        return;
                    }
                    data.real_ptr = new_ptr;
                    printf("realloc()\n");
                }
                data.real_ptr[i] = val;
                i++;
                data.len = i; 
            }
        }
        fclose(fptr);

        // just checking if everything is correct here
        // for (size_t i = 0; i < data.len; i++) {
        //     printf("%f\n", data.real_ptr[i]);
        // }
        // printf("data.len = %d\n", data.len);
    }
}

void write_csv() {
    // TODO: needs to write 2d data because we have the real and imag parts.
    // TODO: later come back to try real and imaginary parts interleaved.
}