#include <bits/stdc++.h>

// 并查集
// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
      
const int MAXN = 1000001;
vector<int> father(MAXN);
vector<int> siz(MAXN);
vector<int> stk(MAXN);
int n;

/*Solution() {
    father.resize(MAXN); 
    sizee.resize(MAXN);
    stk.resize(MAXN);
}*/

void build(int n){
    for(int i = 0; i <= n; i++){
        father[i] = i;
        siz[i] = 1;
    }
}

int find(int i) {
    if (father[i] != i) {
        father[i] = find(father[i]);
    }
    return father[i];
}

int find(int i){
    int s = 0;
    while(i != father[i]){
        stk[s++] = i;
        i = father[i];
    }
    while(s > 0){
        father[stk[--s]] = i;
    }
    return i;
}

bool isSameSet(int x, int y){
    return find(x) == find(y);
}

void merge(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx != fy){
        if(siz[fx] >= siz[fy]){
            siz[fx] += siz[fy];
            father[fy] = fx;
        }else{
            siz[fy] += siz[fx];
            father[fx] = fy;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
      
    cin >> n;
    build();
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        int op, x, y;
        // 查询节点 x 和节点 y 之间是否链接 
        // 如果链接就 union(x, y)
        cin >> op >> x >> y;
        if(op == 1){
            if(isSameSet(x, y)){
                cout << "Yes\n";
            }else{
                cout << "No\n";
            }
        }else{
            merge(x, y);
        }
    }
      
    return 0;
}