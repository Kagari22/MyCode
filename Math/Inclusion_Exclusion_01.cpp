#include <bits/stdc++.h>

// 容斥原理 01
// https://github.com/algorithmzuo/algorithm-journey/blob/main/src/class099/Code04_NumberOfSubsetGcdK.java
// https://codeforces.com/problemset/problem/803/F
// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

int n;    
const int LIMIT = 100000;
int dp[LIMIT + 1];
int cnt[LIMIT + 1];
int pow2[LIMIT + 1];

void build(){
    pow2[0] = 1;
    for(int i = 1; i <= LIMIT; i++){
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
}

int compute(){
    for(int i = LIMIT; i >= 1; i--){
        int count = 0;
        for(int j = i; j <= LIMIT; j += i){
            count += cnt[j];
        }
        dp[i] = (pow2[count] - 1 + MOD) % MOD;
        for(int j = 2 * i; j <= LIMIT; j += i){
            dp[i] = (dp[i] - dp[j] + MOD) % MOD;
        }
    }
    return dp[1];
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    build();
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        cnt[a[i]]++;
    }
    cout << compute() << endl;
      
    return 0;
}