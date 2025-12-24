#include <bits/stdc++.h>
using namespace std;

/*
같은 숫자 기준으로 왼쪽 오른쪽 수 집합을 교집합 했을떄 개수 전부 구하기로 치환
uniq 하니까 서로 인덱스를 알 수 있다.
*/

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;
    vector<vector<int>> st(n+1);
    vector<int> indegree(n+1,0);
    queue<int> Q;
    vector<int> result;
    for(int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        st[a].push_back(b);
        indegree[b]++;
    }

    for(int i = 1; i <= n; i++){
        if(!indegree[i]) Q.push(i);
    }

    while(!Q.empty()){
        int cur = Q.front(); Q.pop();
        result.push_back(cur);
        for(auto x : st[cur]){
            indegree[x]--;
            if(!indegree[x]) Q.push(x);
        }
    }

    for(auto x : result) cout << x << " ";

    return 0;
}