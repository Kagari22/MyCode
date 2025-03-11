#include<bits/stdc++.h>

//树状数组模版4 二维数组范围增加 + 范围查询
//https://leetcode.cn/problems/O4NDxx/
using namespace std;

class NumMatrix {
public:
    vector<vector<int>> tree;
    vector<vector<int>> nums;
    int n, m;

    NumMatrix(vector<vector<int>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();
        tree = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));
        nums = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                update(i, j, matrix[i][j]);
            }
        }
    }

    int lowbit(int i) {
        return i & -i;
    }

    void add(int x, int y, int v) {
        for(int i = x; i <= n; i += lowbit(i)) {
            for(int j = y; j <= m; j += lowbit(j)) {
                tree[i][j] += v;
            }
        }
    }
    
    int sum(int x, int y) {
        int ans = 0;
        for(int i = x; i > 0; i -= lowbit(i)) {
            for(int j = y; j > 0; j -= lowbit(j)) {
                ans += tree[i][j];
            }
        }
        return ans;
    }

    void update(int x, int y, int v) {
        add(x + 1, y + 1, v - nums[x + 1][y + 1]);
        nums[x + 1][y + 1] = v;
    }

    int sumRegion(int a, int b, int c, int d) {
        return sum(c + 1, d + 1) - sum(a, d + 1) - sum(c + 1, b) + sum(a, b);
    }
};

int main() {
    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };
    
    NumMatrix numMatrix(matrix);
    
    cout << "Sum of region (2, 1, 4, 3): " << numMatrix.sumRegion(2, 1, 4, 3) << endl;  // Output: 8
    cout << "Sum of region (1, 1, 2, 2): " << numMatrix.sumRegion(1, 1, 2, 2) << endl;  // Output: 11
    cout << "Sum of region (1, 2, 2, 4): " << numMatrix.sumRegion(1, 2, 2, 4) << endl;  // Output: 12
    
    numMatrix.update(3, 2, 2);
    cout << "Sum of region (2, 1, 4, 3) after update: " << numMatrix.sumRegion(2, 1, 4, 3) << endl;  // Output: 10
    
    return 0;
}
