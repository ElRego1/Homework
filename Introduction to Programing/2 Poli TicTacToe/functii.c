// Copyright Robert LIca robertlica21@gmail.com
#include "./functii.h"

// 1 pe tabla este x pus
// 2 pe tabla este 0 pus
// Conventii:
// -valorile impare nenule sunt pentru jucatorul X
// -valorile pare nenule sunt pentru jucatorul 0
// -"i" va fi folosit singur numai in prima paranteza patrata la matrici
//      (numai pentru linie)
// -"j" va fi folosit singur numai in a doua paranteza patrata la matrici
//      (numai pentru coloane)
void completeaza_boardurile(char **board, char **macroboard, int *n, int *m,
                            int task3[4]) {
    char t, temp_t = '.';
    int x, y, error_flag = 0;
    for (int i = 0; i < *m; i++) {
        scanf(" %c %d %d", &t, &x, &y);
        error_flag = error(board, macroboard, *n, t, temp_t, x, y, task3);
        if (error_flag == 1) {
            temp_t = t;
            continue;
        } else if (error_flag == 2) {
            break;
        }
        if (board[x][y] == 0) {
            if ((t == 'X') > 0) {
                board[x][y] = 1;
            } else {
                board[x][y] = 2;
            }
            if (verifica_castigator_micro(board, macroboard, n, x, y) == 1) {
                if (t == 'X') {
                    task3[0]++;
                } else {
                    task3[2]++;
                }
            }
            if (check_if_full_after_good_insertion(board, *n)) {
                printf("FULL BOARD\n");
                break;
            }
            temp_t = t;
        } else {
            temp_t = t;
            printf("NOT AN EMPTY CELL\n");
            int temp = cauta_diagonala(board, n, &t);
            if (!verifica_castigator_micro(board, macroboard, n, temp, t)) {
                break;
            }
        }
    }
}

int verifica_castigator_micro(char **board, char **macroboard, int *n,
                        int x, int y) {
    if (x < 0 || y < 0) {
        return 0; // Boardul este full
    } else if (macroboard[x / *n][y / *n]) {
        return 2; // Deja exista un castigator
    }
    int x_colt = x / (*n) * (*n);
    int y_colt = y / (*n) * (*n);
    int flag = 0;
// Verific diagonalele microboardului:
// Diagonala principala
    if ((int)board[x_colt][y_colt] != 0) {
        flag = (int)board[x_colt][y_colt];
        for (int i = 1; i < *n; i++) {
            if ((int)board[x_colt + i][y_colt + i] != flag) {
                flag = 0;
                break;
            }
        }
    }
    if (check_and_put_macroboard(macroboard, n, flag, x, y)) {
        return 1;
    }
// Diagonala secundara
    flag = 0;
    if (board[x_colt][y_colt + *n - 1] != 0) {
        flag = (int)board[x_colt][y_colt + *n - 1];
        for (int i = 1; i < *n; i++) {
            if ((int)board[x_colt + i][y_colt + *n - 1 - i] != flag) {
                flag = 0;
                break;
            }
        }
    }
    if (check_and_put_macroboard(macroboard, n, flag, x, y)) {
        return 1;
    }
// Cautam pe linii
    flag = 0;
    for (int i = 0; i < *n; i++) {
        if ((int)board[x_colt + i][y_colt] != 0) {
            flag = (int)board[x_colt + i][y_colt];
        } else {
            continue;
        }
        for (int j = 1; j < *n; j++) {
            if ((int)board[x_colt + i][y_colt + j] != flag) {
                flag = 0;
                break;
            }
        }
        if (check_and_put_macroboard(macroboard, n, flag, x, y)) {
            return 1;
        }
    }
// Cautam pe coloane
    flag = 0;
    for (int j = 0; j < *n; j++) {
        if ((int)board[x_colt][y_colt + j] != 0) {
            flag = (int)board[x_colt][y_colt + j];
        } else {
            continue;
        }
        for (int i = 1; i < *n; i++) {
            if ((int)board[x_colt + i][y_colt + j] != flag) {
                flag = 0;
                break;
            }
        }
        if (check_and_put_macroboard(macroboard, n, flag, x, y)) {
            return 1;
        }
    }
// Nu s-a castigat nimica
    return 2;
}

int check_and_put_macroboard(char **macroboard, int *n, int flag,
                             int x, int y) {
    if (flag % 2 == 1) {
        macroboard[x / *n][y / *n] = 1;
        return 1;
    } else if (flag % 2 == 0 && flag != 0) {
        macroboard[x / *n][y / *n] = 2;
        return 1;
    }
    return 0;
}

int cauta_diagonala(char **board, int *n, char *t) {
// Il voi folosi pe t ca sa mi pastrez al 2-lea parametru pentru pozitie
    int n2 = (*n) * (*n);
    for (int i = 0; i < n2; i++) {
        if (!board[i][i]) {
            if (((int)*t - '9') > 0) {
                board[i][i] = 1;
            } else {
                board[i][i] = 2;
            }
            *t = i;
            return i;
        }
    }
// ->Nu e pe diagonala principala
    int c = 1;
    for (int i = 1; i < n2 ; i++) {
        for (int k = 0; k + c < n2; k++) {
            if (!board[k][k + c]) {
                if (((int)*t - '9') > 0) {
                    board[k][k + c] = 1;
                } else {
                    board[k][k + c] = 2;
                }
                *t = k + c;
                return k;
            }
        }
        for (int k = 0; k + c < n2; k++) {
            if (!board[k + c][k]) {
                if (((int)*t - '9') > 0) {
                    board[k + c][k] = 1;
                } else {
                    board[k + c][k] = 2;
                }
                *t = k;
                return k + c;
            }
        }
        c++;
    }

    printf("FULL BOARD\n");
    *t = 0;
    return -11;
}

int error(char **board, char **macroboard, int n, char t, char temp_t,
          int x, int y, int task3[4]) {
    if (t == temp_t) {
        printf("NOT YOUR TURN\n");
        return 1;
    }  else if (temp_t == '.' && t != 'X') {
        printf("NOT YOUR TURN\n");
        return 1;
    } else if (x < 0 || y < 0 || x >= n*n || y >= n*n) {
        printf("INVALID INDEX\n");
        if (t == 'X') {
            task3[1]++;
        } else {
            task3[3]++;
        }
        int temp = cauta_diagonala(board, &n, &t);
        if (!verifica_castigator_micro(board, macroboard, &n, temp, t)) {
                return 2;
        }
        return 1;
    }
    if (t == 'X') {
        task3[1]++;
    } else {
        task3[3]++;
    }
    return 0;
}

void verifica_castigator_joc(char **macroboard, int n) {
    int x_player = check_win(macroboard, n, 1);
    int o_player = check_win(macroboard, n, 2);
    printeaza_macroboard(macroboard, n);
    if (x_player == o_player) {
        printf("Draw again! Let's play darts!\n");
    } else if (x_player) {
        printf("X won\n");
    } else {
        printf("0 won\n");
    }
}

int check_win(char **macroboard, int n, int val) {
    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (val != macroboard[i][i]) {
            flag = 0;
            break;
        }
    }
    if (flag) {
        return 1;
    }
    flag = 1;
    for (int i = 0; i < n; i++) {
        if (val != macroboard[i][n -1 - i]) {
            flag = 0;
            break;
        }
    }
    if (flag) {
        return 1;
    }
    flag = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (val != macroboard[i][j]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            return 1;
        }
        flag = 1;
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (val != macroboard[i][j]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            return 1;
        }
        flag = 1;
    }
    return 0;
}

void printeaza_macroboard(char **macroboard, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (macroboard[i][j] == 1) {
                printf("X");
            } else if (macroboard[i][j] == 2) {
                printf("0");
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
}

void printeaza_inteligenta(int task3[4]) {
    double d;
    printf("X ");
    if (!task3[1]) {
        printf("N/A\n");
    } else {
        d = ((double)task3[0]) / task3[1];
        printf("%.10lf\n", d);
    }
    printf("0 ");
    if (!task3[3]) {
        printf("N/A\n");
    } else {
        d = 1.0 * task3[2] / task3[3];
        printf("%.10lf\n", d);
    }
}

int check_if_full_after_good_insertion(char **board, int n) {
    for (int i = 0; i < n * n; i++) {
        for (int j = 0; j < n * n; j++) {
            if (!board[i][j]) {
                return 0;
            }
        }
    }
    return 2;
}
