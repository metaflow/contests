#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> c(100001);
    vector<int> h(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i] >> a[i];
        c[h[i]]++;
    }
    for (int i = 0; i < n; i++) {
        cout << (n-1 + c[a[i]]) << " " << (n - 1 - c[a[i]]) << endl;
    }
}
