#include <bits/stdc++.h>

// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

struct Node {
    int val;
    Node* next;
};

void solve() {
    int n;
    cin >> n;

    // 创建第一个链表
    Node* head1 = nullptr;
    Node* tail1 = nullptr;
    for (int i = 1; i <= n; i++) {
        Node* new_Node = new Node();
        new_Node->val = i * i;  // 节点值为 i 的平方
        new_Node->next = nullptr;

        if (head1 == nullptr) {
            head1 = new_Node;
            tail1 = new_Node;
        } else {
            tail1->next = new_Node;
            tail1 = new_Node;
        }
    }

    // 创建第二个链表
    Node* head2 = nullptr;
    Node* tail2 = nullptr;
    for (int i = 1; i <= n; i++) {
        Node* new_Node = new Node();
        new_Node->val = i * 3;  // 节点值为 i * 3
        new_Node->next = nullptr;

        if (head2 == nullptr) {
            head2 = new_Node;
            tail2 = new_Node;
        } else {
            tail2->next = new_Node;
            tail2 = new_Node;
        }
    }

    // 合并两个有序链表并去重
    Node* dummy = new Node();  // 虚拟头节点
    Node* tail = dummy;        // 新链表的尾节点
    Node* a = head1;
    Node* b = head2;

    while (a && b) {
        if (a->val < b->val) {
            // 如果 a 的值较小，加入新链表
            if (tail == dummy || tail->val != a->val) {  // 去重
                tail->next = a;
                tail = a;
            }
            a = a->next;
        } else if (a->val > b->val) {
            // 如果 b 的值较小，加入新链表
            if (tail == dummy || tail->val != b->val) {  // 去重
                tail->next = b;
                tail = b;
            }
            b = b->next;
        } else {
            // 如果 a 和 b 的值相等，只加入一个
            if (tail == dummy || tail->val != a->val) {  // 去重
                tail->next = a;
                tail = a;
            }
            a = a->next;
            b = b->next;
        }
    }

    // 将剩余的节点加入新链表
    if (a) {
        tail->next = a;
    }
    if (b) {
        tail->next = b;
    }

    // 打印合并后的链表
    Node* cur = dummy->next;
    while (cur) {
        cout << cur->val << ' ';
        cur = cur->next;
    }
    cout << '\n';

    // 释放动态分配的内存
    cur = dummy->next;
    while (cur) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
    delete dummy;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}