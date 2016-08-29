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
        int query_subtree(int p, int l, int r, int ql, int qr);
        int replace_subtree(int p, int l, int r, int ql, int qr, int value);
    public:
        SegmentedTree(const vi &content);
        int query(int i, int j);
        int get(int idx);
        int size();
        void replace(int index, int value);
        void replace_region(int from, int to, int value);
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
    if (a[p1] < a[p2]) {
        st[p] = p1;
    } else {
        st[p] = p2;
    }
    return st[p];
}

int SegmentedTree::query(int i, int j) {
    return query_subtree(1, 0, a.size() - 1, i, j);
}

int SegmentedTree::query_subtree(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return -1;
    if (ql <= l && r <= qr) return st[p];
    int p1 = query_subtree(left_child(p), l, (l + r) / 2, ql, qr);
    int p2 = query_subtree(right_child(p), (l + r) / 2 + 1, r, ql, qr);
    if (p2 == -1) return p1;
    if (p1 == -1) return p2;
    if (a[p1] < a[p2]) return p1;
    return p2;
}

void SegmentedTree::replace(int index, int value) {
    replace_subtree(1, 0, a.size() - 1, index, index, value);
}

void SegmentedTree::replace_region(int from, int to, int value) {
    replace_subtree(1, 0, a.size() - 1, from, to, value);
}

// return updated index if it was changed or -1 if not
int SegmentedTree::replace_subtree(int p, int l, int r,
        int ql, int qr, int value) {
    if (qr < l || r < ql) return -1;
    if (l == r) {
        a[l] = value;
        return l;
    }
    int i = replace_subtree(left_child(p), l, (l + r) / 2, ql, qr, value);
    int j = replace_subtree(right_child(p), (l + r) / 2 + 1, r, ql, qr, value);
    int v = st[p];
    if (i != -1 && a[i] < a[v]) v = i;
    if (j != -1 && a[j] < a[v]) v = j;
    st[p] = v;
    return v;
}

int SegmentedTree::get(int i) {
    return a[i];
}

int SegmentedTree::size() {
    return a.size();
}

void assert_query(SegmentedTree &t, int l, int r) {
    int v = t.query(l, r);
    int e = l;
    for (int i = l; i <= r; i++) {
        if (t.get(i) < t.get(e)) e = i;
    }
    if (e != v) {
        cerr << "assertion failed for query " << l << ".." << r;
        cerr << " on tree \n";
        for (int i = 0; i < t.size(); i++) {
            cerr << t.get(i) << " ";
        }
        cerr << "\n";
        cerr << "expected " << e << " but " << v << "\n";
    }
    assert(e == v);
}

void assert_tree(SegmentedTree &t) {
    for (int i = 0; i < t.size(); i++) {
        for (int j = i; j < t.size(); j++) {
            int v = t.query(i, j);
            assert_query(t, i, j);
        }
    }
}

int main() {
    vi a;
    for (int i = 0; i < 10; i++) a.push_back(i);
    SegmentedTree t(a);
    assert_tree(t);
    t.replace(4, -1);
    assert_tree(t);
    t.replace_region(5, 6, -2);
    assert_tree(t);
    return 0;
}
