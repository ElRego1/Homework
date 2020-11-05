#include <bits/stdc++.h>

#define FILE_I "p1.in"
#define FILE_O "p1.out"
#define INF (1 << 30)
#define NMAX 100100
// the city where Robin Hood is
#define SRC 1
// the city status where Robin Hood is
#define RB_HD_BASE 0
// a city that has no modifier
#define FREE 1
// a city that is blocked by Robin Hood's pals
#define BLOCKED 2
// a city from where enemies start to search for Robin Hood
#define ENEMY_CAMP 3

using namespace std;

class Task {
  int n, m, k;
  vector<int> adj[NMAX];
  vector<int> status;
  vector<int> closing_cities;
  int solution = 0;

 public:
  void solve() {
    read();
    compute_solution();
    print();
  }

 private:
  void read() {
    std::ifstream fin(FILE_I);
    fin >> n >> m >> k;
    status = vector<int>(n + 1, FREE);
    status[SRC] = RB_HD_BASE;

    int temp, temp2;
    for (int i = 0; i < k; ++i) {
      fin >> temp;
      status[temp] = ENEMY_CAMP;
    }

    for (int i = 0; i < n - 1; ++i) {
      fin >> temp;
      closing_cities.push_back(temp);
    }

    for (int i = 0; i < m; ++i) {
      fin >> temp >> temp2;
      adj[temp].push_back(temp2);
      adj[temp2].push_back(temp);
    }

    fin.close();
  }

  void compute_solution() {
    vector<bool> visited(n + 1, false);
    visited[SRC] = true;
    if (is_connected(visited) == false) {
      return;
    }

    for (auto it = closing_cities.begin(); it < closing_cities.end(); ++it) {
      status[*it] = BLOCKED;
      ++solution;
      if (visited[*it] == false) {
        continue;
      }

      visited = vector<bool>(n + 1, false);
      visited[SRC] = true;

      if (is_connected(visited) == false) {
        return;
      }
    }
  }


bool is_connected(vector<bool> &visited) {
  queue<int> q;
  q.push(SRC);
  visited[SRC] = true;

  while (q.empty() == false) {
    int node = q.front();
    q.pop();

    for (auto &neighbour : adj[node]) {
      if (visited[neighbour] == false) {
        if (status[neighbour] == FREE) {
          visited[neighbour] = true;
          q.push(neighbour);
        } else if (status[neighbour] == ENEMY_CAMP) {
          // the enemies reach Robin Hood so we block another city
          visited[neighbour] = true;
          return true;
        }
      }
    }
  }
  // we found the minimum solution
  return false;
}

  void print() {
    std::ofstream fout(FILE_O);
    fout << solution;
    fout.close();
  }
};

int main() {
  Task *t = new Task();
  t->solve();
  delete t;
  return 0;
}
