#include <bits/stdc++.h>

// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

// 对顶堆模板开始，注意以下模板维护的其实是前 K 小的元素

struct Magic {
    int K;
    typedef pair<int, int> pii;
    multiset<pii> st1, st2;
    long long sm1;

    Magic(int K): K(K) {
        sm1 = 0;
    }

    // 把第一个堆的大小调整成 K
    void adjust() {
        while (!st2.empty() && st1.size() < K) {
            pii p = *(st2.begin());
            st1.insert(p); sm1 += 1LL * p.first * p.second;
            st2.erase(st2.begin());
        }
        while (st1.size() > K) {
            pii p = *prev(st1.end());
            st2.insert(p);
            st1.erase(prev(st1.end())); sm1 -= 1LL * p.first * p.second;
        }
    }

    // 加入元素 p
    void add(pii p) {
        if (!st2.empty() && p >= *(st2.begin())) st2.insert(p);
        else st1.insert(p), sm1 += 1LL * p.first * p.second;
        adjust();
    }

    // 删除元素 p
    void del(pii p) {
        auto it = st1.find(p);
        if (it != st1.end()) st1.erase(it), sm1 -= 1LL * p.first * p.second;
        else st2.erase(st2.find(p));
        adjust();
    }
};

// 对顶堆模板结束

class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<long long> ans;
        unordered_map<int, int> cnt;
        Magic magic(x);
        for (int i = 0; i < k; i++) cnt[nums[i]]++;
        // 因为模板维护的是前 x 小的元素，所以这里元素全部取反
        for (auto &p : cnt) magic.add({-p.second, -p.first});
        for (int i = 0; ; i++) {
            ans.push_back(magic.sm1);
            if (i + k == n) break;
            // 滑动窗口滑动一格
            magic.del({-cnt[nums[i]], -nums[i]});
            cnt[nums[i]]--;
            if (cnt[nums[i]] > 0) magic.add({-cnt[nums[i]], -nums[i]});
            if (cnt[nums[i + k]] > 0) magic.del({-cnt[nums[i + k]], -nums[i + k]});
            cnt[nums[i + k]]++;
            magic.add({-cnt[nums[i + k]], -nums[i + k]});
        }
        return ans;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums = {1,1,2,2,3,4,2,3};
    int k = 6, x = 2;
    
    // 创建 Solution 类的实例
    Solution sol;

    // 获取返回的结果
    vector<long long> result = sol.findXSum(nums, k, x);

    // 输出结果
    for (long long r : result) {
        cout << r << '\n';
    }

    return 0;
}