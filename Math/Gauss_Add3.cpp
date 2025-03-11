#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P4035
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int diff = 1e-7;

void solve() {
    int n;
    cin >> n;

    vector<vector<double>> matrix(n + 5, vector<double>(n + 5)), data(n + 5, vector<double>(n + 5));

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> data[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            matrix[i][j] = 2 * (data[i][j] - data[i + 1][j]);
            matrix[i][n + 1] += data[i][j] * data[i][j] - data[i + 1][j] * data[i + 1][j];
        }
    }

    auto SWAP = [&](int a, int b) -> void {
        auto temp = matrix[a];
        matrix[a] = matrix[b];
        matrix[b] = temp;
    };

    auto gauss = [&]() -> void {
        for (int i = 1; i <= n; i++) {
            int mx = i;
            for (int j = 1; j <= n; j++) {
                if (j < i && abs(matrix[j][j]) >= diff) {
                    continue;
                }
                if (abs(matrix[j][i]) > abs(matrix[mx][i])) {
                    mx = j;
                }
            }
            SWAP(i, mx);
            if (abs(matrix[i][i]) >= diff) {
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
        }
    };

    gauss();

    for (int i = 1; i <= n; i++) {
        cout << fixed << setprecision(3) << matrix[i][n + 1] << ' ';
    }
    cout << '\n';
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