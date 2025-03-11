#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

vector<int> divisors(int n) {
    vector<int> divs;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);  
            if (i != n / i) {
                divs.push_back(n / i);  
            }
        }
    }
    return divs;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> divs = divisors(n);
    for (int d : divs) {
        cout << d << " ";
    }

    return 0;
}