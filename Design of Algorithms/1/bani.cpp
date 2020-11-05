// Lica Robert Mihai <robertlica21@gmail.com>

#include <bits/stdc++.h>

// sa se inlocuiasca '0' cu '1' pentru a fi mai incet programul
#define LOOP_UNROLLED 1

#define FILE_I "bani.in"
#define FILE_O "bani.out"
#define MOD 1000000007

#define MAT_VECT_SIZE 25

#define MAT_INIT    1, 1, 1, 1, 1
#define MAT_TIP_1   0, 1, 1, 0, 0, \
                    1, 0, 0, 1, 0, \
                    1, 0, 1, 0, 0, \
                    0, 1, 0, 0, 1, \
                    1, 0, 0, 1, 0

#define MAT_TIP_2   0, 1, 1, 0, 0, \
                    1, 0, 0, 1, 0, \
                    1, 0, 1, 0, 0, \
                    0, 1, 1, 0, 1, \
                    1, 0, 0, 1, 0

std::vector <int> recursive_matrix_mul(std::vector <int> &base, int exponent);
std::vector <int> five_matrix_mul(std::vector <int> &a, std::vector <int> &b);

class Task {
    int type;
    int n;
    int solution = 0;

 public:
    void read() {
        std::ifstream fin(FILE_I);
        fin >> type >> n;
        fin.close();
    }

    void compute_solution() {
        std::vector <int> start_matrix = {MAT_INIT};;
        std::vector <int> recursion;

        if (type == 1) {
            recursion = {MAT_TIP_1};
        } else {
            recursion = {MAT_TIP_2};
        }

        std::vector <int> result(start_matrix.size(), 0);
        --n;

        if (n != 0) {
            recursion = recursive_matrix_mul(recursion, n);

            // facem inmultirea intre matricea initiala cu cea la puterea (n-1)
            for (unsigned int i = 0; i < start_matrix.size(); ++i) {
                for (unsigned int j = 0; j < start_matrix.size(); ++j) {
                    result[i] += (1LL * start_matrix[j] *
                                recursion[j * 5 + i]) % MOD;
                    result[i] %= MOD;
                }
            }
        } else {
            result = start_matrix;
        }

        for (unsigned int i = 0; i < result.size(); ++i) {
            solution += result[i];
            solution %= MOD;
        }
    }

    void solve() {
        read();
        compute_solution();
        print();
    }

    void print() {
        std::ofstream fout(FILE_O);
        fout << solution;
        fout.close();
    }
};

int main() {
    Task *gigel_trezorier = new Task();
    gigel_trezorier->solve();
    delete gigel_trezorier;
    return 0;
}

std::vector <int> recursive_matrix_mul(std::vector <int> &base, int exponent) {
    if (exponent == 1) {
        return base;
    }
    if (exponent & 1) {
        std::vector <int> temp = recursive_matrix_mul(base, (exponent >> 1));
        temp = five_matrix_mul(temp, temp);
        return five_matrix_mul(base, temp);
    } else {
        std::vector <int> temp = recursive_matrix_mul(base, (exponent >> 1));
        return five_matrix_mul(temp, temp);
    }
}

#if LOOP_UNROLLED == 0
// aceasta functie este mai scurta si face acelasi lucru precum cea cu acelasi
// nume, doar ca este mai inceata. Ofc ca putea fi si mai scurta, cu mai multe
// for-uri dar am ales-o pe aceasta ca si compromis pentru matrici de 5X5
[[gnu::always_inline]] inline
std::vector <int> five_matrix_mul(std::vector <int> &a, std::vector <int> &b) {
    std::vector <int> m(MAT_VECT_SIZE);

    for (int i = 4; i >= 0; --i) {
        m[i] = ((((
            (1LL * a[0] * b[i]) % MOD +
            (1LL * a[1] * b[5 + i]) % MOD) % MOD +
            (1LL * a[2] * b[10 + i]) % MOD) % MOD +
            (1LL * a[3] * b[15 + i]) % MOD) % MOD +
            (1LL * a[4] * b[20 + i]) % MOD) % MOD;
        m[5 + i] = ((((
            (1LL * a[5] * b[0 + i]) % MOD +
            (1LL * a[6] * b[5 + i]) % MOD) % MOD +
            (1LL * a[7] * b[10 + i]) % MOD) % MOD +
            (1LL * a[8] * b[15 + i]) % MOD) % MOD +
            (1LL * a[9] * b[20 + i]) % MOD) % MOD;
        m[10 + i] = ((((
            (1LL * a[10] * b[i]) % MOD +
            (1LL * a[11] * b[5 + i]) % MOD) % MOD +
            (1LL * a[12] * b[10 + i]) % MOD) % MOD +
            (1LL * a[13] * b[15 + i]) % MOD) % MOD +
            (1LL * a[14] * b[20 + i]) % MOD) % MOD;
        m[15 + i] = ((((
            (1LL * a[15] * b[i]) % MOD +
            (1LL * a[16] * b[5 + i]) % MOD) % MOD +
            (1LL * a[17] * b[10 + i]) % MOD) % MOD +
            (1LL * a[18] * b[15 + i]) % MOD) % MOD +
            (1LL * a[19] * b[20 + i]) % MOD) % MOD;
        m[20 + i] = ((((
            (1LL * a[20] * b[0 + i]) % MOD +
            (1LL * a[21] * b[5 + i]) % MOD) % MOD +
            (1LL * a[22] * b[10 + i]) % MOD) % MOD +
            (1LL * a[23] * b[15 + i]) % MOD) % MOD +
            (1LL * a[24] * b[20 + i]) % MOD) % MOD;
    }

    return m;
}

#else
[[gnu::always_inline]] inline
std::vector <int> five_matrix_mul(std::vector <int> &a, std::vector <int> &b) {
    std::vector <int> m(MAT_VECT_SIZE, 0);
    // am sa fac operatiile de calcul manual, consider ca este mai eficient asa
    // tot ce fac este o inmultire de 2 matrici patratice de marime 5
// ----------------------------------- coloana 1 ------------------------------
    m[0] = ((((
    (1LL * a[0] * b[0]) % MOD + (1LL * a[1] * b[5]) % MOD) % MOD +
    (1LL * a[2] * b[10]) % MOD) % MOD + (1LL * a[3] * b[15]) % MOD) % MOD +
    (1LL * a[4] * b[20]) % MOD) % MOD;
    m[5] = ((((
    (1LL * a[5] * b[0]) % MOD + (1LL * a[6] * b[5]) % MOD) % MOD +
    (1LL * a[7] * b[10]) % MOD) % MOD + (1LL * a[8] * b[15]) % MOD) % MOD +
    (1LL * a[9] * b[20]) % MOD) % MOD;
    m[10] = ((((
    (1LL * a[10] * b[0]) % MOD + (1LL * a[11] * b[5]) % MOD) % MOD +
    (1LL * a[12] * b[10]) % MOD) % MOD + (1LL * a[13] * b[15]) % MOD) % MOD +
    (1LL * a[14] * b[20]) % MOD) % MOD;
    m[15] = ((((
    (1LL * a[15] * b[0]) % MOD + (1LL * a[16] * b[5]) % MOD) % MOD +
    (1LL * a[17] * b[10]) % MOD) % MOD + (1LL * a[18] * b[15]) % MOD) % MOD +
    (1LL * a[19] * b[20]) % MOD) % MOD;
    m[20] = ((((
    (1LL * a[20] * b[0]) % MOD + (1LL * a[21] * b[5]) % MOD) % MOD +
    (1LL * a[22] * b[10]) % MOD) % MOD + (1LL * a[23] * b[15]) % MOD) % MOD +
    (1LL * a[24] * b[20]) % MOD) % MOD;

// ----------------------------------- coloana 2 ------------------------------
    m[1] = ((((
    (1LL * a[0] * b[1]) % MOD + (1LL * a[1] * b[6]) % MOD) % MOD +
    (1LL * a[2] * b[11]) % MOD) % MOD + (1LL * a[3] * b[16]) % MOD) % MOD +
    (1LL * a[4] * b[21]) % MOD) % MOD;
    m[6] = ((((
    (1LL * a[5] * b[1]) % MOD + (1LL * a[6] * b[6]) % MOD) % MOD +
    (1LL * a[7] * b[11]) % MOD) % MOD + (1LL * a[8] * b[16]) % MOD) % MOD +
    (1LL * a[9] * b[21]) % MOD) % MOD;
    m[11] = ((((
    (1LL * a[10] * b[1]) % MOD + (1LL * a[11] * b[6]) % MOD) % MOD +
    (1LL * a[12] * b[11]) % MOD) % MOD + (1LL * a[13] * b[16]) % MOD) % MOD +
    (1LL * a[14] * b[21]) % MOD) % MOD;
    m[16] = ((((
    (1LL * a[15] * b[1]) % MOD + (1LL * a[16] * b[6]) % MOD) % MOD +
    (1LL * a[17] * b[11]) % MOD) % MOD + (1LL * a[18] * b[16]) % MOD) % MOD +
    (1LL * a[19] * b[21]) % MOD) % MOD;
    m[21] = ((((
    (1LL * a[20] * b[1]) % MOD + (1LL * a[21] * b[6]) % MOD) % MOD +
    (1LL * a[22] * b[11]) % MOD) % MOD + (1LL * a[23] * b[16]) % MOD) % MOD +
    (1LL * a[24] * b[21]) % MOD) % MOD;

// ----------------------------------- coloana 3 ------------------------------
    m[2] = ((((
    (1LL * a[0] * b[2]) % MOD + (1LL * a[1] * b[7]) % MOD) % MOD +
    (1LL * a[2] * b[12]) % MOD) % MOD + (1LL * a[3] * b[17]) % MOD) % MOD +
    (1LL * a[4] * b[22]) % MOD) % MOD;
    m[7] = ((((
    (1LL * a[5] * b[2]) % MOD + (1LL * a[6] * b[7]) % MOD) % MOD +
    (1LL * a[7] * b[12]) % MOD) % MOD + (1LL * a[8] * b[17]) % MOD) % MOD +
    (1LL * a[9] * b[22]) % MOD) % MOD;
    m[12] = ((((
    (1LL * a[10] * b[2]) % MOD + (1LL * a[11] * b[7]) % MOD) % MOD +
    (1LL * a[12] * b[12]) % MOD) % MOD + (1LL * a[13] * b[17]) % MOD) % MOD +
    (1LL * a[14] * b[22]) % MOD) % MOD;
    m[17] = ((((
    (1LL * a[15] * b[2]) % MOD + (1LL * a[16] * b[7]) % MOD) % MOD +
    (1LL * a[17] * b[12]) % MOD) % MOD + (1LL * a[18] * b[17]) % MOD) % MOD +
    (1LL * a[19] * b[22]) % MOD) % MOD;
    m[22] = ((((
    (1LL * a[20] * b[2]) % MOD + (1LL * a[21] * b[7]) % MOD) % MOD +
    (1LL * a[22] * b[12]) % MOD) % MOD + (1LL * a[23] * b[17]) % MOD) % MOD +
    (1LL * a[24] * b[22]) % MOD) % MOD;

// ----------------------------------- coloana 4 ------------------------------
    m[3] = ((((
    (1LL * a[0] * b[3]) % MOD + (1LL * a[1] * b[8]) % MOD) % MOD +
    (1LL * a[2] * b[13]) % MOD) % MOD + (1LL * a[3] * b[18]) % MOD) % MOD +
    (1LL * a[4] * b[23]) % MOD) % MOD;
    m[8] = ((((
    (1LL * a[5] * b[3]) % MOD + (1LL * a[6] * b[8]) % MOD) % MOD +
    (1LL * a[7] * b[13]) % MOD) % MOD + (1LL * a[8] * b[18]) % MOD) % MOD +
    (1LL * a[9] * b[23]) % MOD) % MOD;
    m[13] = ((((
    (1LL * a[10] * b[3]) % MOD + (1LL * a[11] * b[8]) % MOD) % MOD +
    (1LL * a[12] * b[13]) % MOD) % MOD + (1LL * a[13] * b[18]) % MOD) % MOD +
    (1LL * a[14] * b[23]) % MOD) % MOD;
    m[18] = ((((
    (1LL * a[15] * b[3]) % MOD + (1LL * a[16] * b[8]) % MOD) % MOD +
    (1LL * a[17] * b[13]) % MOD) % MOD + (1LL * a[18] * b[18]) % MOD) % MOD +
    (1LL * a[19] * b[23]) % MOD) % MOD;
    m[23] = ((((
    (1LL * a[20] * b[3]) % MOD + (1LL * a[21] * b[8]) % MOD) % MOD +
    (1LL * a[22] * b[13]) % MOD) % MOD + (1LL * a[23] * b[18]) % MOD) % MOD +
    (1LL * a[24] * b[23]) % MOD) % MOD;

// ----------------------------------- coloana 5 ------------------------------
    m[4] = ((((
    (1LL * a[0] * b[4]) % MOD + (1LL * a[1] * b[9]) % MOD) % MOD +
    (1LL * a[2] * b[14]) % MOD) % MOD + (1LL * a[3] * b[19]) % MOD) % MOD +
    (1LL * a[4] * b[24]) % MOD) % MOD;
    m[9] = ((((
    (1LL * a[5] * b[4]) % MOD + (1LL * a[6] * b[9]) % MOD) % MOD +
    (1LL * a[7] * b[14]) % MOD) % MOD + (1LL * a[8] * b[19]) % MOD) % MOD +
    (1LL * a[9] * b[24]) % MOD) % MOD;
    m[14] = ((((
    (1LL * a[10] * b[4]) % MOD + (1LL * a[11] * b[9]) % MOD) % MOD +
    (1LL * a[12] * b[14]) % MOD) % MOD + (1LL * a[13] * b[19]) % MOD) % MOD +
    (1LL * a[14] * b[24]) % MOD) % MOD;
    m[19] = ((((
    (1LL * a[15] * b[4]) % MOD + (1LL * a[16] * b[9]) % MOD) % MOD +
    (1LL * a[17] * b[14]) % MOD) % MOD + (1LL * a[18] * b[19]) % MOD) % MOD +
    (1LL * a[19] * b[24]) % MOD) % MOD;
    m[24] = ((((
    (1LL * a[20] * b[4]) % MOD + (1LL * a[21] * b[9]) % MOD) % MOD +
    (1LL * a[22] * b[14]) % MOD) % MOD + (1LL * a[23] * b[19]) % MOD) % MOD +
    (1LL * a[24] * b[24]) % MOD) % MOD;

    return m;
}
#endif
