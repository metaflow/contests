#include <set>
#include <stdio.h>

using namespace std;

int main() {
    int days;
    while (scanf("%d", &days), days != 0) {
        int total = 0;
        multiset<int> s;
        int k;
        int v;
        multiset<int>::iterator it;
        while (days--) {
            scanf("%d", &k);
            while (k--) {
                scanf("%d", &v);
                s.insert(v);
            }
            it = s.end();
            total += *(--it);
            s.erase(it);
            it = s.begin();
            total -= *it;
            s.erase(it);
        }
        printf("%d\n", total);
    }
    return 0;
}
