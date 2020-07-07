// Copyright Robert LIca robertlica21@gmail.com
#include "./functii.h"

// boardul gol este 0
// X de la input = 1 pe board
// 0 de la input = 2 pe board
// vectorul "task3" are 4 elemente cu scopul:
// [0] - numarul de castiguri proprii ale jucatorului X
// [1] - numarul de jocuri al jucatorului X
// [2] - numarul de castiguri proprii ale jucatorului 0
// [3] - numarul de jocuri al jucatorului 0
int main() {
    int m = 0, n = 0, task3[4] = {0};
    scanf("%d %d", &n, &m);
    int n2 = n * n;
    char **board, **macroboard;
    board = malloc(n2 * sizeof(char*));
    macroboard = malloc(n * sizeof(char*));
    if (board == NULL || macroboard == NULL) {
        fprintf(stderr, "Boardul nu a putut fi initializata");
        return -1;
    }
    for (int i = 0; i < n2; i++) {
        board[i] = calloc(n2, sizeof(char));
        if (board[i] == NULL) {
            fprintf(stderr, "Boardul[%i] nu a putut fi initializata", i);
            return -1;
        }
    }
    for (int i = 0; i < n; i++) {
        macroboard[i] = calloc(n, sizeof(char));
        if (macroboard[i] == NULL) {
            fprintf(stderr, "Macroboardul[%d] nu a ptut fi initializat", i);
            return -1;
        }
    }

    completeaza_boardurile(board, macroboard, &n, &m, task3);
    verifica_castigator_joc(macroboard, n);
    printeaza_inteligenta(task3);

    for (int i = 0; i < n2; i++) {
        free(board[i]);
    }
    free(board);
    for (int i = 0; i < n; i++) {
        free(macroboard[i]);
    }
    free(macroboard);
    return 0;
}
