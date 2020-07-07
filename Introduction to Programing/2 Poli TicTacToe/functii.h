// Copyright Robert LIca robertlica21@gmail.com
#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

void completeaza_boardurile(char **board, char **macroboard, int *n, int *m,
            int task3[4]);
int cauta_diagonala(char **board, int *n, char *t);
int verifica_castigator_micro(char **board, char **macroboard, int *n,
            int x, int y);
void verifica_castigator_joc(char **macroboard, int n);
void printeaza_macroboard(char **macroboard, int n);
int check_win(char ** macroboard, int n, int val);
int error(char **boaard, char **macroboard, int n, char t, char temp_t,
            int x, int y, int task3[4]);
int check_and_put_macroboard(char **macroboard, int *n, int flag,
            int x, int y);
void printeaza_inteligenta(int task3[4]);
int check_if_full_after_good_insertion(char **board, int n);
#endif
