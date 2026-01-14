#include <stdio.h>

int main(){
    int num = 10; // variable with value

    //& operator means "address of", and * operator is the
    // indirection or dereference operator. it's both how you define a pointer
    // varialbe (such as i've done here) and dereference the pointer (pull the
    // value that lives at the memory address). a pointer is a variable that
    // stores a memory address as its value. i think it also has it's own
    // memory address.
    int *ptr = &num; //pointer variable of type int

    printf("num = %d\n", num);
    printf("the address of num should be = %p\n", &num);
    printf("the value of the pointer to this number is = %p\n", ptr);
    printf("the dereferenced pointer value is = %d\n", *ptr);

    return 0;
}