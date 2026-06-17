#include <stdio.h>
#include <string.h>

int main() {
    char password[50];

    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(password, "1234") == 0) {
        printf("You Pass\n");
    } else {
        printf("Try Next Time\n");
    }

    return 0;
}