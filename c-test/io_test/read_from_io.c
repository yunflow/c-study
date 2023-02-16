#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fP = fopen("grid", "r");

    int matrix[20][20] = {0};

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            fscanf(fP, "%d", &matrix[i][j]);
        }
    }
    
    fclose(fP);

    //print
    for (int m = 0; m < 20; m++) {
        for (int n = 0; n < 20; n++) {
            printf("%d ", matrix[m][n]);
        }
        printf("\n");
    }

    return 0;
}
