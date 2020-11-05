#include <bits/stdc++.h>

#define FILE_I "p3.in"
#define FILE_O "p3.out"
#define INF (1 << 30)
#define NMAX 100100
#define p pair< int, int>
#define SRC 1

using namespace std;

class Task {
  int n, m, e;
  vector<p> adj[NMAX];
  vector<int> parrent;
  vector<double> energy;
  vector<bool> visited;
  vector<int> route;

 public:
  void solve() {
    read();
    compute_result();
    print();
  }

 private:
  void read() {
    std::ifstream fin(FILE_I);
    fin >> n >> m >> e;
    parrent = vector<int>(n + 1, 0);
    energy = vector<double>(n + 1, 0);
    visited = vector<bool>(n + 1, false);

    int i, j, pr;
    for (int k = 0; k < m; ++k) {
      fin >> i >> j >> pr;
      adj[i].push_back({j, pr});
    }
    fin.close();
  }

  void compute_result() {
    energy[SRC] = e;
    parrent[SRC] = 0;
    priority_queue< pair< double, int>, vector<pair< double, int>>> q;
    q.push({energy[SRC], SRC});  // bagam nodul 1

    while (q.empty() == false) {
      int node = q.top().second;
      q.pop();

      if (visited[node] == true) continue;
      visited[node] = true;

      for (auto &elem : adj[node]) {
        int next_node = elem.first;
        double res = energy[node] * (1 - elem.second / 100.0);

        if (visited[next_node] == false && res > energy[next_node]) {
          energy[next_node] = res;
          parrent[next_node] = node;
          q.push({energy[next_node], next_node});
        }
      }
    }

    int cur = n;
    while (cur != SRC) {
      route.push_back(cur);
      cur = parrent[cur];
    }
    route.push_back(SRC);
  }


  void print() {
    std::ofstream fout(FILE_O);
    fout << setprecision(16) << energy[n] << "\n";
    for (auto x = route.end() - 1; x >= route.begin(); --x) {
      fout << *x << " ";
    }
    fout.close();
  }
};

int main() {
  Task *t = new Task();
  t->solve();
  delete t;
  return 0;
}
