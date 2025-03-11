#include <bits/stdc++.h>

#define MAXN 500001
#define INF LLONG_MIN

using namespace std;

long long arr[MAXN];
long long sum[MAXN << 2];
long long maxVal[MAXN << 2];
int cnt[MAXN << 2];
long long sem[MAXN << 2];
long long maxAdd[MAXN << 2];
long long otherAdd[MAXN << 2];
long long maxHistory[MAXN << 2];
long long maxAddTop[MAXN << 2];
long long otherAddTop[MAXN << 2];

void up(int i) {
    int l = i << 1, r = i << 1 | 1;
    maxHistory[i] = max(maxHistory[l], maxHistory[r]);
    sum[i] = sum[l] + sum[r];
    maxVal[i] = max(maxVal[l], maxVal[r]);
    if (maxVal[l] > maxVal[r]) {
        cnt[i] = cnt[l];
        sem[i] = max(sem[l], maxVal[r]);
    } else if (maxVal[l] < maxVal[r]) {
        cnt[i] = cnt[r];
        sem[i] = max(maxVal[l], sem[r]);
    } else {
        cnt[i] = cnt[l] + cnt[r];
        sem[i] = max(sem[l], sem[r]);
    }
}

void lazy(int i, int n, long long maxAddv, long long otherAddv, long long maxUpv, long long otherUpv) {
    maxHistory[i] = max(maxHistory[i], maxVal[i] + maxUpv);
    maxAddTop[i] = max(maxAddTop[i], maxAdd[i] + maxUpv);
    otherAddTop[i] = max(otherAddTop[i], otherAdd[i] + otherUpv);
    sum[i] += maxAddv * cnt[i] + otherAddv * (n - cnt[i]);
    maxVal[i] += maxAddv;
    if (sem[i] != INF) sem[i] += otherAddv;
    maxAdd[i] += maxAddv;
    otherAdd[i] += otherAddv;
}

void down(int i, int ln, int rn) {
    int l = i << 1, r = i << 1 | 1;
    long long tmp = max(maxVal[l], maxVal[r]);
    if (maxVal[l] == tmp) lazy(l, ln, maxAdd[i], otherAdd[i], maxAddTop[i], otherAddTop[i]);
    else lazy(l, ln, otherAdd[i], otherAdd[i], otherAddTop[i], otherAddTop[i]);
    
    if (maxVal[r] == tmp) lazy(r, rn, maxAdd[i], otherAdd[i], maxAddTop[i], otherAddTop[i]);
    else lazy(r, rn, otherAdd[i], otherAdd[i], otherAddTop[i], otherAddTop[i]);
    
    maxAdd[i] = otherAdd[i] = maxAddTop[i] = otherAddTop[i] = 0;
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = maxVal[i] = maxHistory[i] = arr[l];
        sem[i] = INF;
        cnt[i] = 1;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    maxAdd[i] = otherAdd[i] = maxAddTop[i] = otherAddTop[i] = 0;
}

void add(int jobl, int jobr, long long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, r - l + 1, jobv, jobv, jobv, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) add(jobl, jobr, jobv, l, mid, i << 1);
        if (jobr > mid) add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void setMin(int jobl, int jobr, long long jobv, int l, int r, int i) {
    if (jobv >= maxVal[i]) return;
    if (jobl <= l && r <= jobr && sem[i] < jobv) {
        lazy(i, r - l + 1, jobv - maxVal[i], 0, jobv - maxVal[i], 0);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) setMin(jobl, jobr, jobv, l, mid, i << 1);
        if (jobr > mid) setMin(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        up(i);
    }
}

long long querySum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) return sum[i];
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long long ans = 0;
    if (jobl <= mid) ans += querySum(jobl, jobr, l, mid, i << 1);
    if (jobr > mid) ans += querySum(jobl, jobr, mid + 1, r, i << 1 | 1);
    return ans;
}

long long queryMax(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) return maxVal[i];
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long long ans = INF;
    if (jobl <= mid) ans = max(ans, queryMax(jobl, jobr, l, mid, i << 1));
    if (jobr > mid) ans = max(ans, queryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
    return ans;
}

long long queryHistoryMax(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) return maxHistory[i];
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long long ans = INF;
    if (jobl <= mid) ans = max(ans, queryHistoryMax(jobl, jobr, l, mid, i << 1));
    if (jobr > mid) ans = max(ans, queryHistoryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(1, n, 1);

    for (int i = 0; i < m; ++i) {
        int op, jobl, jobr;
        long long jobv;
        cin >> op >> jobl >> jobr;
        if (op == 1) {
            cin >> jobv;
            add(jobl, jobr, jobv, 1, n, 1);
        } else if (op == 2) {
            cin >> jobv;
            setMin(jobl, jobr, jobv, 1, n, 1);
        } else if (op == 3) {
            cout << querySum(jobl, jobr, 1, n, 1) << '\n';
        } else if (op == 4) {
            cout << queryMax(jobl, jobr, 1, n, 1) << '\n';
        } else if (op == 5) {
            cout << queryHistoryMax(jobl, jobr, 1, n, 1) << '\n';
        }
    }
    
    return 0;
}
