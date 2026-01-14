#include <stdio.h>

void file_reader(const char* f_name) {
    // the FILE type comes from the stdio.h library.
    // we want to create a FILE type pointer.
    FILE *fptr;
    fptr = fopen(f_name, "r");  // "r" mode creates a new file every time. if we
    // wanted to append, we would use mode "a", but i haven't gotten it to work
    // try to open the file with fopen. the value of fptr will be NULL if the
    // file can't be read.
    if (fptr == NULL) {
        printf("error opening file '%s'\n", f_name);
        return;
    } else {
        printf("opening file\n");
        char buffer[255];  // i think 255 because the null terminator is 1 char
        // while conditions are true of there is anything other than 0 or NULL,
        // and fgets returns NULL when there's an error or end of file, so
        // that's part of why this works.
        // also the char array called buffer undergoes pointer decay when it is
        // passed to fgets(). the function's signature does not have a
        // const char *, so the char array gets modified. we could also directly
        // include the address operator for the same result like this:
        // fopen(&buffer, ...)
        while (fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), fptr)) {
            printf("%s", buffer);
        }
        fclose(fptr);
    }
}

void file_writer(const char* f_name, const char* line_char_arr) {
    // the FILE type comes from the stdio.h library.
    // we want to create a FILE type pointer.
    FILE *fptr;
    fptr = fopen(f_name, "w");
    fprintf(fptr, "%s\n", line_char_arr);
    fclose(fptr);
    printf("file write success\n");
}

int main() {
    char f_name[] = "asdf.txt";
    file_writer(f_name, "line1");
    // we currently can't call the file writer twice unless we want to overwrite
    // the last write. so we shouldn't close the file until we are done writing
    // or use a different fopen() mode to append to the end of a file.
    file_writer(f_name, "line2");
    file_reader(f_name);
    return 0;
}