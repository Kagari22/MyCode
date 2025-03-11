#include <bits/stdc++.h>

// 给定一个线性方程组求其求解
// https://www.luogu.com.cn/problem/P3389
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MAXN = 114;

double diff = 1e-7;

void solve() {
    vector<vector<double>> matrix(MAXN, vector<double>(MAXN));

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cin >> matrix[i][j];
        }
    }

    auto SWAP = [&](int a, int b) -> void {
        auto temp = matrix[a];
        matrix[a] = matrix[b];
        matrix[b] = temp;
    };

    auto gauss = [&]() -> int {
        for (int i = 1; i <= n; i++) {
            int mx = i;
            for (int j = i + 1; j <= n; j++) {
                if (abs(matrix[j][i]) > abs(matrix[mx][i])) {
                    mx = j;
                }
            }
            SWAP(i, mx);
            if (abs(matrix[i][i]) < diff) {
                return 0;
            }
            double temp = matrix[i][i];
            for (int j = i; j <= n + 1; j++) {
                matrix[i][j] /= temp;
            }
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    double rate = matrix[j][i] / matrix[i][i];
                    for (int k = i; k <= n + 1; k++) {
                        matrix[j][k] -= matrix[i][k] * rate;
                    }
                }
            }
        }
        return 1;
    };

    int sign = gauss();

    if (sign == 0) {
        cout << "No Solution" << '\n';
    } else {
        for (int i = 1; i <= n; i++) {
            cout << fixed << setprecision(2) << matrix[i][n + 1] << '\n';
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