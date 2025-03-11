#include <bits/stdc++.h>

// 逆元与除法同余
// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
      
int compute1(int a, int b, int mod){
    return (a / b) % mod;
}

int power(int b, int n, int mod){
    int ans = 1;
    while(n > 0){
        if((n & 1) == 1){
            ans = (ans * b) % mod;
        }
        b = (b * b) % mod;
        n >>= 1;
    }
    return ans;
}

int calc(int a, int b, int mod){
    int inv = power(b, mod - 2, mod);
    return ((a % mod) * inv) % mod;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    // 必须保证 a / b 可以整除
    // 必须保证 mod 是质数
    // 必须保证 b 和 mod 的最大公约数是 1
    int mod = 41;
    int b = 3671613;
    int a = 67312 * b;
    cout << compute1(a, b, mod) << "\n";
    cout << calc(a, b, mod) << "\n";
      
    return 0;
}