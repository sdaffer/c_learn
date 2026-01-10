#include <stdio.h>

void safe_strcpy(char *src, char *dest, int dest_size) {
    int length = sizeof(*src)/sizeof(char);
    if (dest_size <= 0) {
        printf("dest_size is <= 0.");
        return;
    }
    int count = 0;
    while (*src != '\0' && count < (dest_size - 1)) {
        *dest = *src;
        dest++;
        src++;
        count++;
    }
    *dest = '\0';
    return;
}

int main() {
    char src_var[] = "source string\n";
    int src_size = sizeof(src_var)/sizeof(char);
    char dest_var[src_size];
    printf("source_var = %s\n", src_var);
    printf("dest_var before = %s\n", dest_var);
    safe_strcpy(src_var, dest_var, sizeof(dest_var)/sizeof(char));
    printf("dest_var after = %s\n", dest_var);
    return 0;
}