#include <stdio.h>

void func(char *str_ptr, int str_length) {
    // from here the char array decays into a pointer that points to the first
    // byte of the array in memory. i can print the memory address with printf()
    // by using the %p formatter. printf() understand this to mean to print
    // the memory address of the pointer.
    printf("str_ptr address = %p\n", str_ptr);

    // we can print the entire char array by giving the pointer for the first
    // byte of the array in memory to printf using the %s format flag. printf()
    // understands to print the char at each memory address until it finds the
    // null terminator \0.
    printf("printf() method:\n");
    printf("str_ptr = %s\n", str_ptr);

    // we can also print the string like this where we loop through each memory
    // address making sure to only go as far as one of the function parameters
    // says
    printf("for loop method:\n");
    for (int i = 0; i < str_length; i++) {
        printf("%c", *str_ptr);
        str_ptr++;
    }
    printf("\n");

    // we can also basically do what printf("%s\n", str_ptr) is doing where
    // we loop through each memory address, grab the character, print it, and
    // only do it until we hit the null terminator.
    // we have to reset the pointer to the original memory address though
    // becuase we've already incremented it from the for loop before this
    str_ptr -= str_length;
    printf("while method:\n");
    while (*str_ptr != '\0') {
        printf("%c", *str_ptr);
        str_ptr++;
    }
    printf("\n");
}

int main() {
    char input[] = "input string";
    int length = sizeof(input)/sizeof(input[0]);
    func(input, length);
    return 0;
}