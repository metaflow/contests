#include <iostream>
#include <utility>

using namespace std;

int n;
const int MAX = 20;

int v[MAX];
bool used[MAX];
bool prime[2 * MAX];

void output(int x) {
  int data[2];
  for(int i=0;i<2;i++) {
    data[i]=x%10;
    x/=10;
  }
  if (data[1]) putchar(data[1]+48);
  putchar(data[0]+48);
}

void backtrack(int x) {
    if (x == n) {
        if (prime[v[n - 1] + v[0]]) {
            for (int i = 0; i < n; i++) {
                if (i) putchar(' ');
                output(v[i]);
                // printf("%d", v[i]);
            }
            putchar('\n');
        }
        return;
    }
    for (int i = 2; i <= n; i++) {
        if (used[i] || (!prime[v[x - 1] + i])) continue;
        used[i] = true;
        v[x] = i;
        backtrack(x + 1);
        used[i] = false;
    }
}

void fill_primes() {
    fill(prime, prime + 2*MAX, true);
    for (int i = 2; i < 2 * MAX; i++) {
        if (!prime[i]) continue;
        int j = 2 * i;
        while (j < MAX * 2) {
            prime[j] = false;
            j += i;
        }
    }
}

int main() {
    int tc = 0;
    fill_primes();
    while(scanf("%d", &n) == 1) {
        tc++;
        if (tc != 1) {
            printf("\n");
        }
        printf("Case %d:\n", tc);
        for (int i = 1; i <= n; i++) {
            used[i] = false;
        }
        v[0] = 1;
        used[1] = true;
        backtrack(1);
    }
}
