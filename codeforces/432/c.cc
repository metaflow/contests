#include <iostream>
#include <vector>

using namespace std;

int pr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317};

vector<pair<int,int>> ops;
vector<int> a;
vector<int> pos;

void swap(int l, int d) {
    if (d == 0) return;
    int r = d + l - 1;
    ops.push_back(make_pair(l + 1, r + 1));
    int t = a[l];
    a[l] = a[r];
    a[r] = t;
    pos[a[l]] = l;
    pos[a[r]] = r;
}

int main() {
    int n;
    cin >> n;
    a.resize(n);
    pos.resize(n + 1);
    vector<int> primes;
    for (int i = 0; i < 66; i++) {
        primes.push_back(pr[i]);
    }
    for (int i = 318; i < 100004; i++) {
        int f = true;
        for (int j = 0; j < 66; j++) {
            if (i % primes[j] == 0) {
                f = false;
                break;
            }
        }
        if (f) primes.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    for (int x = 1; x <= n; x++) {
        int p = pos[x];
        int d = p - x + 2;
        if (d == 1) continue;
        bool found = false;
        int d1 = 0, d2 = 0;
        for (int i = 0; i < primes.size(); i++) {
            if (d < primes[i]) break;
            if (d > primes[i]) continue;
            swap(x - 1, d);
            found = true;
        }
        if (!found) {
            d++;
            if (d % 2 == 0) {
                for (int i = 0; i < primes.size() && !found; i++)
                for (int j = i; j < primes.size() && !found; j++) {
                    if (d > primes[i] + primes[j]) continue;
                    if (d < primes[i] + primes[j]) break;
                    swap(p - primes[i] + 1, primes[i]);
                    swap(x-1, primes[j]);
                    // printf("%d = %d + %d\n", d, primes[i], primes[j]);
                    found = true;
                }
            } else {
                d--;
                swap(p - 1, 2);
                p--;
                for (int i = 0; i < primes.size() && !found; i++)
                for (int j = i; j < primes.size() && !found; j++) {
                    if (d > primes[i] + primes[j]) continue;
                    if (d < primes[i] + primes[j]) break;
                    swap(p - primes[i] + 1, primes[i]);
                    swap(x-1, primes[j]);
                    // printf("%d = 2 + %d + %d\n", d + 2, primes[i], primes[j]);
                    found = true;
                }
            }
        }

    }
    cout << ops.size() << endl;
    for (auto p : ops) {
        cout << p.first << " " << p.second << endl;
    }
}
