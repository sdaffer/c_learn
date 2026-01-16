#include <stdio.h>

typedef struct car {
    char model[50];
    float price;
} car;

void set_car_price(car *c, float price) {
    // these two are equivalent. the arrow operator is much nicer.
    // (*c).price = price;
    c->price = price;
}

int main() {
    car toyota = {.model = "camry", .price=35000};
    printf("%f\n", toyota.price);
    set_car_price(&toyota, 0.99);
    printf("%f\n", toyota.price);
    return 0;
}