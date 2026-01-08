#include <stdio.h>


// #define array_size(x) (sizeof(x)/sizeof(x[0]));
#define array_size(x) (sizeof(x)/sizeof(x[0]));

int main() {
    
    int arr[] = {2, 4, 8, 12, 16, 18};
    char test_str[] = "test string";
    // printf("%s\n", test_str);
    // int n = sizeof(arr)/sizeof(arr[0]);
    // int n = sizeof(test_str)/sizeof(char);
    int n = array_size(test_str);
    for (int i = 0; i < n; i++){
        printf("%c\n", test_str[i]);
    }
    return 0;
}