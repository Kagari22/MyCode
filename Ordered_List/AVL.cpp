#include <bits/stdc++.h>

// AVL树模板
// https://www.luogu.com.cn/problem/P3369
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

class AVLTree {
public:
    int cnt;  
    int head;  
    vector<int> key, height, left, right, count, size;

    AVLTree(int n) {
        cnt = 0;
        head = 0;
        key.resize(n + 1);
        height.resize(n + 1);
        left.resize(n + 1);
        right.resize(n + 1);
        count.resize(n + 1);
        size.resize(n + 1);
    }

    void up(int i) {
        size[i] = size[left[i]] + size[right[i]] + count[i];
        height[i] = std::max(height[left[i]], height[right[i]]) + 1;
    }

    int leftRotate(int i) {
        int r = right[i];
        right[i] = left[r];
        left[r] = i;
        up(i);
        up(r);
        return r;
    }

    int rightRotate(int i) {
        int l = left[i];
        left[i] = right[l];
        right[l] = i;
        up(i);
        up(l);
        return l;
    }

    int maintain(int i) {
        int lh = height[left[i]];
        int rh = height[right[i]];
        if (lh - rh > 1) {
            if (height[left[left[i]]] >= height[right[left[i]]]) {
                i = rightRotate(i);
            } else {
                left[i] = leftRotate(left[i]);
                i = rightRotate(i);
            }
        } else if (rh - lh > 1) {
            if (height[right[right[i]]] >= height[left[right[i]]]) {
                i = leftRotate(i);
            } else {
                right[i] = rightRotate(right[i]);
                i = leftRotate(i);
            }
        }
        return i;
    }

    // 加数
    void add(int num) {
        head = add(head, num);
    }

    int add(int i, int num) {
        if (i == 0) {
            key[++cnt] = num;
            count[cnt] = size[cnt] = height[cnt] = 1;
            return cnt;
        }
        if (key[i] == num) {
            count[i]++;
        } else if (key[i] > num) {
            left[i] = add(left[i], num);
        } else {
            right[i] = add(right[i], num);
        }
        up(i);
        return maintain(i);
    }

    // 删数
    void remove(int num) {
        if (rank(num) != rank(num + 1)) {
            head = remove(head, num);
        }
    }

    int remove(int i, int num) {
        if (key[i] < num) {
            right[i] = remove(right[i], num);
        } else if (key[i] > num) {
            left[i] = remove(left[i], num);
        } else {
            if (count[i] > 1) {
                count[i]--;
            } else {
                if (left[i] == 0 && right[i] == 0) {
                    return 0;
                } else if (left[i] != 0 && right[i] == 0) {
                    i = left[i];
                } else if (left[i] == 0 && right[i] != 0) {
                    i = right[i];
                } else {
                    int mostLeft = right[i];
                    while (left[mostLeft] != 0) {
                        mostLeft = left[mostLeft];
                    }
                    right[i] = removeMostLeft(right[i], mostLeft);
                    left[mostLeft] = left[i];
                    right[mostLeft] = right[i];
                    i = mostLeft;
                }
            }
        }
        up(i);
        return maintain(i);
    }

    int removeMostLeft(int i, int mostLeft) {
        if (i == mostLeft) {
            return right[i];
        } else {
            left[i] = removeMostLeft(left[i], mostLeft);
            up(i);
            return maintain(i);
        }
    }

    // 查询排名 即多少个数比 num 小
    int rank(int num) {
        return small(head, num) + 1;
    }

    int small(int i, int num) {
        if (i == 0) {
            return 0;
        }
        if (key[i] >= num) {
            return small(left[i], num);
        } else {
            return size[left[i]] + count[i] + small(right[i], num);
        }
    }

    // 如果将集合排序后 排名位于第 x 位的数
    int index(int x) {
        return index(head, x);
    }

    int index(int i, int x) {
        if (size[left[i]] >= x) {
            return index(left[i], x);
        } else if (size[left[i]] + count[i] < x) {
            return index(right[i], x - size[left[i]] - count[i]);
        }
        return key[i];
    }

    // 寻找前驱 即小于 num 且最大的数
    int pre(int num) {
        return pre(head, num);
    }

    int pre(int i, int num) {
        if (i == 0) {
            return -INF;
        }
        if (key[i] >= num) {
            return pre(left[i], num);
        } else {
            return std::max(key[i], pre(right[i], num));
        }
    }

    // 寻找后继 即大于 num 且最小的数
    int post(int num) {
        return post(head, num);
    }

    int post(int i, int num) {
        if (i == 0) {
            return INF;
        }
        if (key[i] <= num) {
            return post(right[i], num);
        } else {
            return std::min(key[i], post(left[i], num));
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    AVLTree tree(n + 1);

    for (int i = 1; i <= m; i++) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            tree.add(x);
        } else if (op == 2) {
            tree.remove(x);
        } else if (op == 3) {
            cout << tree.rank(x) << '\n';
        } else if (op == 4) {
            cout << tree.index(x) << '\n';
        } else if (op == 5) {
            cout << tree.pre(x) << '\n';
        } else {
            cout << tree.post(x) << '\n';
        }
    }
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