#include <bits/stdc++.h>
using namespace std;

struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> sz, dep, par, top, in;
    int pv; // 방문순서카운터
    HLD(int _n) : n(_n), adj(_n), sz(_n), dep(_n), par(_n), top(_n), in(_n) {
        pv = 0;
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // 서브트리 크기, 깊이 계산 & Heavy Edge를 맨 앞으로(swap)
    void dfs1(int u, int p) {
        sz[u] = 1; 
        dep[u] = (p == -1 ? 0 : dep[p] + 1);
        par[u] = p;

        for(auto & v : adj[u]) {
            if (v == p) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if (adj[u][0] == p || sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
        }
    }

    void dfs2(int u) {
        in[u] = pv++; // 방문 순서대로 매겨주기 
        for(auto v : adj[u]) {
            if (v == par[u]) continue;
            if (v == adj[u][0]) top[v] = top[u]; // 부모체인 받기
            else top[v] = v; // 자기가 새로운체인
            dfs2(v);
        }
    }

    void build(int root = 0) {
        dfs1(root, -1); 
        top[root] = root;
        dfs2(root);
    }

    int query_path(int u, int v, SegTree<int> & seg) {
        int ret = 0;
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            int start = top[u];
            ret = seg.merge(ret, seg.query(in[start], in[u]));
            u = par[start]; // 체인 갈아탐
        }
        if (dep[u] > dep[v]) swap(u, v);
        ret = seg.merge(ret, seg.query(in[u]+1, in[v]));
        return ret;
    }

    int get_lca(int u, int v) {
        while(top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = par[top[u]];
        } return (dep[u] < dep[v]) ? u : v;
    }
};

template <typename T>
struct SegTree {
    int n;          // 리프 노드의 개수 (2의 거듭제곱)
    vector<T> tree;
    T identity;     // 항등원 (덧셈:0, 곱셈:1, Min:INF, Max:-INF)

    T merge(T a, T b) {
        return std::max(a,b);
    }

    SegTree(int size, const vector<T>& data, T id = 0) {
        identity = id;
        n = 1;
        while (n < size) n *= 2;
        tree.assign(n * 2, identity); // 초기화

        for(int i = 0; i < data.size(); i++) {
            if(i < size) tree[n+i] = data[i];
        }
        for(int i = n-1; i >= 1; i--) {
            tree[i] = merge(tree[2*i], tree[2*i+1]);
        }
    }

    // idx번째(0-based) 값을 val로 변경
    void update(int idx, T val) {
        int i = n + idx;    // 리프 노드 인덱스
        tree[i] = val;      // 값 덮어쓰기 (문제에 따라 += 일 수도 있음)
        
        // 루트까지 올라가며 갱신
        for (i /= 2; i >= 1; i /= 2) {
            tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // 구간 [l, r] (0-based, inclusive)의 결과 반환
    T query(int l, int r) {
        l += n;
        r += n;
        T res_l = identity;
        T res_r = identity;

        while (l <= r) {
            if (l % 2 == 1) res_l = merge(res_l, tree[l++]); // 왼쪽에서 닫힘
            if (r % 2 == 0) res_r = merge(tree[r--], res_r); // 오른쪽에서 닫힘
            l /= 2;
            r /= 2;
        }
        return merge(res_l, res_r);
    }

    void debug() {
        for(int i=1; i<2*n; i++) cout << tree[i] << " ";
        cout << "\n";
    }
};