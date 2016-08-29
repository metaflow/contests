#include <stdio.h>

struct node {
    int value;
    node *left;
    node *right;
};

class btree {
public:
    btree();
    ~btree();
    void insert(int value);
    bool contains(int value);
private:
    node *root;
    void insert(int value, node* root);
    node* find(int value, node* r);
    void delete_subtree(node *root);
};

btree::btree() {
    root = NULL;
}

btree::~btree() {
    delete_subtree(root);
}

void btree::delete_subtree(node *r) {
    if (r == NULL) return;
    delete_subtree(r->left);
    delete_subtree(r->right);
    delete r;
}

void btree::insert(int value) {
    if (root == NULL) {
        root = new node();
        root->value = value;
        return;
    }
    insert(value, root);
}

void btree::insert(int value, node* r) {
    if (value < r->value) {
        if (r->left != NULL) {
            insert(value, r->left);
            return;
        }
        r->left = new node();
        r->left->value = value;
    } else {
        if (r->right != NULL) {
            insert(value, r->right);
            return;
        }
        r->right = new node();
        r->right->value = value;
    }
}

bool btree::contains(int value) {
    node *n = find(value, root);
    return (n != NULL);
}

node* btree::find(int value, node* r) {
    if (r == NULL || r->value == value) return r;
    if (value < r->value) return find(value, r->left);
    return find(value, r->right);
}

int main() {
    int m, n;
    while (scanf("%d%d", &n, &m), m != 0 && n != 0) {
        btree b;
        while (n--) {
            int v;
            scanf("%d", &v);
            b.insert(v);
        }
        int r = 0;
        while (m--) {
            int v;
            scanf("%d", &v);
            if (b.contains(v)) r++;
        }
        printf("%d\n", r);
    }
    return 0;
}
