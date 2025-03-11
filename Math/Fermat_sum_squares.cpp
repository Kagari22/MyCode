#include <bits/stdc++.h>

// 费马平方和 : 当且仅当一个自然数的质因数分解中，满足 4k+3 形式的质数次方数均为偶数时，该自然数才能被表示为两个平方数之和
// from: cpp.json
#define int long long
#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

bool judgeSquareSum(int c) {
    for(int base = 2; base * base <= c; base++) {
        if (c % base != 0) {
            continue;
        }
        // 确保 base 是质数
        if (!isPrime(base)) {
            continue;
        }

        int exp = 0;
        while (c % base == 0) {
            c /= base;
            exp++;
        }
        if (base % 4 == 3 && exp % 2 != 0) {
            return false;
        }
    }
    return c % 4 != 3;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cout << judgeSquareSum(n) << endl;

    return 0;
}