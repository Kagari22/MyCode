#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

template <typename T>
class Treap {  // 有序集合  插入/删除/排名/前驱/后继
private:
    struct Node {
        T val;
        int key, sz;
        Node *lson, *rson;
        Node(T val, int key) : val(val), key(key), sz(1), lson(nullptr), rson(nullptr) {
        }
    }* root;
    int size(Node* cur) {
        return cur ? cur->sz : 0;
    }
    void up(Node* cur) {
        cur->sz = size(cur->lson) + size(cur->rson) + 1;
    }
    pair<Node*, Node*> split(Node* cur, T val) {
        if (!cur)
            return {nullptr, nullptr};
        if (cur->val <= val) {
            auto p = split(cur->rson, val);
            cur->rson = p.first;
            up(cur);
            return {cur, p.second};
        } else {
            auto p = split(cur->lson, val);
            cur->lson = p.second;
            up(cur);
            return {p.first, cur};
        }
    }
    Node* merge(Node* l, Node* r) {
        if (!l || !r)
            return l ? l : r;
        if (l->key < r->key) {
            l->rson = merge(l->rson, r);
            up(l);
            return l;
        } else {
            r->lson = merge(l, r->lson);
            up(r);
            return r;
        }
    }
    T get_kth(Node* cur, int k) {
        if (!cur)
            return T(NULL);
        if (size(cur->lson) + 1 == k)
            return cur->val;
        if (k <= size(cur->lson))
            return get_kth(cur->lson, k);
        return get_kth(cur->rson, k - size(cur->lson) - 1);
    }
 
public:
    Treap() : root(nullptr) {
    }
    ~Treap() {
        auto clear = [&](auto&& self, Node* node) -> void {
            if (node) {
                self(self, node->lson);
                self(self, node->rson);
                delete node;
            }
        };
        clear(clear, root);
    }
    void insert(T val) {
        auto p = split(root, val);
        root = merge(merge(p.first, new Node(val, rand())), p.second);
    }
    void remove(T val) {
        auto p1 = split(root, val);
        auto p2 = split(p1.first, val - 1);
        p2.second = merge(p2.second->lson, p2.second->rson);
        root = merge(merge(p2.first, p2.second), p1.second);
    }
    int size() {
        return size(root);
    }
    int count(T val) {
        auto p1 = split(root, val);
        auto p2 = split(p1.first, val - 1);
        int ans = size(p2.second);
        root = merge(merge(p2.first, p2.second), p1.second);
        return ans;
    }
    T front() {
        return get_kth(root, 1);
    }
    T back() {
        return get_kth(root, size());
    }
    T get(int k) {
        return get_kth(root, k + 1);
    }
    T pre(T val) {
        auto p = split(root, val - 1);
        T ans = get_kth(p.first, size(p.first));
        root = merge(p.first, p.second);
        return ans;
    }
    T suf(T val) {
        auto p = split(root, val);
        T ans = get_kth(p.second, 1);
        root = merge(p.first, p.second);
        return ans;
    }
    int rank(T val) {
        auto p = split(root, val - 1);
        int ans = size(p.first) + 1;
        root = merge(p.first, p.second);
        return ans;
    }
    inline int operator[](int k) {
        return get_kth(root, k + 1);
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 100;
    Treap<int> t;
    t.insert(0);
    t.insert(n + 1);

    return 0;
}