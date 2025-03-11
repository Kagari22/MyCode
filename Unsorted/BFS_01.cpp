#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
      

int mincost(vector<vector<int>>& grid) {
    vector<vector<int>> move = {{}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> distance(n, vector<int>(m, numeric_limits<int>::max()));
    deque<pair<int, int>> q;
    q.push_front({0, 0});
    distance[0][0] = 0;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();
        
        if (x == n - 1 && y == m - 1) {
            return distance[x][y];
        }
        
        for (int i = 1; i <= 4; i++) {
            int nx = x + move[i][0];
            int ny = y + move[i][1];
            int w = grid[x][y] != i ? 1 : 0;
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && distance[x][y] + w < distance[nx][ny]) {
                distance[nx][ny] = distance[x][y] + w;
                if (w == 0) {
                    q.push_front({nx, ny});
                } else {
                    q.push_back({nx, ny});
                }
            }
        }
    }
    
    return -1;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        
    vector<vector<int>> grid = {{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}};
    cout << mincost(grid) << endl;
      
    return 0;
}