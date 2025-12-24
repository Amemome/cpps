#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

vector<int> G[10'001];
vector<int> GT[10'001];
int cnt = 0;
char vis[10'001];
stack<int> endT; 

void dfs1(int x) {
	vis[x] = true;
	for(auto i : G[x]) {
		if(vis[i]) continue;
		dfs1(i);
	}
	endT.push(x);
}

void dfs2(int x, vector<int>& res) {
	vis[x] = true;
	res.push_back(x);
	for(auto i : GT[x]) {
		if(vis[i]) continue;
		dfs2(i, res);
	}
}	

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int v,e;
	cin >>v >> e;
	while(e--) {
		int u,v;
		cin >> u >> v;
		G[u].push_back(v);
		GT[v].push_back(u);
	}
	memset(vis, 0x00, sizeof(vis));
	for(int i = 1; i <= v; i++) if(!vis[i]) dfs1(i);
	memset(vis, 0x00, sizeof(vis));

	vector<vector<int>> res;
	
	while(!endT.empty()) {
		int x = endT.top(); endT.pop();
		if(vis[x]) continue;

		vector<int> tmp;
		dfs2(x, tmp);
		res.push_back(tmp);
	}

	cout << res.size() << endl;

	for(auto & x : res) sort(x.begin(), x.end());

	sort(res.begin(), res.end());
	for(auto x : res) {
		for(auto y : x) cout << y << ' ';
		cout << "-1\n";
	}
	return 0;
}
