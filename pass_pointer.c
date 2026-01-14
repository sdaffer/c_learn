#include <stdio.h>

void func_str_decay(char *str_ptr, int str_length) {
    // from here the char array decays into a pointer that points to the first
    // byte of the array in memory. i can print the memory address with printf()
    // by using the %p formatter. printf() understand this to mean to print
    // the memory address of the pointer.
    printf("str_ptr address = %p\n", str_ptr);

    // we can print the entire char array by giving the pointer for the first
    // byte of the array in memory to printf using the %s format flag. printf()
    // understands to print the char at each memory address until it finds the
    // null terminator '\0'.
    printf("printf() method:\n");
    printf("str_ptr = %s\n", str_ptr);

    // we can also print the string like this where we loop through each memory
    // address making sure to only go as far as one of the function parameters
    // says. notice that we subtract one from the string length because that
    // includes the null terminator '\0'.
    printf("for loop method:\n");
    for (int i = 0; i < str_length - 1; i++) {
        printf("%c", *str_ptr);
        str_ptr++;
    }
    printf("\n");

    // we can also basically do what printf("%s\n", str_ptr) is doing where
    // we loop through each memory address, grab the character, print it, and
    // only do it until we hit the null terminator.
    // we have to reset the pointer to the original memory address though
    // because we've already incremented it from the for loop before this
    str_ptr -= (str_length - 1);  // note the -1 again. see for loop comment.
    printf("while method:\n");
    while (*str_ptr != '\0') {
        printf("%c", *str_ptr);
        str_ptr++;
    }
    printf("\n");
}

void func_int(int *int_ptr) {
    *int_ptr += 3;
}

int main() {
    char input[] = "input string";
    int length = sizeof(input)/sizeof(input[0]);
    func_str_decay(input, length);

    int num = 12;
    printf("num = %d", num);
    // we pass in the address of num because the function is
    // supposed to take a pointer as a parameter
    func_int(&num);  
    // we should see that the value of num has now changed
    printf("num = %d", num);
    // i think this is how we would do functions with arrays and structs: we
    // would pass in pointers to those objects
    
    return 0;
}