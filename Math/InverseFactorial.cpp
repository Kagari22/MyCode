#include <bits/stdc++.h>

// 连续阶乘逆元的线性递推
// 实现组合公式 C(n,m) 的计算
// 最终结果 % 1000000007 后返回
// 0 <= m <= n <= 1000
// from: cpp.json
#define i128 __int128_t
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
      
const int LIMIT = 1000;
int fac[LIMIT + 1];
int inv[LIMIT + 1];

int power(int x, int n){
    int ans = 1;
    while(n > 0){
        if((n & 1) == 1){
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ans;
}

void build(){
    fac[0] = 1;
    fac[1] = 1;
    for(int i = 2; i <= LIMIT; i++){
        fac[i] = (i * fac[i - 1]) % MOD;
    }
    inv[LIMIT] = power(fac[LIMIT], MOD - 2);
    for(int i = LIMIT - 1; i >= 0; i--){
        inv[i] = ((i + 1) * inv[i + 1]) % MOD;
    }
}

int c(int n, int m){
    int ans = fac[n];
    ans = (ans * inv[m]) % MOD;
    ans = (ans * inv[n - m]) % MOD;
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    build();
    cout << c(5, 2);
    
    return 0;
}