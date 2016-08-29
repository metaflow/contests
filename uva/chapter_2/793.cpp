#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef vector<int> vi;

vi parent, height;

int get_parent(int a) {
    while (parent[a] != a) a = parent[a];
    parent[a] = a;
    return a;
}

void connect(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a == b) return;    
    if (height[a] < height[b]) swap(a, b);
    if (height[a] == height[b]) height[a]++;
    parent[b] = a;
}

bool is_connected(int a, int b) {
    return (get_parent(a) == get_parent(b));
}

int main() {
    int tcn;
    scanf("%d", &tcn);
    while (tcn--) {
        int n;
        scanf("%d\n", &n);
        char s[80];        
        int success = 0;
        int failed = 0;
        parent.resize(n);
        height.resize(n);
        fill(height.begin(), height.end(), 0);
        for (int i = 0; i < n; i++) parent[i] = i;
        while (fgets(s, 80, stdin) != NULL) {
            char op;
            int a, b;
            if (sscanf(s, "%c %d %d", &op, &a, &b) != 3) break;
            a--; b--;
            if (op == 'c') {
                connect(a, b);
            } else {
                if (is_connected(a, b)) {
                    success++;
                 } else {
                    failed++;
                 }
            }
        }
        printf("%d,%d\n", success, failed);
        if (tcn) printf("\n");
    }
}
