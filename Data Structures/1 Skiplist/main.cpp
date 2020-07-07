// Copyright Robert Lica robertlica21@gmail.com
#include "./Skiplist.h"
#include "./makeOperations.h"

int main() {
    char input_file[] = "races.in", output_file[] = "races.out";
    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");
    if (!in || !out) {
        fprintf(stderr, "ERROR: Nu s-a putut deschide unul dintre fisiere\n");
        return -1;
    }
    do_commands(in, out);
    fclose(in);
    fclose(out);
    return 0;
}
