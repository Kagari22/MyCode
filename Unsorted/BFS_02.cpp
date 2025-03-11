#include <bits/stdc++.h>

#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

int n, k;
int visited[1000][1000];

struct node{
    int x, y, steps, magic;
};

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void solve(){
    cin >> n >> k;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    
    memset(visited, -1, sizeof(visited));
    queue<node> q;
    visited[0][0] = 0;
    q.push({0, 0, 0, 0}); 
    
    while(!q.empty()){
        node cur = q.front();
        q.pop();
        
        if(cur.x == n - 1 && cur.y == n - 1){
            cout << cur.steps << "\n";
            return;
        }
        
        for(int i = 0; i < 4; i++){
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) {
                continue;  
            }
            
            if(a[nx][ny] == 'X' && cur.magic == 0){
                continue;  
            }
            
            int magic = max(0LL, cur.magic - 1);  
            if(a[nx][ny] == '%'){
                magic = k;  
            }
            
            if(visited[nx][ny] < magic && a[nx][ny] != '#'){
                visited[nx][ny] = magic;
                q.push({nx, ny, cur.steps + 1, magic});
            }
        }
    }
    
    cout << -1 << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    
    return 0;
}
