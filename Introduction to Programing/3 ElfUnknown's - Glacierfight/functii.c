// Copyright Robert Lica robertlica21@gmail.com
#include "./functii.h"

void alloc_and_read(int ****matrix, FILE *in, int r) {
    *matrix = malloc((r * 2 + 1) * sizeof(int **));
    if (*matrix == NULL) {
        matrix = NULL;
        return;
    }
    for (int i = 0; i < r * 2 + 1; i++) {
        *(*matrix + i) = malloc((r * 2 + 1) * sizeof(int *));
        if (*(*matrix + i) == NULL) {
            matrix = NULL;
            return;
        }
        for (int j = 0; j < r * 2 + 1; j++) {
            *(*(*matrix + i) + j) = calloc(3, sizeof(int));
            if (*(*(*matrix + i) + j) == NULL) {
                matrix = NULL;
                return;
            }
            *(*(*(*matrix + i) + j) + 2) = -1;
            fscanf(in, "%d %d", (*(*(*matrix + i) + j) + 0),
                   (*(*(*matrix + i) + j) + 1));
        }
    }
}
