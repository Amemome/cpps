#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

int main() {
    int q; cin >> q;
    vector<pair<ll, ll> > res;
    while(q--) {
        res.clear();
        res.resize(0);
        ll n,x,y;
        cin >> n >> x >> y;
        ll ny = n * y;
        ll a = ny / (x+y);
        ll a1 = a+1;
        ll la1 = ny % (x+y);
        ll la = x+y-la1;
        res.push_back({a, la});
        if(la1 != 0) {
            res.push_back({a1, la1});
        }
        cout << res.size() << '\n';
        for(auto x : res) cout << x.first << ' ' << x.second << '\n';
    }
    
}