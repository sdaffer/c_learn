#include <stdio.h>

// student struct
struct Student{
    char name[50];
    int age;
    float gpa;
};

// typedef student struct. basically allows you not have to specify that this
// is a struct every time you define a new variable of struct type
// Student_typedef
typedef struct Student_typedef{
    char name[50];
    int age;
    float gpa;
} std_td;

void set_name_from_char_arr(char name_in[], std_td *student_in){
    int n = sizeof(name_in)/sizeof(char); // FIXME: i think this doesn't work
    // because the char decays to a pointer, so i need to pass in the size of
    // the name somehow.
    for (int i = 0; i < n; i++){
        // (*student_in).name[i] = name_in[i];
        student_in->name[i] = name_in[i];
    }
}

int main(){
    // define new variable of type struct Student
    struct Student jake;
    jake.age = 30;
    jake.gpa = 4.0;
    printf("%i\n", jake.age);
    printf("%f\n\n", jake.gpa);

    // basically the same but with the typedef struct shorthand. define a new
    // variable of type std_td which is exactly the same as struct Student, but
    // i don't have to type struct Student.
    std_td jake_td;
    jake_td.age = 31;
    jake_td.gpa = 4.1;
    printf("%i\n", jake_td.age);
    printf("%f\n\n", jake_td.gpa);

    // try to set the name with a loop
    char name[6] = "JakeF.";
    set_name_from_char_arr(name, &jake_td);
    printf("%s\n\n", jake_td.name);

    // it's also possible to set the struct fields like this. i like this much
    // much better.
    std_td jerry_td = {.age = 40, .gpa = 3.2, .name = "Jerry"};
    printf("%i\n", jerry_td.age);
    printf("%f\n", jerry_td.gpa);
    printf("%s\n", jerry_td.name);

    printf("\ndone\n");
    return 0;
}