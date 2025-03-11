#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
      
const int LIMIT = 100000;
// dp[i] : 当前所有硬币无限制的情况下 花掉 i 元 方法数是多少
int dp[LIMIT + 1];
// 面值多少
int value[4];
// 数量多少
int cnt[4];
int n, s;

void build(){
    dp[0] = 1;
    for(int i = 0; i < 4; i++){
        for(int j = value[i]; j <= LIMIT; j++){
            dp[j] += dp[j - value[i]];
        }
    }
}

int query(){
    int illegal = 0;
    for(int status = 1; status <= 15; status++){
        int t = s;
        int sign = -1;
        for(int j = 0; j < 4; j++){
            if(((status >> j) & 1) == 1){
                t -= value[j] * (cnt[j] + 1);
                sign = -sign;
            }
        }
        if(t >= 0){
            illegal += dp[t] * sign;
        }
    }
    return dp[s] - illegal;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    cin >> value[0] >> value[1] >> value[2] >> value[3] >> n;
    build();
    for(int i = 0; i < n; i++){
        cin >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3] >> s;
        cout << query() << "\n";
    }

      
    return 0;
}