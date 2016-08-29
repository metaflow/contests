#include <vector>
#include <stdio.h>
#include <iostream>

using namespace std;

typedef vector<int> vi;

const int MAX = 26;

struct area {
    bool awake;
    int awake_connections;
    bool connected_to[MAX];
    bool present;
};

int main() {
    int n;
    while (scanf("%d\n", &n) == 1) {
        vector<area> brain(MAX);
        int year = 0;
        int m;
        scanf("%d\n", &m);
        int sleep_count = n;
        vi to_awake;
        for (int i = 0; i < 3; i++) {
            char a;
            scanf("%c", &a);
            a -= 'A';
            to_awake.push_back(a);
            brain[a].present = true;
        }
        for (int i = 0; i < m; i++) {
            char a, b;
            scanf("\n%c%c", &a, &b);
            a -= 'A';
            b -= 'A';
            brain[a].connected_to[b] = true;
            brain[b].connected_to[a] = true;
            brain[a].present = true;
            brain[b].present = true;
        }
        while (!to_awake.empty()) {
            while (!to_awake.empty()) {
                int j = to_awake.back();
                to_awake.pop_back();
                if (brain[j].awake) continue;
                brain[j].awake = true;
                sleep_count--;
                for (int i = 0; i < MAX; i++) {
                    if (!brain[j].connected_to[i]) continue;
                    if (brain[i].awake) continue;
                    brain[i].awake_connections++;
                }
            }
            if (sleep_count == 0) break;
            year++;
            for (int i = 0; i < MAX; i++) {
                if (!brain[i].present || brain[i].awake || brain[i].awake_connections < 3) continue;
                to_awake.push_back(i);
            }
        }
        if (sleep_count > 0) {
            printf("THIS BRAIN NEVER WAKES UP\n");
        } else {
            printf("WAKE UP IN, %d, YEARS\n", year);
        }
    }
    return 0;
}
