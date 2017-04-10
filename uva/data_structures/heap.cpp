#include <vector>
#include <cassert>

using namespace std;

class Heap {
private:
    vector<int> content;
    void heapify_up(int position);
    void heapify_down(int position);
public:
    void push(int value);
    void pop();
    int top();
    int size();
    Heap();
    ~Heap();
};

Heap::Heap() {
    content.clear();
    content.push_back(0);
}

Heap::~Heap() {
}

void Heap::heapify_up(int positions) {
    //TODO
}

void Heap::heapify_down(int position) {\
    //TODO
}

int Heap::size() {
    return content.size() - 1;
}

void Heap::push(int value) {
    content.push_back(value);
    heapify_up(content.size() - 1);
    //TODO
}

int Heap::top() {
    return content[1];
}

void Heap::pop() {
    content[1] = content[content.size() - 1];
    content.resize(content.size() - 1);
    heapify_down(1);
}

int main() {
    Heap h;
    assert(h.size() == 0);
    h.push(2);
    assert(2 == h.top());
    assert(h.size() == 1);
    h.pop();
    assert(h.size() == 0);
    return 0;
}
