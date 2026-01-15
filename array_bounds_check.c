#include <stdio.h>

// defining arrays with this struct structure is the way to go apparently. this
// is called runtime bounds checking because we will use the length and capacity
// to make sure we don't access out of bounds memory information.
// https://youtu.be/9UIIMBqq1D4?t=1201
// according to that video, runtime bounds checking wasn't a standard practice
// in the early days because there were significant resource restrictions. that
// really isn't an issue today.
typedef struct {
    int* items; // a pointer to the first item in memory.
    int length; // the length, how many items are currently in the array
    int capacity;  // the capacity, how much the array can hold. not sure how
    // to use this yet because i think i'm using a static array structure.
} intarray;

// this function will return 0 if we index out of bounds
int get_item(intarray arr, int index) {
    if (index >= 0 && index < arr.length) {
        // notice in the following line how we don't need to access the items
        // of the array by arr.*items[index]. this is because the [] operator
        // already does the dereferencing for us. this is the definition:
        // a[i] = *(a + i)
        // so a[i] means dereference the pointer at position a + i.
        return arr.items[index];
    }
    else {
        return 0;
    }
}

void itr_items(intarray arr) {
    for (int i = 0; i < arr.length; i++) {
        printf("get_item(arr, i) = %d\n", get_item(arr, i));
    }
}

int main() {
    intarray arr;
    // we can use a compound literal to assign arr.items:
    arr.items = (int[]){6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    // notice that we can't calculate the length by accessing arr.items because
    // it's just a pointer. we lose all information about the object when it
    // becomes a pointer, so this calculation is incorrect:
    printf("sizeof(arr.items)/sizeof(arr.items[0]) = %d\n",
        sizeof(arr.items)/sizeof(arr.items[0]));

    // a better way to assign the items is this because we can calculate the
    // length:
    int data[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    arr.items = data;
    arr.length = sizeof(data)/sizeof(data[0]);
    // this will correctly calculate the length
    printf("arr.length = %d\n", arr.length);

    // now lets call our function
    itr_items(arr);
    return 0;
}