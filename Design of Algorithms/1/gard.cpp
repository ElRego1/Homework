// Lica Robert Mihai <robertlica21@gmail.com>

#include <bits/stdc++.h>

#define FILE_I "gard.in"
#define FILE_O "gard.out"

class Task {
    std::vector <std::pair <int, int>> intervals;
    int solution = 0;

 public:
    void read() {
        std::ifstream fin(FILE_I);
        int n, x, y;
        fin >> n;
        for (int i = n; i > 0; --i) {
            fin >> x >> y;
            intervals.push_back(std::pair <int, int>(x, y));
        }
        fin.close();
    }

    void compute_solution() {
        // ordonam crescator dupa pozitia de start si daca e egala,
        // descrescator dupa cea de final
        std::sort(intervals.begin(), intervals.end(),
            [](const std::pair <int, int>& a, const std::pair <int, int>& b) {
                return (a.first != b.first) ? (a.first < b.first) :
                                            (a.second > b.second);
            });

        int last_y = 0;
        for (auto& x : intervals) {
            if (x.second <= last_y) {
                ++solution;
            } else {
                last_y = x.second;
            }
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
    Task *scandura_al_lui_gigel = new Task();
    scandura_al_lui_gigel->solve();
    delete scandura_al_lui_gigel;
    return 0;
}
