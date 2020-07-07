// Copyright Robert Lica robertlica21@gmail.com
#include "./spiridusi.h"

#define INCR 10

void do_commands(int ****matrix, FILE *in, FILE *out, elfs *v, int r,
                 int n, int design) {
    int exit = 0;
    char comand[18], c;
    unsigned char i = 0;
    fscanf(in, "%c", &c);
    if (check_remaining(*matrix, out, v, r, &design) == 0 ||
            feof(in) != 0) {
        fprintf(out, "\n");
        free_matrix(matrix, r);
        free_elfs(v, n);
        fclose(in);
        fflush(out);
        fclose(out);
        return;
    }
    while (1) {
        c = 'A';
        i = 0;
        while (1) {
            fscanf(in, "%c", &c);
            if (feof(in) != 0) {
                exit = 1;
                break;
            }
            if (c != ' ' && c != '\n') {
                comand[i] = c;
                i++;
            } else {
                break;
            }
        }
        comand[i] = '\0';
        if (comand[0] == 'M' && comand[1] == 'O') {
            do_move(*matrix, in, out, v, r, n, &design);
        } else if (comand[0] == 'M' && comand[1] == 'E') {
            do_meltdown(matrix, in, out, v, &r, n, &design);
        } else if (comand[0] == 'S') {
            do_snowstorm(*matrix, in, out, v, r, n, &design);
        } else if (comand[0] == 'P') {
            if (design == 1) {
                fprintf(out, "\n");
            } else {
                design = 1;
            }
            fprintf(out, "SCOREBOARD:");
            do_scoreboard(out, v, n, &design);
        }
        fflush(out);
        for (int j = 0; j < 18; j++) {
            comand[j] = '0';
        }
        if (check_remaining(*matrix, out, v, r, &design) == 0 ||
                feof(in) != 0) {
            break;
        }
    }
    fprintf(out, "\n");
    free_matrix(matrix, r);
    free_elfs(v, n);
    fclose(in);
    fflush(out);
    fclose(out);
}

void do_scoreboard(FILE *out, elfs *v, int n, int *design) {
    int *ordered = malloc(n * sizeof(int));
    if (ordered == NULL) {
        fprintf(stderr, "Nu s-a putut aloca memorie!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        ordered[i] = i;
    }
    make_order(ordered, v, n);
    print_dry_wet(out, ordered, v, n, design);
    free(ordered);
}

void print_dry_wet(FILE *out, int *ordered, elfs *v, int n, int *design) {
    int most_kills = 0;
    for (int i = 0; i < n; i++) {
        if (v[i].kills > most_kills) {
            most_kills = v[i].kills;
        }
    }
    int save = most_kills;
    while (most_kills >= 0) {
        for (int i = 0; i < n; i++) {
            if (v[ordered[i]].hp > 0 && v[ordered[i]].kills == most_kills) {
                if (*design == 1) {
                    fprintf(out, "\n");
                } else {
                    *design = 1;
                }
                fprintf(out, "%s\tDRY\t%d", v[ordered[i]].nume,
                        v[ordered[i]].kills);
            }
        }
        most_kills--;
    }
    most_kills = save;
    while (most_kills >= 0) {
        for (int i = 0; i < n; i++) {
            if (v[ordered[i]].hp <= 0 && v[ordered[i]].kills == most_kills) {
                if (*design == 1) {
                    fprintf(out, "\n");
                } else {
                    *design = 1;
                }
                fprintf(out, "%s\tWET\t%d", v[ordered[i]].nume,
                        v[ordered[i]].kills);
            }
        }
        most_kills--;
    }
}

void make_order(int *ordered, elfs *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(v[ordered[j]].nume, v[ordered[j + 1]].nume) > 0) {
                ordered[j] = ordered[j] + ordered[j + 1];
                ordered[j + 1] = ordered[j] - ordered[j + 1];
                ordered[j] = ordered[j] - ordered[j + 1];
            }
        }
    }
}

void do_meltdown(int ****matrix, FILE *in, FILE *out, elfs *v, int *r,
                 int n, int *design) {
    int stamina, ***matrix_simple = *matrix;
    fscanf(in, "%d", &stamina);
    char c;
    fscanf(in, "%c", &c);
    for (int i = 0; i < n; i++) {
        if (v[i].hp <= 0) {
            continue;
        }
        if (check_melting(*r, v[i].x, v[i].y)) {
            v[i].stamina += stamina;
        } else {
            v[i].hp = 0;
            matrix_simple[v[i].x][v[i].y][2] = -1;
            if (*design == 1) {
                fprintf(out, "\n");
            } else {
                *design = 1;
            }
            fprintf(out, "%s got wet because of global warming.", v[i].nume);
        }
    }
    *matrix = do_shrink_iceberg(matrix, v, r);
    if (*matrix == NULL) {
        fprintf(stderr, "Nu s-a putut aloca memorie");
        return;
    }
}

int ***do_shrink_iceberg(int ****matrix, elfs *v, int *r) {
    int ***temp, ***matrix_simple = *matrix;
    temp = malloc(((*r - 1) * 2 + 1) * sizeof(int**));
    if (temp == NULL) {
        *matrix == temp;
        return NULL;
    }
    for (int i = 0; i < (*r - 1) * 2 + 1; i++) {
        temp[i] = malloc(((*r - 1) * 2 + 1) * sizeof(int*));
        if (temp[i] == NULL) {
            *matrix = NULL;
            return NULL;
        }
        for (int j = 0; j < (*r - 1) * 2 + 1; j++) {
            temp[i][j] = calloc(3, sizeof(int));
        }
    }

    for (int i = 0; i < (*r - 1) * 2 + 1; i++) {
        for (int j = 0; j < (*r - 1) * 2 + 1; j++) {
            temp[i][j][0] = matrix_simple[i + 1][j + 1][0];
            temp[i][j][1] = matrix_simple[i + 1][j + 1][1];
            temp[i][j][2] = matrix_simple[i + 1][j + 1][2];
            if (v[temp[i][j][2]].hp > 0) {
                v[temp[i][j][2]].x = i;
                v[temp[i][j][2]].y = j;
            }
        }
    }
    for (int i = 0; i < (*r) * 2 + 1; i++) {
        for (int j = 0; j < (*r) *2 + 1; j++) {
            free(*(*(*matrix + i) + j));
        }
        free(*(*matrix + i));
    }
    free(*matrix);
    *r -= 1;
    return temp;
}

void do_snowstorm(int ***matrix, FILE *in, FILE *out, elfs *v, int r,
                  int n, int *design) {
    // x y r dmg
    unsigned char decoded[4] = {0};
    read_K(in, decoded);
    for (int i = 0; i < n; i++) {
        if (v[i].hp <= 0) {
            continue;
        }
        if (check_hit(decoded, v[i].x, v[i].y)) {
            if (v[i].hp - decoded[3] <= 0) {
                if (*design == 1) {
                    fprintf(out, "\n");
                } else {
                    *design = 1;
                }
                fprintf(out, "%s was hit by snowstorm.", v[i].nume);
                v[i].hp = 0;
                matrix[v[i].x][v[i].y][2] = -1;
            } else {
                v[i].hp -= decoded[3];
            }
        }
    }
}

int check_hit(unsigned char decoded[4], int x, int y) {
    if (decoded[0] == x && decoded[1] == y && decoded[2] == 0) {
        return 1;
    } else if ((x - decoded[0]) * (x - decoded[0]) +
               (y - decoded[1]) * (y - decoded[1]) <=
               decoded[2] * decoded[2]) {
        return 1;
    }
    return 0;
}

void read_K(FILE *in, unsigned char decoded[4]) {
    unsigned int k;
    fscanf(in, "%d", &k);
    // x
    decoded[0] = k & 0xff;
     k = k>>8;
    // y
    decoded[1] = k & 0xff;
    k = k>>8;
    // r
    decoded[2] = k & 0xff;
    k = k>>8;
    // dmg
    decoded[3] = k & 0xff;
}

void do_move(int ***matrix, FILE *in, FILE *out, elfs *v, int r,
             int n, int *design) {
    char *p = NULL, c;
    int id;
    fscanf(in, "%d", &id);
    if (v[id].hp <= 0) {
        fscanf(in, "%c", &c);
        while (c != '\n' && feof(in) == 0) {
            fscanf(in, "%c", &c);
        }
        return;
    }
    get_moves(&p, in);
    make_move(matrix, p, v, out, &(v[id]), r, design);
}

void make_move(int ***matrix, char *p, elfs *v, FILE *out, elfs *e, int r,
               int *design) {
    for (unsigned int i = 0; i < strlen(p); i++) {
        if (p[i] != 'U' && p[i] != 'D' && p[i] != 'L' && p[i] != 'R') {
            continue;
        }
        if (p[i] == 'U') {
            if (check_stamina(matrix, e, r, e->x - 1, e->y)) {
                e->x--;
            } else {
                continue;
            }
        } else if (p[i] == 'D') {
            if (check_stamina(matrix, e, r, e->x + 1, e->y)) {
                e->x++;
            } else {
                continue;
            }
        } else if (p[i] == 'L') {
            if (check_stamina(matrix, e, r, e->x, e->y - 1)) {
                e->y--;
            } else {
                continue;
            }
        } else if (p[i] == 'R') {
            if (check_stamina(matrix, e, r, e->x, e->y + 1)) {
                e->y++;
            } else {
                continue;
            }
        }
        if (check_landing(r, e->x, e->y)) {
                    if (matrix[e->x][e->y][1] > e->manusi) {
                        matrix[e->x][e->y][1] =
                                matrix[e->x][e->y][1] + e->manusi;
                        e->manusi = matrix[e->x][e->y][1] - e->manusi;
                        matrix[e->x][e->y][1] =
                                matrix[e->x][e->y][1] - e->manusi;
                    }
                    if (matrix[e->x][e->y][2] != -1) {
                        if (fight(e, &(v[matrix[e->x][e->y][2]]),
                                  out, design) > 0) {
                            matrix[e->x][e->y][2] = e->id;
                        }
                        break;
                    } else {
                        matrix[e->x][e->y][2] = e->id;
                    }
                } else {
                    e->hp = 0;
                    if (*design == 1) {
                        fprintf(out, "\n");
                    } else {
                        *design = 1;
                    }
                    fprintf(out, "%s fell off the glacier.", e->nume);
                    break;
                }
    }
    free(p);
}

int fight(elfs *e1, elfs *e2, FILE *out, int *design) {
    if (e1->stamina < e2->stamina) {
        e1->hp -= e2->manusi;
    }
    if (e1->hp <= 0) {
        if (*design == 1) {
            fprintf(out, "\n");
        } else {
            *design = 1;
        }
        fprintf(out, "%s sent %s back home.", e2->nume, e1->nume);
        e2->stamina += e1->stamina;
        e2->kills++;
        e1->hp = 0;
        return -1;
    }
    while (1) {
        e2->hp -= e1->manusi;
        if (e2->hp <= 0) {
            if (*design == 1) {
                fprintf(out, "\n");
            } else {
                *design = 1;
            }
            fprintf(out, "%s sent %s back home.", e1->nume, e2->nume);
            e1->stamina += e2->stamina;
            e1->kills++;
            e2->hp = 0;
            return 1;
        }
        e1->hp -= e2->manusi;
        if (e1->hp <= 0) {
            if (*design == 1) {
                fprintf(out, "\n");
            } else {
                *design = 1;
            }
            fprintf(out, "%s sent %s back home.", e2->nume, e1->nume);
            e2->stamina += e1->stamina;
            e2->kills++;
            e1->hp = 0;
            return -1;
        }
    }
}

int check_stamina(int ***matrix, elfs *e, int r, int x, int y) {
    // aici fac o chestie periculoasa
    if (x < 0 || y < 0 || x >= r * 2 + 1 || y >= r * 2 + 1) {
        matrix[e->x][e->y][2] = -1;
        return 1;
    }
    if (abs(matrix[e->x][e->y][0] - matrix[x][y][0]) > e->stamina) {
        return 0;
    } else {
        matrix[e->x][e->y][2] = -1;
        e->stamina -= abs(matrix[e->x][e->y][0] - matrix[x][y][0]);
        return 1;
    }
}

void get_moves(char **p, FILE *in) {
    int n = INCR, i = 0;
    char c, *tmp;
    fscanf(in, "%c", &c);
    *p = malloc(n * sizeof(char));

    if (*p == NULL) {
        fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
        return;
    }
    while (1) {
        if (n == i) {
            n += INCR;
            tmp = realloc(*p, n * sizeof(char));
            if (tmp != NULL) {
                *p = tmp;
            } else {
                fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
                return;
            }
        }
        fscanf(in, "%c", &c);
        if (feof(in) != 0 || c == '\n') {
            break;
        }
        *(*p + i * sizeof(char)) = c;
        i++;
    }
    if (n == i) {
        tmp = realloc(*p, (n + 1) * sizeof(char));
        if (tmp != NULL) {
            *p = tmp;
        } else {
            fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
            return;
        }
    }
    *(*p + i * sizeof(char)) = '\0';
}

void read_elfs(int ***matrix, elfs *v, FILE *in, FILE *out, int r, int n,
                int *design) {
    for (int i = 0; i < n; i++) {
        v[i].id = i;
        read_name(&(v[i].nume), in);
        fscanf(in, "%d %d %d %d", &v[i].x, &v[i].y, &v[i].hp, &v[i].stamina);
        v[i].kills = 0;
        if (!check_landing(r, v[i].x, v[i].y)) {
            // spiridusul a aterizat in apa
            if (*design == 1) {
                fprintf(out, "\n");
            } else {
                *design = 1;
            }
            fprintf(out, "%s has missed the glacier.", v[i].nume);
            v[i].hp = 0;
            v[i].manusi = 0;
        } else {
            v[i].manusi = matrix[v[i].x][v[i].y][1];
            matrix[v[i].x][v[i].y][1] = 0;
            matrix[v[i].x][v[i].y][2] = i;
        }
    }
}

void read_name(char **nume, FILE *in) {
    char c, *tmp;
    int n = INCR, i = 0;
    // scapam de \n
    fscanf(in, "%c", &c);
    *nume = malloc(n * sizeof(char));
    if (*nume == NULL) {
        fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
        return;
    }
    while (c != ' ') {
        if (n == i) {
            n += INCR;
            tmp = realloc(*nume, n * sizeof(char));
            if (tmp != NULL) {
                *nume = tmp;
            } else {
                fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
                return;
            }
        }
        fscanf(in, "%c", &c);
        *(*nume + i * sizeof(char)) = c;
        i++;
    }
    if (n == i) {
        tmp = realloc(*nume, (n + 1) * sizeof(char));
        if (tmp != NULL) {
            *nume = tmp;
        } else {
            fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
            return;
        }
    }
    i--;
    *(*nume + i * sizeof(char)) = '\0';
}

int check_landing(int r, int x, int y) {
    if ((x - r) * (x - r) + (y - r) * (y - r) > r * r || x < 0 || y < 0 ||
            x >= r * 2 + 1 || y >= r * 2 + 1) {
        return 0;
    } else {
        return 1;
    }
}

int check_melting(int r, int x, int y) {
    if ((x - r) * (x - r) + (y - r) * (y - r) > (r - 1) * (r - 1)) {
        return 0;
    } else {
        return 1;
    }
}

int check_remaining(int ***matrix, FILE *out, elfs *v, int r, int *design) {
    char flag = 0;
    int first_id;
    for (int i = 0; i < r * 2 + 1; i++) {
        for (int j = 0; j < r * 2 + 1; j++) {
            if (matrix[i][j][2] != -1) {
                first_id = matrix[i][j][2];
                flag++;
            }
            if (flag > 1) {
                return 1;
            }
        }
    }
    if (flag == 1) {
        if (*design == 1) {
            fprintf(out, "\n");
        } else {
            *design = 1;
        }
        fprintf(out, "%s has won.", v[first_id].nume);
    }
    return 0;
}

void read_until_char(char *p, FILE *in, char c) {
    int n = INCR, i = 0;
    char read = '\0', *tmp;
    // fscanf(in, "%c", &read);
    p = malloc(n * sizeof(char));
    if (p == NULL) {
        fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
        return;
    }

    do {
        if (n == i) {
            n += INCR;
            tmp = realloc(p, n * sizeof(char));
            if (tmp != NULL) {
                p = tmp;
            } else {
                fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
                return;
            }
        }
        fscanf(in, "%c", &read);
        *(p + i * sizeof(char)) = read;
        i++;
    } while (read != c && feof(in) == 0);

    if (n == i) {
        tmp = realloc(p, (n + 1) * sizeof(char));
        if (tmp != NULL) {
            p = tmp;
        } else {
            fprintf(stderr, "Nu s-a reusit alocarea de memorie!\n");
            return;
        }
    }
    *(p + n * sizeof(char)) = '\0';
}

void free_matrix(int ****matrix, int r) {
    for (int i = 0; i < r * 2 + 1; i++) {
        for (int j = 0; j < r *2 + 1; j++) {
            free(*(*(*matrix + i) + j));
        }
        free(*(*matrix + i));
    }
    free(*matrix);
}

void free_elfs(elfs *v, int n) {
    for (int i = 0; i < n; i++) {
        free(v[i].nume);
    }
    free(v);
}
