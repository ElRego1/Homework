// Lica Robert Mihai <robertlica21@gmail.com>

#include <bits/stdc++.h>

#define FILE_I "sala.in"
#define FILE_O "sala.out"

class Task {
    unsigned int n, m;
    std::vector <std::pair <int, int>> input;
    unsigned long long solution = 0;

 public:
    void read() {
        std::ifstream fin(FILE_I);
        fin >> n >> m;
        int left, right;
        for (unsigned int i = 0; i < n; ++i) {
            fin >> left >> right;
            input.push_back(std::pair <int, int>(left, right));
        }
        fin.close();
    }

    void compute_solution() {
        auto cmp = [](const std::pair <int, int>& a,
            const std::pair <int, int>& b) {
                return a.second > b.second;
            };

        // sortam inputul descrescator dupa greutate
        std::sort(input.begin(), input.end(),
            [](const std::pair <int, int>& a, const std::pair <int, int>& b) {
                return a.first > b.first;
            });

        unsigned int index = 0;
        unsigned long long rep_inserate = 0;
        for (index = 0; index < m; ++index) {
            rep_inserate += input[index].second;
            unsigned long long temp = rep_inserate * input[index].first;
            if (temp > solution) {
                solution = temp;
            }
        }

        std::priority_queue <std::pair <int, int>,
            std::vector <std::pair <int, int>>,
            decltype(cmp)> rep_min_heap(input.begin(), input.begin() + m, cmp);

        for (index = m; index < n; ++index) {
            // ne mai pasa sa schimbam in heap daca numarul de repetitii creste
            if (input[index].second > rep_min_heap.top().second) {
                rep_inserate -= rep_min_heap.top().second;
                rep_min_heap.pop();

                // inseram urmatoarea gantera din input cu o greutate mai mica
                rep_min_heap.push(input[index]);
                rep_inserate += input[index].second;

                // verificam daca avem o solutie mai buna si o salvam daca da
                unsigned long long temp = rep_inserate * input[index].first;
                if (temp > solution) {
                    solution = temp;
                }
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
    Task *gigel_mr_univers = new Task();
    gigel_mr_univers->solve();
    delete gigel_mr_univers;
    return 0;
}
