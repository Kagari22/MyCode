#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

bool ok(int n, int k){
    if(k % 2 == 1){
        return n % k == 0;
    }else{
        return n % k != 0 && 2 * n % k == 0;
    }
    return 0;
}

int consecutiveNumbersSum(int n) {
    int ans = 0;
    int mx = 2 * n;
    for(int i = 1; i * (i + 1) <= mx; i++){
        if(ok(n, i)){
            ans++;
        }
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cout << consecutiveNumbersSum(n);

    return 0;
}