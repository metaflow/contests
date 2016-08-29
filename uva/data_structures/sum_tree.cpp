#include <vector>
#include <iostream>
#include <cassert>
#include <stdio.h>

using namespace std;

typedef vector<int> vi;

class SegmentedTree {
    private:
        vi st, a;
        int build_subtree(int p, int l, int r);
        int left_child(int p);
        int right_child(int p);
        int sum_subtree(int p, int l, int r, int ql, int qr);
    public:
        SegmentedTree(const vi &content);
        int sum(int i, int j);
};

SegmentedTree::SegmentedTree(const vi &content) {
    a = content;
    st.assign(4 * a.size(), 0);
    build_subtree(1, 0, a.size() - 1);
}

int SegmentedTree::left_child(int p) {
    return p * 2;
}

int SegmentedTree::right_child(int p) {
    return p * 2 + 1;
}

int SegmentedTree::build_subtree(int p, int l, int r) {
    if (l == r) {
        st[p] = l;
        return st[p];
    }
    int p1 = build_subtree(left_child(p), l, (l + r) / 2);
    int p2 = build_subtree(right_child(p), (l + r) / 2 + 1, r);
    st[p] = p1 + p2;
    return st[p];
}

int SegmentedTree::sum(int i, int j) {
    return sum_subtree(1, 0, a.size() - 1, i, j);
}

int SegmentedTree::sum_subtree(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return st[p];
    int p1 = sum_subtree(left_child(p), l, (l + r) / 2, ql, qr);
    int p2 = sum_subtree(right_child(p), (l + r) / 2 + 1, r, ql, qr);
    return p1 + p2;
}

int main() {
    vi a;
    for (int i = 0; i < 10; i++) a.push_back(i);
    SegmentedTree t(a);
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            int v = t.sum(i, j);
            printf("%d..%d %d\n", i, j, v);
            assert(v == (i + j) * (j - i + 1) / 2);
        }
    }
    return 0;
}
