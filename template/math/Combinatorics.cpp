#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;
const int MAX_N = 200'005;

ll fact[MAX_N];
ll invFact[MAX_N];

// 1. 거듭제곱 - O(log exp)
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// 2. 모듈러 역원 페르마의 소정리 이용
// MOD가 소수일 때만 성립: a^(MOD-2) mod MOD
ll modInverse(ll n) {
    return power(n, MOD - 2);
}

// 3. 전처리 - O(N) 팩토리얼과 역원 팩토리얼을 미리 계산
void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    } // 가장 끝 값의 역원을 구하고 역방향으로 채움
    invFact[MAX_N - 1] = modInverse(fact[MAX_N - 1]);
    for (int i = MAX_N - 2; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

// 4. nCr
ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

// 5. nPr
ll nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[n - r] % MOD;
}

// 6. nHr 중복조합
// nHr = (n+r-1)Cr
ll nHr(int n, int r) {
    if (n == 0 && r == 0) return 1; // 예외처리
    return nCr(n + r - 1, r);
}
