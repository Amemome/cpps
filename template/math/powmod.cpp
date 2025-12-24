typedef long long ll;

ll powmod(ll base, ll exp, ll mod) {
    ll res = 1; base %= mod;
    while(exp > 0) {
        if (exp % 2) res = (res * base) % mod;
        base = (base * base) % mod; exp /= 2;
    } return res;
}