#include <stdio.h>
#include <stdlib.h>


// TODO: you'll have to deal with if the numbers in the file have too many or
// not enough digits.


#define MAX_ALLOC_SIZE 1000000000  // 1 Gb


typedef enum {
    LINE_COMMENT,
    LINE_DATA,
    // LINE_ERROR,  // don't really know how to implement this right now
    // LINE_EMPTY,  // don't really know how to implement this right now
} line_types;

typedef struct dat_arr {
    double* real_ptr;
    size_t len;  // int can overflow for large numbers. size_t avoids this
    size_t cap;  // allocation capacity
} dat_arr;


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
int handle_mem_cap(double** ptr_ptr, size_t len, size_t* cap) {
    if (len + 1 > *cap) {
        size_t new_cap = 2*(*cap);
        // check to make sure we aren't trying to allocate more than max size
        // TODO: we probably want to fix this because if we are always doubling
        // then when we currently have a bit more than half the max size, this
        // check will cause return -1. how else can we handle this?
        if (new_cap > MAX_ALLOC_SIZE/sizeof(**ptr_ptr)) return -1;
        double* new_ptr = realloc(*ptr_ptr, new_cap*sizeof(**ptr_ptr));
        if (new_ptr == NULL) {
            fprintf(stderr, "memory allocation failed\n");
            return -1;
        }
        *cap = new_cap;
        *ptr_ptr = new_ptr;
    }
    return 0;
}

int read_csv(const char* f_path) {
    // define pointer of type FILE (from stdio.h)
    FILE* fptr;
    // fopen() on the path with read mode. it will return the pointer if
    // successful and NULL if not
    fptr = fopen(f_path, "r");
    if (fptr == NULL) {
        printf("error opening file '%s'\n", f_path);
        return -1;
    }

    char buffer[255];
    double val;
    size_t i = 0;
    dat_arr data = {NULL, 0, 1};

    // allocate for one value first
    data.real_ptr = malloc(data.cap*sizeof(*data.real_ptr));
    if (data.real_ptr == NULL) {
        fprintf(stderr, "memory allocation failed\n");
        return -1;
    }

    // NOTE: gpt says that fgets can cause a truncation error for long lines
    // (because the buffer can overflow, but getline() (POSIX) works with
    // arbitrary line lengths? but it also doesn't work on windows.
    while (fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), fptr)) {
        line_types type = line_parser(buffer, &val);
        if (type == LINE_DATA) {
            // realocate memory if adding this value to the array will put us
            // above our current memory allocation
            handle_mem_cap(&data.real_ptr, data.len, &data.cap);
            data.real_ptr[i] = val;
            i++;
            data.len = i; 
            }
            // data.real_ptr[i] = val;
            // i++;
            // data.len = i; 
        }
    fclose(fptr);
    // TODO: free memory when done
    printf("success\n");
    return 0;
}

void write_csv() {
    // TODO: needs to write 2d data because we have the real and imag parts.
    // TODO: later come back to try real and imaginary parts interleaved.
}