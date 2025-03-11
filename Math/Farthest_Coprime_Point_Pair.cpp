#include <bits/stdc++.h>

// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

void solve() {
    int l, r;
    cin >> l >> r;

    for (auto ans = r - l; ; ans--) {
        for (auto i = l; i + ans <= r; i++) {
            if (__gcd(i, ans) == 1) {
                cout << ans << '\n';
                return;
            }
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