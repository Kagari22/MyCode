#include <bits/stdc++.h>

// 最大公约数
// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
      
int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
      
    return 0;
}