#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct node;
using pnode = shared_ptr<node>;

struct node {
  int data;
  pnode left, right;
};

default_random_engine source(random_device{}());

ll random_in_range(ll a, ll b) {
  return uniform_int_distribution<ll>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

pnode random_tree(ll size, vi data, ll data_pos) {
  if (size == 0) return NULL;
  pnode root = make_shared<node>();
  root->data = data[data_pos];
  data_pos++;
  size--;
  ll left_size = random_in_range(0, size);
  root->left = random_tree(left_size, data, data_pos);
  data_pos += left_size;
  root->right = random_tree(size - left_size, data, data_pos);
  return root;
}

void traverse_inorder(pnode root, vi& out) {
  if (!root) return;
  traverse_inorder(root->left, out);
  out.emplace_back(root->data);
  traverse_inorder(root->right, out);
}

void traverse_postorder(pnode root, vi& out) {
  if (!root) return;
  traverse_postorder(root->left, out);
  traverse_postorder(root->right, out);
  out.emplace_back(root->data);
}

pnode restore(pnode left, vi::iterator& io, vi::iterator& po, int stop) {
  if (*po == stop) return left;
  pnode u = make_shared<node>();
  u->left = left;
  u->data = *io;
  io++;
  if (u->data != *po) {
    u->right = restore(NULL, io, po, u->data);
  }
  po++;
  return restore(u, io, po, stop);
}

void print_tree(pnode root) {
  if (!root) return;
  cout << "("; print_tree(root->left); cout << ")";
  cout << " " << root->data << " ";
  cout << "("; print_tree(root->right); cout << ")";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  for (ll j = 0; j < 1000; j++) {
    ll n = random_in_range(1, 10);
    vi data(n);
    for (ll i = 0; i < n; i++) data[i] = i;
    auto t = random_tree(n, data, 0);

    vi io, po;
    traverse_inorder(t, io);
    traverse_postorder(t, po);
    // cout << "{";
    // for (auto i : io) cout << i << ", ";
    // cout << "}" << endl;
    // cout << "{";
    // for (auto i : po) cout << i << ", ";
    // cout << "}" << endl;
    io.emplace_back(-1);
    po.emplace_back(-1);
    auto it1 = io.begin();
    auto it2 = po.begin();
    auto restored = restore(NULL, it1, it2, po.back());
    // if (!restored || restored->data != po.back()) {
    //   pnode v = make_shared<node>();
    //   v->left = restored;
    //   v->data = po.back();
    //   swap(v, restored);
    // }
    vi rio, rpo;
    traverse_inorder(restored, rio);
    traverse_postorder(restored, rpo);
    io.pop_back();
    po.pop_back();
    if (io == rio && rpo == po) continue;
    cout << "!!!!" << endl;
    print_tree(t); cout << endl;
    print_tree(restored); cout << endl;
    break;
  }

}
