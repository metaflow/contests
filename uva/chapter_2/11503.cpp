#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct node {
    int size;
    int parent;
};

map<string, int> names;
vector<node> people;

int get_index(string &name) {
    map<string, int>::iterator e = names.find(name);
    if (e != names.end()) return e->second;
    node n;
    n.size = 1;
    n.parent = people.size();
    people.push_back(n);
    names[name] = n.parent;
    return n.parent;
}

int get_parent(int a) {
    int i = a;
    while (a != people[a].parent) a = people[a].parent;
    people[i].parent = a;
    return a;
}

int join(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a == b) return a;
    if (people[a].size < people[b].size) swap(a, b);
    people[a].size += people[b].size;
    people[b].parent = a;
    return a;
}

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        names.clear();
        people.clear();
        int f;
        cin >> f;
        while (f--) {
            string a, b;
            cin >> a >> b;
            int i = get_index(a);
            int j = get_index(b);
            i = join(i, j);
            cout << people[i].size << '\n';
        }
    }
    return 0;
}
