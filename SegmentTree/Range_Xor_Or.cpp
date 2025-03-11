#include <bits/stdc++.h>

// from: cpp.json
#define INF 1e18
#define int long long
using namespace std;

void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> preXor(n + 1);
    vector<vector<int>> b(n + 1, vector<int>(32));
    vector<vector<int>> preOr(n + 1, vector<int>(32));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 31; j++) {
            b[i][j] = (a[i] >> j) & 1;
        }
    } 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 31; j++) {
            preOr[i + 1][j] = preOr[i][j] + b[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        preXor[i + 1] = preXor[i] ^ a[i];
    }
    for (int i = 0; i < q; i++) {
        int op, l, r;
        cin >> op >> l >> r;
        int Xor = preXor[r] ^ preXor[l - 1];  
        int Or = 0;
        for (int j = 0; j < 31; j++) {
            if (preOr[r][j] - preOr[l - 1][j] > 0) {
                Or |= (1 << j);
            }
        }
        cout << abs(Xor - Or) << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}