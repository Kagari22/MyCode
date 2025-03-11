#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

vector<int> commonDivisors(int a, int b) {
    int g = gcd(a, b);
    vector<int> divisors;

    for (int i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            divisors.push_back(i);  
            if (i != g / i) {
                divisors.push_back(g / i); 
            }
        }
    }

    return divisors;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    vector<int> divisors = commonDivisors(a, b);
    sort(divisors.begin(), divisors.end());
    for (int d : divisors) {
        cout << d << " ";
    }

    return 0;
}