#include "assert.h"
#include "stdio.h"

struct Node {
    Node *left, *right, *parent;
    int key;
    int value;
};

class SplayTree {
private:
    Node *root;
    void delete_subtree(Node *x);
    void splay(Node *x);
    void rotate(Node *x);
    void remove_node(Node *x);
    bool is_leaf(Node *n);
    Node *find_closest(int key);
    Node* find(int key);
    bool is_binary_subtree(Node *n); // for testing
public:
    SplayTree();
    ~SplayTree();
    void insert(int key, int value);
    bool contains(int key);
    int get(int key);
    void remove(int key);
    int min();
    int max();
};

SplayTree::SplayTree() {
    root = NULL;
}

SplayTree::~SplayTree() {
    delete_subtree(root);
}

bool SplayTree::is_binary_subtree(Node *n) {
    if (!n) return true;
    if (n->left) {
        if (n->left->key > n->key) return false;
        if (!is_binary_subtree(n->left)) return false;
    }
    if (n->right) {
        if (n->key > n->right->key) return false;
        if (!is_binary_subtree(n->right)) return false;
    }
    return true;
}

bool SplayTree::is_leaf(Node *n) {
    if (!n) return false;
    return (!n->left && !n->right);
}

void SplayTree::insert(int key, int value) {
    assert(is_binary_subtree(root));
    Node *p = find_closest(key);
    if (p != NULL && p->key == key) {
        p->value = value;
        splay(p);
        return;
    }
    Node *x = new Node();
    x->parent = p;
    x->key = key;
    x->value = value;
    if (p != NULL) {
        if (key < p->key) {
            p->left = x;
        } else {
            p->right = x;
        }
        splay(x);
    } else {
        root = x;
    }
}

void SplayTree::rotate(Node *x) {
    if (x == NULL || x->parent == NULL) return;
    Node *p = x->parent;
    Node *g = p->parent;
    //update grandparent link
    x->parent = g;
    if (g) {
        if (g->left == p) {
            g->left = x;
        } else {
            g->right = x;
        }
    } else {
        root = x;
    }
    //move subtrees and set p as child of x
    if (p->left == x) {
        p->left = x->right;
        if (p->left) p->left->parent = p;
        x->right = p;
    } else {
        p->right = x->left;
        if (p->right) p->right->parent = p;
        x->left = p;
    }
    p->parent = x;
}

void SplayTree::splay(Node *x) {
    if (x == NULL || x->parent == NULL) return;
    Node *p = x->parent;
    Node *g = p->parent;
    if (g) {
        if ((g->left == p) == (p->left == x)) {
            rotate(p);
        } else {
            rotate(x);
        }
    }
    rotate(x);
    splay(x);
}

Node* SplayTree::find_closest(int key) {
    assert(is_binary_subtree(root));
    Node *t = root;
    if (!t) return NULL;
    while (t->key != key) {
        if (key < t->key) {
            if (!t->left) return t;
            t = t->left;
        } else {
            if (!t->right) return t;
            t = t->right;
        }
    }
    return t;
}

Node* SplayTree::find(int key) {
    assert(is_binary_subtree(root));
    Node *t = find_closest(key);
    if (!t || t->key != key) return NULL;
    return t;
}

bool SplayTree::contains(int key) {
    Node *t = find(key);
    return t != NULL;
}

int SplayTree::get(int key) {
    assert(is_binary_subtree(root));
    Node *t = find(key);
    splay(t);
    if (t) return t->value;
    return 0;
}

int SplayTree::max() {
    assert(is_binary_subtree(root));
    Node *t = root;
    if (!t) return 0;
    while (t->right) t = t->right;
    return t->key;
}

int SplayTree::min() {
    assert(is_binary_subtree(root));
    Node *t = root;
    if (!t) return 0;
    while (t->left) t = t->left;
    return t->key;
}

void SplayTree::delete_subtree(Node *x) {
    if (!x) return;
    delete_subtree(x->left);
    delete_subtree(x->right);
    delete x;
}

void SplayTree::remove(int key) {
    Node *t = find(key);
    splay(t);
    remove_node(t);
}

void SplayTree::remove_node(Node *n) {
    assert(is_binary_subtree(root));
    if (!n) return;
    Node *p = n->parent;
    if (is_leaf(n)) {
        if (p) {
            if (p->left == n) p->left = NULL;
            if (p->right == n) p->right = NULL;
        } else {
            root = NULL;
        }
    } else {
        Node *c;
        if (n->left) {
            c = n->left;
            while (c->right) c = c->right;
        } else {
            c = n->right;
            while (c->left) c = c->left;
        }
        // delete c from original location
        Node *t = c->left;
        if (!t) t = c->right;
        if (c->parent->left == c) c->parent->left = t;
        if (c->parent->right == c) c->parent->right = t;
        if (t) t->parent = c->parent;
        // replace n with c
        c->parent = p;
        if (p) {
            if (p->left == n) p->left = c;
            if (p->right == n) p->right = c;
        } else {
            root = c;
        }
        c->left = n->left;
        if (c->left) c->left->parent = c;
        c->right = n->right;
        if (c->right) c->right->parent = c;
    }

    delete n;
}

int main() {
    SplayTree t;
    t.insert(2, 9);
    t.insert(1, 8);
    t.insert(3, 7);
    t.insert(5, -9);
    t.insert(0, 34);
    t.insert(3, 17);
    printf("min %d max %d\n", t.min(), t.max());
    assert(5 == t.max());
    assert(0 == t.min());
    assert(t.contains(0));
    t.remove(0);
    printf("min %d max %d\n", t.min(), t.max());
    assert(1 == t.min());
    assert(t.contains(1));
    assert(!t.contains(0));
    printf("[ %d %d ]\n", t.get(t.min()), t.get(t.max()));
    return 0;
}
