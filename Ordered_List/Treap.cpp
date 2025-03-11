#include <bits/stdc++.h>

#define INF 1e18
#define int long long
using namespace std;

template <typename T>
class Treap {
private:
    struct Node {
        T val;
        int key, sz;
        Node *lson, *rson;
        Node(T val, int key) : val(val), key(key), sz(1), lson(nullptr), rson(nullptr) {}
    } *root;

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
    Treap() : root(nullptr) {}

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
        if (p2.second) {
            p2.second = merge(p2.second->lson, p2.second->rson);
        }
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

    inline T operator[](int k) {
        return get_kth(root, k + 1);
    }
};

void solve() {
    Treap<int> treap;

    // 插入元素
    treap.insert(5);
    treap.insert(3);
    treap.insert(7);
    treap.insert(1);
    treap.insert(9);

    // 输出树的大小
    cout << "Size of treap: " << treap.size() << endl;

    // 输出第 k 小的元素
    cout << "2nd smallest element: " << treap.get(1) << endl;

    // 输出前驱和后继
    cout << "Predecessor of 5: " << treap.pre(5) << endl;
    cout << "Successor of 5: " << treap.suf(5) << endl;

    // 删除元素
    treap.remove(5);

    // 再次输出树的大小
    cout << "Size of treap after deletion: " << treap.size() << endl;

    // 检查元素是否存在
    cout << "Is 5 in treap? " << (treap.count(5) ? "Yes" : "No") << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}