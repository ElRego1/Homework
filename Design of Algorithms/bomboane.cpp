#include <bits/stdc++.h>

#define FILE_I "bomboane.in"
#define FILE_O "bomboane.out"
#define MOD 1000000007

#define N_MAX 2000
#define M_MAX 2000

class Task {
    std::vector <std::pair <int, int>> intervals;
    int n, m;
    int solution = -1;

 public:
    void read() {
        std::ifstream fin(FILE_I);
        int left_bound = 0, right_bound = 0;

        fin >> n >> m;
        int temp_left, temp_right;

        for (int i = 0; i < n; ++i) {
            fin >> temp_left >> temp_right;
            intervals.push_back(std::pair <int, int>(temp_left, temp_right));
            left_bound += temp_left;
            right_bound += temp_right;
        }
        fin.close();

        // raspundem imediat dupa citire daca raspunsul va fi 0
        if (m < left_bound || m > right_bound) {
            solution = 0;
        }
    }

    void compute_solution() {
        if (solution == 0) {
            return;
        }

        std::vector <std::vector <int>> dp(n, std::vector <int> (m + 1, 0));

        // cazul de baza
        for (int i = intervals[0].first; i <= intervals[0].second &&
                i <= m; ++i) {
            dp[0][i] = 1;
        }

        // cazul general
        int start_pos = intervals[0].first;  // optimizare sa de la pos != 0
        for (int i = 1; i < n; ++i) {
            for (int k = intervals[i].first; k <= intervals[i].second; ++k) {
                // ca sa terminam mai repede uitatul pe o linie, cand gasim din
                // nou 0, nu va mai urma nimic deoarece sunt intervale
                // continue, deci putem sa nu ne mai uitam pe restul liniei
                for (int j = start_pos; j + k <= m; ++j) {
                    if (dp[i - 1][j] != 0) {
                        dp[i][j + k] = (dp[i][j + k] + dp[i - 1][j]) % MOD;
                    } else {
                        break;
                    }
                }
            }
            start_pos += intervals[i].first;
        }

        // solutia se afla in ultima casuta a matricii
        solution = dp[n - 1][m];
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
    Task *bombonica_de_gigel = new Task();
    bombonica_de_gigel->solve();
    delete bombonica_de_gigel;
    return 0;
}
