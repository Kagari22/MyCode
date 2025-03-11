#include <bits/stdc++.h>

// https://acm.hdu.edu.cn/showproblem.php?pid=5833
// from: cpp.json
#define INF 2e18
#define int long long
using namespace std;

const int MOD = 1e9 + 7;
const int MAXV = 2000;
const int MAXN = 305;

int cnt = 0;

int prime[MAXV + 1];
int pow2[MAXN];

void Calc_Prime() {
    vector<bool> visited(MAXV + 1);

    for (int i = 2; i * i <= MAXV; i++) {
        if (!visited[i]) {
            for (int j = i * i; j <= MAXV; j += i) {
                visited[j] = true;
            }
        }
    }
    
    for (int i = 2; i <= MAXV; i++) {
        if (!visited[i]) {
            prime[++cnt] = i;
        }
    }

    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
}

int T = 0;

void solve() {
    int N;
    cin >> N;

    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    vector<vector<int>> mat(MAXN, vector<int>(MAXN));

    int cur = -1;

    for (int i = 1; i <= N; i++) {
        cur = a[i];
        for (int j = 1; j <= cnt && cur != 0; j++) {
            while (cur % prime[j] == 0) {
                mat[j][i] ^= 1;
                cur /= prime[j];
            }
        } 
    }

    auto SWAP = [&](int i, int j) -> void {
        auto temp = mat[i];
        mat[i] = mat[j];
        mat[j] = temp;
    };

    auto gauss = [&](int n) -> void {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (j < i && mat[j][j] == 1) {
                    continue;
                }
                if (mat[j][i] == 1) {
                    SWAP(i, j);
                    break;
                }
            }
            if (mat[i][i] == 1) {
                for (int j = 1; j <= n; j++) {
                    if (i != j && mat[j][i] == 1) {
                        for (int k = i; k <= n + 1; k++) {
                            mat[j][k] ^= mat[i][k];
                        }
                    }
                }
            }
        }
    };

    gauss(cnt);

    int main = 0;

    for (int i = 1; i <= cnt; i++) {
        if (mat[i][i] == 1) {
            main++;
        }
    }

    cout << "Case #" << T << ":" << '\n';
    cout << pow2[N - main] - 1 << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    Calc_Prime();

    while(t--){
        T++;
        solve();
    }

    return 0;
}