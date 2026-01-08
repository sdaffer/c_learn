#include <stdio.h>

int main(){
    int num = 10;
    int * ptr = &num;
    printf("%p\n", ptr);
    printf("%i\n", * ptr);
    return 0;
}