#include <bits/stdc++.h>

#define FILE_I "p2.in"
#define FILE_O "p2.out"
#define INF (1 << 30)
#define p pair<int, int>
#define NMAX 200100

using namespace std;

class Task {
  int n, m, src, dst;
  std::vector<p> adj[NMAX];
  vector<int> distance;
  vector<int> t_out;

 public:
  void solve() {
    read();
    fa();
    print();
  }

 private:
  void read() {
    std::ifstream fin(FILE_I);
    fin >> n >> m;
    fin >> src >> dst;
    distance = vector<int>(n + 1, INF);
    t_out = vector<int>(n + 1, 0);

    int x, y, z;
    for (int i = 0; i < m; ++i) {
      fin >> x >> y >> z;
      adj[x].push_back({y, z});
    }

    fin.close();
  }

  void fa() {
    stack<int> s;
    get_out_time(s);

    distance[src] = 0;

    while (s.empty() == false) {
      int node = s.top();
      s.pop();

      if (distance[node] == INF) continue;

      for (auto &elem : adj[node]) {
        if (distance[node] + elem.second < distance[elem.first]) {
          // actualizam noul cost
          distance[elem.first] = distance[node] + elem.second;
        }
      }
    }
  }

  void get_out_time(stack<int> &s) {
    std::vector<int> vizitat(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
      if (vizitat[i] == 0) {
        dfs(i, vizitat, s);
      }
    }
  }

  void dfs(int nod, std::vector<int> &vizitat, stack<int> &s) {
    vizitat[nod] = 1;
    for (auto &x : adj[nod]) {
      if (vizitat[x.first] == 0) {
        dfs(x.first, vizitat, s);
      }
    }
    s.push(nod);
  }

  void print() {
    std::ofstream fout(FILE_O);
    fout << distance[dst];
    fout.close();
  }
};

int main() {
  Task *t = new Task();
  t->solve();
  delete t;
  return 0;
}
