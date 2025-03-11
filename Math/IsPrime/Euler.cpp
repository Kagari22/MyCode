#include <bits/stdc++.h>

#define ll long long
using namespace std;
      
int euler(int n){
    vector<bool> visited(n + 1);
    vector<int> prime(n / 2 + 1);
    int cnt = 0;
    for(int i = 2; i <= n; i++){
        if(!visited[i]){
            prime[cnt++] = i;
        }
        for(int j = 0; j < cnt; j++){
            if(i * prime[j] > n){
                break;
            }
            visited[i * prime[j]] = true;
            if(i % prime[j] == 0){
                break;
            }
        }
    }
    return cnt;
}

int countPrimes(int n){
    return euler(n - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    int n;
    cin >> n;
    cout << countPrimes(n) << endl;
      
    return 0;
}