#include <stdio.h>

// argc is the number of cl args. argc are the actual arguments.
// argc will always be at least 1 because the program itself is a cl arg.

// note that char* argv[] and char** argv are exactly equivalent.
// also note that argv[argc] == NULL, so this is how the memory is structured:
// call: ./a.out hello world
// argc -> [ ptr -> "./a.out\0" ] -- this is argv[0]
//         [ ptr -> "hello\0"   ] -- this is argv[1]
//         [ ptr -> "world\0"   ] -- this is argv[2]
//         [ NULL               ] -- this is argv[3]
// so it's an array of pointers that point to char*'s (arrays of characters)
// that are terminated with the null terminator so the printf() function knows
// where to stop printing.


// int main(int argc, char* argv[]) {
int main(int argc, char** argv) {
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[i] = %s\n", argv[i]);
    }
    return 0;
}

// i wonder if they actually have to be acalled argc and argv.
// testing shows no. you can name them whatever you want.
// int main(int argc2, char* argv2[]) {
//     printf("argc2 = %d\n", argc2);
//     for (int i = 0; i < argc2; i++) {
//         printf("argv2[i] = %s\n", argv2[i]);
//     }
//     return 0;
// }