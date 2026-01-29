#include <stdio.h>

typedef enum {
    BRICK, // = 0
    WOOD, // = 1
    COPPER, // = 2
    SILVER=5, // = 5
    ONYX, // = 6
} resource;

int main() {
    resource r;
    r = BRICK;
    printf("r = %d\n", r);
    r = WOOD;
    printf("r = %d\n", r);
    r = COPPER;
    printf("r = %d\n", r);
    r = 300;
    printf("r = %d\n", r);
    // notice how we can't make r a float? that's because enums are just ints.
    r = 300.1;
    printf("r = %f\n", r);
}