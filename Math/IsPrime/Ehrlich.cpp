#include <bits/stdc++.h>

// 计算小于 n 的质数的数量
#define ll long long
using namespace std;
      
int ehrlich(int n){
    vector<bool> visited(n + 1);
    for(int i = 2; i * i <= n; i++){
        if(!visited[i]){
            for(int j = i * i; j <= n; j += i){
                visited[j] = true;
            }
        }
    }
    int cnt = 0;
    for(int i = 2; i <= n; i++){
        if(!visited[i]){
            cnt++;
        }
    }
    return cnt;
}

int countPrimes(int n){
    return ehrlich(n - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    int n;
    cin >> n;
    // 小于 n 的质数的数量
    cout << countPrimes(n) << endl;
      
    return 0;
}