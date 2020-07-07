// Copyright Robert Lica robertlica21@gmail.com
#ifndef SPIRIDUSI_H
#define SPIRIDUSI_H

#include "./functii.h"

typedef struct spiridusi {
    char *nume;
    int id;
    int x;
    int y;
    int hp;
    int stamina;
    int manusi;
    int kills;
}elfs;

void read_elfs(int ***matrix, elfs *v, FILE *in, FILE *out,
               int r, int n, int *design);
void read_name(char **nume, FILE *in);
int check_landing(int r, int x, int y);
void read_until_char(char *p, FILE *in, char c);
void free_matrix(int ****matrix, int r);
void free_elfs(elfs *v, int n);

// Acum pun functiile de comenzi deoarece nu am reusit sa le pun in alt header
// file pt ca nu imi vedea strucura
void do_commands(int ****matrix, FILE *in, FILE *out, elfs *v,
                 int r, int n, int design);
int check_remaining(int ***matrix, FILE *out, elfs *v, int r, int *design);

void do_move(int ***matrix, FILE *in, FILE *out, elfs *v, int r,
             int n, int *design);
void get_moves(char **p, FILE *in);
void make_move(int ***matrix, char *p, elfs *v, FILE *out, elfs *e,
               int r, int *design);
// check landing here
int check_stamina(int ***matrix, elfs *e, int r, int x_nou, int y_nou);
int fight(elfs *e1, elfs *e2, FILE *out, int *design);

void do_snowstorm(int ***matrix, FILE *in, FILE *out, elfs *v, int r,
                  int n, int *design);
void read_K(FILE *in, unsigned char decoded[4]);
int check_hit(unsigned char decoded[4], int x, int y);
void give_damage(int ***matrix, FILE *out, elfs *v, unsigned char decoded[4]);

void do_meltdown(int ****matrix, FILE *in, FILE *out, elfs *v, int *r,
                 int n, int *design);
int check_melting(int r, int x, int y);
int ***do_shrink_iceberg(int ****matrix, elfs *v, int *r);

void do_scoreboard(FILE *out, elfs *v, int n, int *design);
void make_order(int *ordered, elfs *v, int n);
void print_dry_wet(FILE *out, int *order, elfs *v, int n, int *design);
#endif
