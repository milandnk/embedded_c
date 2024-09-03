#include <stdio.h>

int main() {
    int n_student = 3;
    int n_subject = 4;
    int marks[3][4];

    for (int i = 0; i < n_student; i++) {
        for (int j = 0; j < n_subject; j++) {
            printf("Enter mark for student %d and subject %d: ", i + 1, j + 1);
            scanf("%d", &marks[i][j]);
        }
    }

    // Displaying the entered marks
    for (int i = 0; i < n_student; i++) {
        for (int j = 0; j < n_subject; j++) {
            printf("Mark of student %d and subject %d: %d\n", i + 1, j + 1, marks[i][j]);
        }
    }

    return 0;
}
