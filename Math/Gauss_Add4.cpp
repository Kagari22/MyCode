#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P5027
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int diff = 1e-7;

void solve() {
    int n;
    cin >> n;

    vector<vector<double>> matrix(n + 5, vector<double>(n + 5));
    vector<vector<int>> data(n + 5, vector<int>(n + 5));

    for (int i = 1; i <= n + 1; i++) {
        int m;
        cin >> m;
        for (int j = 1; j <= m; j++) {
            int cur;
            cin >> cur;
            data[i][cur] = 1;
        }
        cin >> data[i][n + 1];
    }

    int ans = 0;
    int times = 0;

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

    auto swapData = [&](int i, int j) -> void {
        auto temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    };

    auto check = [&]() -> int {
        gauss();
        double maxv = -INF;
        int maxt = 0, ans = 0;

        for (int i = 1; i <= n; i++) {
            if (matrix[i][i] == 0) {
                return 0;
            }
            if (matrix[i][n + 1] <= 0 || matrix[i][n + 1] != (int) matrix[i][n + 1]) {
                return 0;
            }
            if (maxv < matrix[i][n + 1]) {
                maxv = matrix[i][n + 1];
                maxt = 1;
                ans = i;
            } else if (maxv == matrix[i][n + 1]) {
                maxt++;
            }
        }

        if (maxt > 1) {
            return 0;
        }

        return ans;
    };

    for (int k = 1; k <= n + 1; k++) {
        swapData(k, n + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n + 1; j++) {
                matrix[i][j] = data[i][j];
            }
        }
        swapData(k, n + 1);
        int cur = check();
        if (cur != 0) {
            times++;
            ans = cur;
        }
    }

    if (times != 1) {
        cout << "illegal\n";
    } else {
        cout << ans << '\n';
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