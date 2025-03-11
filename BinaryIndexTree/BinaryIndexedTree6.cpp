#include <bits/stdc++.h>
#include <cstdio>

//https://www.luogu.com.cn/problem/P1908    
//逆序对 归并分治做法
using namespace std;

#define MAXN 500001

vector<int> arr(MAXN, 0);
vector<int> help(MAXN, 0);
/*int arr[MAXN];
int help[MAXN];*/
int n;

long long merge(int l, int m, int r){
    long long ans = 0;
    for(int i = m, j = r; i >= l; i--){
        while(j >= m + 1 && arr[i] <= arr[j]){
            j--;
        }
        ans += j - m;
    }
    int i = l;
    int a = l;
    int b = m + 1;
    while(a <= m && b <= r){
        help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
    }
    while(a <= m){
        help[i++] = arr[a++];
    }
    while(b <= r){
        help[i++] = arr[b++];
    }
    for(i = l; i <= r; i++){
        arr[i] = help[i];
    }
    return ans;
}

long long f(int l, int r){
    if(l >= r){
        return 0;
    }
    int m = (l + r) / 2;
    return f(l, m) + f(m + 1, r) + merge(l, m, r);
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }

    cout << f(1, n) << endl;

    return 0;
}
