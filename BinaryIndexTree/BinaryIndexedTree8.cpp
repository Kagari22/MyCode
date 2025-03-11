#include <bits/stdc++.h>

// 求三元上升子序列的数量
// https://www.luogu.com.cn/problem/P1637
using namespace std;

#define MAXN 30001

vector<int> arr(MAXN);
vector<int> sort_(MAXN);
vector<long long> tree1(MAXN);
vector<long long> tree2(MAXN);

int n, m;

int lowbit(int i){
    return i & -i;
}

void add(vector<long long>& tree, int i, long long c){
    while(i <= m){
        tree[i] += c;
        i += lowbit(i);
    }
}

long long sum(vector<long long>& tree, int i){
    long long ans = 0;
    while(i > 0){
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

int rank_(int v){
    int l = 1, r = m, mid;
    int ans = 0;
    while(l <= r){
        mid = (l + r) / 2;
        if(sort_[mid] >= v){
            ans = mid;
            r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return ans;
}

long long compute(){
    sort(sort_.begin() + 1, sort_.begin() + n + 1);
    m = 1;
    for(int i = 2; i <= n; i++){
        if(sort_[m] != sort_[i]){
            sort_[++m] = sort_[i];
        }
    }
    for(int i = 1; i <= n; i++){
        arr[i] = rank_(arr[i]);
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        ans += sum(tree2, arr[i] - 1);
        add(tree1, arr[i], 1);
        add(tree2, arr[i], sum(tree1, arr[i] - 1));
    }
    return ans;
}

int main(){
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> arr[i];
        sort_[i] = arr[i];
    }

    cout << compute() << endl;

    return 0;
}