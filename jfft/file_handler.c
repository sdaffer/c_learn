#include "file_handler.h"

#include <stdio.h>
#include <stdlib.h>

#include "data_structs.h"


// TODO: you'll have to deal with if the numbers in the file have too many or
// not enough digits.

// TODO: change the read file to a complex dat_c_arr, but only load the real
// part. so everything needs to be complex.


#define MAX_ALLOC_SIZE 1000000000  // 1 Gb


line_types line_parser(char* line, double* real_val, double* imag_val) {
    // parses the line as real, imaginary and erros if there are more ','.
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
        *real_val = strtod(line, &endptr);
        if (*endptr == ',') {
            *imag_val = strtod(endptr+1, &endptr); // ?
        } else {
            *imag_val = 0.0;
        }
        // we only support 2 columns
        if (*endptr == ',') {return LINE_ERROR;}
        return LINE_DATA;
    }
}
int handle_mem_cap(double** ptr_ptr, size_t len, size_t* cap, size_t max_cap) {
    if (len + 2 > *cap) {
        // size_t new_cap = 2*(*cap);  // double the capacity for dynamic alloc.
        size_t new_cap = 4*(*cap);  // double the capacity for dynamic
        // allocation of memory, but remember we have two numbers (real and
        // imag parts), so we need to multiply by 4.
        // check to make sure we aren't trying to allocate more than max size
        if (*cap == max_cap) return -1;
        if (new_cap > max_cap) new_cap = MAX_ALLOC_SIZE;
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

dat_c_arr read_csv_dat_c_arr(const char* f_path) {

    dat_c_arr data = {NULL, 0, 0};

    // define pointer of type FILE (from stdio.h)
    FILE* fptr;
    // fopen() on the path with read mode. it will return the pointer if
    // successful and NULL if not
    fptr = fopen(f_path, "r");
    if (fptr == NULL) {
        printf("error opening file '%s'\n", f_path);
        return data;
    }

    char buffer[255];
    double real_val;
    double imag_val;
    size_t i = 0;
    size_t max_cap = MAX_ALLOC_SIZE/sizeof(*data.data_ptr);
    data.cap = 1; // mem alloc alg. can't have this be 0.

    // allocate for one value first
    data.data_ptr = malloc(data.cap*sizeof(*data.data_ptr));
    if (data.data_ptr == NULL) {
        fprintf(stderr, "memory allocation failed\n");
        return data;
    }

    // NOTE: gpt says that fgets can cause a truncation error for long lines
    // (because the buffer can overflow, but getline() (POSIX) works with
    // arbitrary line lengths? but it also doesn't work on windows.
    while (fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), fptr)) {
        line_types type = line_parser(buffer, &real_val, &imag_val);
        if (type == LINE_DATA) {
            // realocate memory if adding this value to the array will put us
            // above our current memory allocation
            handle_mem_cap(&data.data_ptr, data.len, &data.cap, max_cap);
            data.data_ptr[i] = real_val;
            data.data_ptr[i+1] = imag_val;
            i += 2;
            data.len = i; 
            }
        }
    // reallocate to the exact amount of memory you need now that you know
    // exactly how much you need.
    double* new_ptr = realloc(data.data_ptr, i*sizeof(data.data_ptr[0]));
    if (new_ptr == NULL) {
        fprintf(stderr, "memory allocation failed\n");
    }
    data.data_ptr = new_ptr;
    data.cap = i;

    fclose(fptr);
    // TODO: free memory when done

    return data;
}

int write_dat_c_arr_csv(dat_c_arr* data, char* f_path) {
    // TODO: write the imaginary part in the second column
    FILE* fptr;
    fptr = fopen(f_path, "w");
    if (fptr == NULL) {
        printf("error opening file '%s'\n", f_path);
        return -1;
    }

    // write the header
    fprintf(fptr, "# real,imag\n");

    // output up to the last line because we don't want a \n on the last line
    // for (size_t i = 0; i < data->len - 1; i++){
    // for (size_t i = 0; i < data->len - 1; i += 2){
    for (size_t i = 0; i < data->len - 2; i += 2){
        fprintf(fptr, "%f,", data->data_ptr[i]);
        fprintf(fptr, "%f\n", data->data_ptr[i+1]);
    }
    // output the last line without a \n
    // FIXME: this is a problem
    // fprintf(fptr, "%f", data->data_ptr[data->len - 1]);
    fprintf(fptr, "%f,", data->data_ptr[data->len - 2]);
    fprintf(fptr, "%f", data->data_ptr[data->len - 2]);
    fclose(fptr);
    return 0;
}