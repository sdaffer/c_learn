#include <stdio.h>
#include <stdlib.h>

// TODO: you'll have to deal with if the numbers in the file have too many or
// not enough digits.

// TODO: understand gpt's code in the comments at the end. i really like that
// stucture better as long as i can understand it. there's some new stuff in
// there that i've never used before.


void line_parser(char* line) {
    // TODO: add support for multiple columns
    if (line[0] == '#') {
        printf("comment = '%s'\n", line);
        line = "";
        printf("comment = '%s'\n", line);
        return;
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
        double val = strtod(line, &endptr);
        return;
    }
}

void read_csv(const char* f_path) {
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
        while (fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), fptr)) {
            line_parser(buffer);
        }
        fclose(fptr);
    }
}

void write_csv() {
    // TODO: needs to write 2d data because we have the real and imag parts.
    // TODO: later come back to try real and imaginary parts interleaved.
}


// gpt code to understand:
// typedef enum {
    // LINE_EMPTY,
    // LINE_COMMENT,
    // LINE_DATA,
    // LINE_ERROR
// } line_type_t;

// line_type_t parse_line(
    // const char *line,
    // double *values,
    // size_t max_values,
    // size_t *num_values
// );

// #include <ctype.h>
// #include <errno.h>

// line_type_t parse_line(
    // const char *line,
    // double *values,
    // size_t max_values,
    // size_t *num_values
// ) {
    // *num_values = 0;

    // // skip leading whitespace
    // while (isspace((unsigned char)*line)) line++;

    // if (*line == '\0')
        // return LINE_EMPTY;

    // if (*line == '#')
        // return LINE_COMMENT;

    // char *end;
    // errno = 0;

    // double v = strtod(line, &end);

    // if (end == line || errno != 0)
        // return LINE_ERROR;

    // values[0] = v;
    // *num_values = 1;

    // return LINE_DATA;
// }

// void read_csv(const char *path) {
    // FILE *f = fopen(path, "r");
    // if (!f) {
        // perror("fopen");
        // return;
    // }

    // char buffer[256];
    // double values[16];
    // size_t n;

    // while (fgets(buffer, sizeof buffer, f)) {
        // line_type_t type = parse_line(buffer, values, 16, &n);

        // if (type == LINE_DATA) {
            // printf("value = %.10f\n", values[0]);
        // }
    // }

    // fclose(f);
// }
