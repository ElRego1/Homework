// Copyright 2018 Blah Blah <ceva@ceva.com>
#include <stdio.h>

void stepOne(int x0, int v0, int x1, int v1, int x2, int v2, int x3,
             int v3, int x4, int v4, int x5, int v5, int x6, int v6, int x7,
             int v7, int x8, int v8, int x9, int v9);
void stepTwo(int x0, int v0, int x1, int v1, int x2, int v2, int x3,
             int v3, int x4, int v4, int x5, int v5, int x6, int v6, int x7,
             int v7, int x8, int v8, int x9, int v9);
int creazaStea(int x, int v, int e);
void printConditionat(int i, int x, int v, int f);

int main() {
    int x0 = 10, x1 = 10, x2 = 10, x3 = 10, x4 = 10, x5 = 10, x6 = 10, x7 = 10,
        x8 = 10, x9 = 10, v0 = -1, v1 = -1, v2 = -1, v3 = -1, v4 = -1, v5 = -1,
        v6 = -1, v7 = -1, v8 = -1, v9 = -1, n, t;
    scanf("%d%d%d%d", &n, &x0, &v0, &t);
    v0 = creazaStea(x0, v0, t);
    scanf("%d%d%d", &x1, &v1, &t);
    v1 = creazaStea(x1, v1, t);
    scanf("%d%d%d", &x2, &v2, &t);
    v2 = creazaStea(x2, v2, t);
    scanf("%d%d%d", &x3, &v3, &t);
    v3 = creazaStea(x3, v3, t);
    scanf("%d%d%d", &x4, &v4, &t);
    v4 = creazaStea(x4, v4, t);
    scanf("%d%d%d", &x5, &v5, &t);
    v5 = creazaStea(x5, v5, t);
    scanf("%d%d%d", &x6, &v6, &t);
    v6 = creazaStea(x6, v6, t);
    scanf("%d%d%d", &x7, &v7, &t);
    v7 = creazaStea(x7, v7, t);
    scanf("%d%d%d", &x8, &v8, &t);
    v8 = creazaStea(x8, v8, t);
    scanf("%d%d%d", &x9, &v9, &t);
    v9 = creazaStea(x9, v9, t);
    stepOne(x0, v0, x1, v1, x2, v2, x3, v3, x4, v4, x5, v5, x6, v6, x7,
            v7, x8, v8, x9, v9);
    return 0;
    }

int creazaStea(int x, int v, int e) {
    if (x == 10) {
        return -1;
    } else if (v >= e) {
        return 10;
    }
    double a = (10.0 * v) / e;
    int b = a;
    a = a - b;
    if (a < 0.5)
        return b;
    else
        return b+1;
}

void stepOne(int x0, int v0, int x1, int v1, int x2, int v2, int x3,
             int v3, int x4, int v4, int x5, int v5, int x6, int v6, int x7,
             int v7, int x8, int v8, int x9, int v9) {
    for (int i = 0; i < 10; i++) {
        if (x0 > x1) {
            x1 = x1 + x0;
            x0 = x1 - x0;
            x1 = x1 - x0;
            v1 = v1 + v0;
            v0 = v1 - v0;
            v1 = v1 - v0;
            i = -1;
        } else if (x1 > x2) {
            x2 = x2 + x1;
            x1 = x2 - x1;
            x2 = x2 - x1;
            v2 = v2 + v1;
            v1 = v2 - v1;
            v2 = v2 - v1;
            i = -1;
        } else if (x2 > x3) {
            x3 = x3 + x2;
            x2 = x3 - x2;
            x3 = x3 - x2;
            v3 = v3 + v2;
            v2 = v3 - v2;
            v3 = v3 - v2;
            i = -1;
        } else if (x3 > x4) {
            x4 = x4 + x3;
            x3 = x4 - x3;
            x4 = x4 - x3;
            v4 = v4 + v3;
            v3 = v4 - v3;
            v4 = v4 - v3;
            i = -1;
        } else if (x4 > x5) {
            x5 = x5 + x4;
            x4 = x5 - x4;
            x5 = x5 - x4;
            v5 = v5 + v4;
            v4 = v5 - v4;
            v5 = v5 - v4;
            i = -1;
        } else if (x5 > x6) {
            x6 = x6 + x5;
            x5 = x6 - x5;
            x6 = x6 - x5;
            v6 = v6 + v5;
            v5 = v6 - v5;
            v6 = v6 - v5;
            i = -1;
        } else if (x6 > x7) {
            x7 = x7 + x6;
            x6 = x7 - x6;
            x7 = x7 - x6;
            v7 = v7 + v6;
            v6 = v7 - v6;
            v7 = v7 - v6;
            i = -1;
        } else if (x7 > x8) {
            x8 = x8 + x7;
            x7 = x8 - x7;
            x8 = x8 - x7;
            v8 = v8 + v7;
            v7 = v8 - v7;
            v8 = v8 - v7;
            i = -1;
        } else if (x8 > x9) {
            x9 = x9 + x8;
            x8 = x9 - x8;
            x9 = x9 - x8;
            v9 = v9 + v8;
            v8 = v9 - v8;
            v9 = v9 - v8;
            i = -1;
        }
    }
    stepTwo(x0, v0, x1, v1, x2, v2, x3, v3, x4, v4, x5, v5, x6, v6, x7,
            v7, x8, v8, x9, v9);
}

void stepTwo(int x0, int v0, int x1, int v1, int x2, int v2, int x3,
             int v3, int x4, int v4, int x5, int v5, int x6, int v6, int x7,
             int v7, int x8, int v8, int x9, int v9) {
    for (int i = 0; i <= 10; i++) {
        printConditionat(i, x0, v0, x1);
        printConditionat(i, x1, v1, x2);
        printConditionat(i, x2, v2, x3);
        printConditionat(i, x3, v3, x4);
        printConditionat(i, x4, v4, x5);
        printConditionat(i, x5, v5, x6);
        printConditionat(i, x6, v6, x7);
        printConditionat(i, x7, v7, x8);
        printConditionat(i, x8, v8, x9);
        printConditionat(i, x9, v9, 10);
        printf("\n");
    }
}

void printConditionat(int i, int x, int v, int f) {
    if (x == 10)
        return;
    if (i == 10) {
        printf("%d", x);
        if (f != 10) {
            printf(" ");
        }
        return;
    } else {
        if ((10 - i) > v) {
            printf(".");
            if (f != 10) {
                printf(" ");
            }
        } else {
            printf("*");
            if (f != 10) {
                printf(" ");
            }
        }
    }
}

/*
scanf("%d%d%d", &x1, &v1, &t);
v1 = creazaStea(x1, v1, t);
==================================================>>>>>>>>>>>>>>>>>>>>
for (int i = 1; i < 10; i++) {
        printf("scanf(\"%%d%%d%%d\", &x%d, &v%d, &t);\n", i, i);
        printf("v%d = creazaStea(x%d, v%d, t);\n", i, i, i);
    }
*/
/*
        if (e0 > 0 && x0 != 10) {
            printf(".");
            if (x1 != 10) {
                printf(" ");
            }
            e0--;
        } else if (v0 > 0 && x0 != 10) {
            printf("*");
            if (x1 != 10) {
                printf(" ");
            }
            v0--;
        } else if (x0 != 10 && i == 9) {
            printf("%d", x0);
            if (x1 != 10) {
                printf(" ");
            }
        }
=====================================================>>>>>>>>>>>>>
for(int i = 0; i<9; i++) {
        printf("if (e%d > 0 && x%d != 10) {\n", i, i);
        printf("    printf(\".\");\n");
        printf("    if (x%d != 10) {\n", i+1);
        printf("        printf(\" \");\n    }\n");
        printf("    e%d--;\n", i);

        printf("} else if (v%d > 0 && x%d != 10) {\n", i, i);
        printf("    printf(\"*\");\n");
        printf("    if (x%d != 10) {\n", i+1);
        printf("        printf(\" \");\n    }\n");
        printf("    v%d--;\n", i);

        printf("} else if (x%d != 10 && i == 9) {\n", i);
        printf("    printf(\"%%d\", x%d);\n");
        printf("    if (x%d != 10) {\n", i+1);
        printf("        printf(\" \");\n    }\n}\n");
    }
*/

/*
if (x0 > x1) {
            x1 = x1 + x0;
            x0 = x1 - x0;
            x1 = x1 - x0;

            e1 = e1 + e0;
            e0 = e1 - e0;
            e1 = e1 - e0;

            v1 = v1 + v0;
            v0 = v1 - v0;
            v1 = v1 - v0;
            i = -1;
            continue;
        }
=======================================================>>>>>>>>>
    for (int i=0; i<9; i++) {
        printf("    if (x%d > x%d) {\n", i, i+1);
        printf("        x%d = x%d + x%d;\n", i+1, i+1, i);
        printf("        x%d = x%d - x%d;\n", i, i+1, i);
        printf("        x%d = x%d - x%d;\n\n", i+1, i+1, i);

        printf("        e%d = e%d + e%d;\n", i+1, i+1, i);
        printf("        e%d = e%d - e%d;\n", i, i+1, i);
        printf("        e%d = e%d - e%d;\n\n", i+1, i+1, i);

        printf("        v%d = v%d + v%d;\n", i+1, i+1, i);
        printf("        v%d = v%d - v%d;\n", i, i+1, i);
        printf("        v%d = v%d - v%d;\n", i+1, i+1, i);

        printf("        i = -1;\n");
        printf("        continue;\n");
        printf("    }\n");
    }
*/

/*if (x0 != 10) {
        v0 = creazaStea(v0,e0);
        e0 = 10;
    }
============================================================>>>>
    for(int i = 0; i<10; i++) {
        printf("    if (x%d != 10) {\n", i);
        printf("        v%d = creazaStea(v%d, e%d);\n", i, i, i);
        printf("        e%d = 10;\n    }\n", i);
    }
*/
