#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

int lcm(int a, int b){
    return a / gcd(a, b) * b;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    int a, b;
    cin >> a >> b;
    cout << lcm(a, b) << endl;    
      
    return 0;
}