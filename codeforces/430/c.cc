#include <vector>
#include <iostream>

using namespace std;

struct node
{
    bool used;
    int state;
    int goal;
    vector<int> n;
};

vector<node> nodes;
vector<int> solution;

void dfs(int idx, int x, int xx) {
    node &a = nodes[idx];
    a.used = true;
    if (a.state ^ x != a.goal) {
        solution.push_back(idx + 1);
        x ^= 1;
    }
    for (auto j : a.n) {
        if (nodes[j].used) continue;
        dfs(j, xx, x);
    }
}

int main() {
    int n;
    cin >> n;
    nodes.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        nodes[a].n.push_back(b);
        nodes[b].n.push_back(a);
    }
    for (int i = 0; i < n; i++) cin >> nodes[i].state;
    for (int i = 0; i < n; i++) cin >> nodes[i].goal;
    dfs(0, 0, 0);
    cout << solution.size() << endl;
    for (auto i : solution) cout << i << endl;
}
