#include <bits/stdc++.h>

// 打印所有质因子
#define ll long long
using namespace std;
      
void f(int n){
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            cout << i << "\n";
            while(n % i == 0){
                n /= i;
            }
        }
    }
    if(n > 1){
        cout << n << "\n";
    }
}     

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    ll x;
    cin >> x;
    f(x);
      
    return 0;
}