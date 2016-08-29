#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

const int MAX = 1000002;

typedef vector<int> vi;

int main() {    
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        vi** indexes = new vi*[MAX];
        for (int i = 0; i < n; i++) {
            int v;
            scanf("%d", &v);
            // cerr << " " << v;
            if (indexes[v] == NULL) {
                indexes[v] = new vi();
            }
            // cerr << "+" << indexes[v];
            indexes[v]->push_back(i);
        }    
        while (m--) {
            int k, v, j;
            scanf("%d %d", &k, &v);
            // cerr << k << "_" << v << "\n";
            if (indexes[v] == NULL || indexes[v]->size() < k) {
                j = 0;            
            } else {
                j = indexes[v]->at(k - 1) + 1;
            }
            printf("%d\n", j);
        }
    }    
    return 0;
}
