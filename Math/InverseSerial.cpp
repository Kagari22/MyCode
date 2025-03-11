#include <bits/stdc++.h>

// 1∼n 中所有整数在模 p 意义下的乘法逆元
// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
      
const int MAXN = 3000001;
int inv[MAXN];
int n, p;

void build(int n){
    inv[1] = 1;
    for(int i = 2; i <= n; i++){
        inv[i] = (p - inv[p % i] * (p / i) % p);
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    cin >> n >> p;  
    build(n);
    for(int i = 1; i <= n; i++){
        cout << inv[i] << "\n";
    }
      
    return 0;
}