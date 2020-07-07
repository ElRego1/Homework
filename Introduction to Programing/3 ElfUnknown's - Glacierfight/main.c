// Copyright Robert Lica robertlica21@gmail.com
#include "./functii.h"

int main(int arg, char *argv[]) {
    char *file_in = calloc((strlen(argv[1])), sizeof(char));
    char *file_out = calloc((strlen(argv[1]) + 1), sizeof(char));
    memcpy(file_in, argv[1], strlen(argv[1]));
    memcpy(file_out, argv[1], strlen(argv[1]));
    int temp = strlen(argv[1]);
    file_out[temp - 2] = 'o';
    file_out[temp - 1] = 'u';
    file_out[temp] = 't';
    file_out[temp + 1] = '\0';
    int r, n;
    int ***matrix;
    elfs *v;
    if (arg < 2) {
        fprintf(stderr, "Nu s-a dat numele fisierului de citit!\n");
        return -1;
    }
    FILE *in = fopen(file_in, "rt");
    FILE *out = fopen(file_out, "wt");
    if (in == NULL || out == NULL) {
        fprintf(stderr, "Nu s-a putut deschide fisierul %s\n", argv[1]);
        return -1;
    }
    fscanf(in, "%d %d", &r, &n);
    v = malloc(n * sizeof(elfs));
    alloc_and_read(&matrix, in, r);
    if (matrix == NULL || v == NULL) {
        fprintf(stderr, "Nu s-a putut aloca memorie!\n");
        return -1;
    }
    int design = 0;
    read_elfs(matrix, v, in, out, r, n, &design);
    do_commands(&matrix, in, out, v, r, n, design);
    return 0;
}
