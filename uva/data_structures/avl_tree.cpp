#include "stdio.h"
#include "assert.h"
#include <algorithm>

using namespace std;

struct Node {
    Node *left, *right, *parent;
    int key;
    int height; // of maximum subtree starting at this node
};

class AvlTree {
    private:
        Node * root;
        void update_height(Node *n);
        void delete_subtree(Node *n);
        void balance(Node *n);
        Node *find_closest(int key);
        Node *find(int key);
        int left_subtree_height(Node *n);
        int right_subtree_height(Node *n);
        void rotate(Node *n);
        bool is_leaf(Node *n);
    public:
        AvlTree();
        ~AvlTree();
        void insert(int key);
        void remove(int key);
        bool contains(int key);
        int min_key();
        int max_key();
};

AvlTree::AvlTree() {
    root = NULL;
}

AvlTree::~AvlTree() {
    delete_subtree(root);
}

void AvlTree::delete_subtree(Node *n) {
    if (!n) return;
    delete_subtree(n->left);
    delete_subtree(n->right);
    delete n;
}

int AvlTree::max_key() {
    if (!root) return 0;
    Node *n = root;
    while (n->right) n = n->right;
    return n->key;
}

int AvlTree::min_key() {
    if (!root) return 0;
    Node *n = root;
    while (n->left) n = n->left;
    return n->key;
}

void AvlTree::update_height(Node *n) {
    if (!n) return;
    int h = max(left_subtree_height(n), right_subtree_height(n)) + 1;
    if (h == n->height) return;
    n->height = h;
    update_height(n->parent);
}

int AvlTree::left_subtree_height(Node *n) {
    if (!n || !n->left) return 0;
    return n->left->height;
}

int AvlTree::right_subtree_height(Node *n) {
    if (!n || !n->right) return 0;
    return n->right->height;
}

bool AvlTree::contains(int key) {
    Node *t = find(key);
    return (t != NULL);
}

Node* AvlTree::find_closest(int key) {
    if (!root) return NULL;
    Node *t = root;
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

bool AvlTree::is_leaf(Node *n) {
    if (!n) return false;
    return (!n->left && !n->right);
}

void AvlTree::remove(int key) {
    Node *t = find(key);
    if (!t) return;
    Node *p = t->parent;
    Node *c = NULL;
    if (!is_leaf(t)) {
        Node *c;
        Node *o = NULL;
        if (t->left) {
            c = t->left;
            while (c->right) c = c->right;
            o = c->left;
        } else {
            c = t->right;
            while (c->left) c = c->left;
            o = c->right;
        }

        if (o) {
            o->parent = c->parent;
            if (c->parent->left == c) {
                o->parent->left = o;
            } else {
                o->parent->right = o;
            }
            update_height(o->parent);
        }

        c->parent = p;
        c->left = t->left;
        if (c->left) c->left->parent = c;
        c->right = t->right;
        if (c->right) c->right->parent = c;
        update_height(c);
    }

    if (p) {
        if (p->left == t) {
            p->left = c;
        } else {
            p->right = c;
        }
        update_height(p);
    } else {
        root = c;
    }
    delete t;
}

Node* AvlTree::find(int key) {
    Node *t = find_closest(key);
    if (!t || t->key != key) return NULL;
    return t;
}

void AvlTree::insert(int key) {
    Node *p = find_closest(key);
    if (p) {
        if (p->key == key) return;
        Node *n = new Node();
        n->key = key;
        n->height = 1;
        if (key < p->key) {
            p->left = n;
        } else {
            p->right = n;
        }
        n->parent = p;
        balance(p);
    } else {
        Node *n = new Node();
        n->key = key;
        n->height = 1;
        n->parent = NULL;
        root = n;
    }
}

void AvlTree::balance(Node *n) {
    if (!n) return;
    update_height(n);
    int l = left_subtree_height(n);
    int r = right_subtree_height(n);
    if (l - r > 1) {
        Node *a = n->left;
        if (left_subtree_height(a) < right_subtree_height(a)) rotate(a->right);
        rotate(n->left);
    }

    if (r - l > 1) {
        Node *a = n->right;
        if (left_subtree_height(a) > right_subtree_height(a)) rotate(a->left);
        rotate(n->right);
    }
    balance(n->parent);
}

void AvlTree::rotate(Node *n) {
    if (!n || !n->parent) return;
    Node *p = n->parent;
    Node *g = p->parent;
    n->parent = g;
    if (g) {
        if (g->left == p) {
            g->left = n;
        } else {
            g->right = n;
        }
    } else {
        root = n;
    }
    if (p->left = n) {
        p->left = n->right;
        if (p->left) p->left->parent = p;
        n->right = p;
    } else {
        p->right = n->left;
        if (p->right) p->right->parent = p;
        n->left = p;
    }
    p->parent = n;
    update_height(p);
}

int main() {
    AvlTree t;
    t.insert(2);
    t.insert(1);
    t.insert(3);
    t.insert(5);
    t.insert(0);
    t.insert(3);
    printf("min %d max %d\n", t.min_key(), t.max_key());
    assert(5 == t.max_key());
    assert(0 == t.min_key());
    assert(t.contains(0));
    t.remove(0);
    assert(!t.contains(0));
    assert(1 == t.min_key());
    assert(t.contains(1));
    t.remove(1);
    assert(!t.contains(1));
    assert(2 == t.min_key());
    return 0;
}
