#include <bits/stdc++.h>

// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

template<class T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for(auto &x : v) {
        is >> x;
    }
    return is;
}
 
class FHQTreap {
public:
    FHQTreap() {}
    FHQTreap(int n) {
        init(n);
    }
 
    void add(int num, int c) { // 插入元素
        split(0, 0, head, num);
        key[++cnt] = num;
        size[cnt] = 1;
        priority[cnt] = c;
        head = merge(merge(rs[0], cnt), ls[0]);
    }
 
    void remove(int num) { // 删除值为 num 的元素
        split(0, 0, head, num);
        int lm = rs[0];
        int r = ls[0];
        split(0, 0, lm, num - 1);
        int l = rs[0];
        int m = ls[0];
        head = merge(merge(l, merge(ls[m], rs[m])), r);
    }
 
    int rank(int num) { // 查询元素排名 查询小于等于 num 的元素个数
        split(0, 0, head, num - 1);
        int ans = size[rs[0]] + 1;
        head = merge(rs[0], ls[0]);
        return ans;
    }
 
    int index(int x) { // 查询树中排名为 x 的元素的值
        return index(head, x);
    }
 
    int pre(int num) { // 查询小于 num 的最大元素
        return pre(head, num);
    }
 
    int post(int num) { //  查询大于 num 的最小元素
        return post(head, num);
    }
 
    int find(int num) { // 查询 >= num 的所有元素的最小优先级是多少
        int cur = head;
        int ret = 1e18;
        while(cur) {
            if(key[cur] > num) {
                ret = std::min(ret, priority[cur]);
                cur = ls[cur];
            } else if(key[cur] < num) {
                cur = rs[cur];
            } else {
                return std::min(priority[cur], ret);
            }
        }
        return ret; // 返回优先级
    }
private:
    void init(int n) {
        head = cnt = 0;
        ls.resize(n + 1, 0);
        rs.resize(n + 1, 0);
        size.resize(n + 1, 0);
        key.resize(n + 1, 0);
        priority.resize(n + 1, 0);
    }
 
    void up(int i) {
        size[i] = size[ls[i]] + size[rs[i]] + 1;
    }
 
    void split(int l, int r, int i, int num) {
        if(i == 0) {
            rs[l] = ls[r] = 0;
        } else {
            if(key[i] <= num) {
                rs[l] = i;
                split(i, r, rs[i], num);
            } else {
                ls[r] = i;
                split(l, i, ls[i], num);
            }
            up(i);
        }
    }
 
    int merge(int l, int r) {
        if(l == 0 || r == 0) {
            return l + r;
        } else {
            if(priority[l] <= priority[r]) {
                rs[l] = merge(rs[l], r);
                up(l);
                return l;
            } else {
                ls[r] = merge(l, ls[r]);
                up(r);
                return r;
            }
        }
    }
 
    int index(int i, int x) {
        if(size[ls[i]] >= x) {
            return index(ls[i], x);
        } else if(size[ls[i]] + 1 < x) {
            return index(rs[i], x - size[ls[i]] - 1);
        } else {
            return key[i];
        }
    }
 
    int pre(int i, int num) {
        if(i == 0) {
            return std::numeric_limits<int>::min();
        }
        if(key[i] >= num) {
            return pre(ls[i], num);
        } else {
            return std::max(key[i], pre(rs[i], num));
        }
    }
 
    int post(int i, int num) {
        if(i == 0) {
            return std::numeric_limits<int>::max();
        }
 
        if(key[i] <= num) {
            return post(rs[i], num);
        } else {
            return std::min(key[i], post(ls[i], num));
        }
    }
 
    int head, cnt;
    std::vector<int> ls, rs, size, key;
    std::vector<int> priority;
}; 

void solve() {
    int n;
    cin >> n;

    FHQTreap treap(n);

    // 添加元素
    treap.add(10, 5);  
    treap.add(20, 3);  
    treap.add(24, 8);
    treap.add(30, 6);
    treap.add(40, 2);

    cout << treap.pre(25) << '\n';
    cout << treap.rank(26) << '\n';
    cout << treap.index(3) << '\n';
    cout << treap.find(22) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while(t--){
        solve();
    }

    return 0;
}