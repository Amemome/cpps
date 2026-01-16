// DSU . Last Update : 26.01.15
struct UnionFind {
    vector<int> parent, sz;

    // 생성자: n개 노드 초기화 (1-based 인덱스 대응을 위해 n+1 크기 할당)
    UnionFind(int n) : parent(n + 1), sz(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0); // 0~n으로 초기화
    }

    // Find: 경로 압축 (Path Compression)
    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }

    // Union: 사이즈 기반 합치기 (Union by Size)
    // u와 v가 이미 같은 집합이면 false, 합쳤으면 true 반환
    bool merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false; // 이미 연결됨
        
        // 더 큰 트리에 작은 트리를 붙임 (Depth 최소화)
        if (sz[u] < sz[v]) swap(u, v);
        parent[v] = u;
        sz[u] += sz[v];
        return true;
    }

    // 두 노드가 연결되어 있는지 확인
    bool connected(int u, int v) {
        return find(u) == find(v);
    }
    
    // 특정 노드가 속한 집합의 크기 반환
    int size(int x) {
        return sz[find(x)];
    }
};

int main() {
    int N = 5;
    UnionFind uf(N); // 0~5번 노드 생성

    uf.merge(1, 2);  // 1과 2 연결
    uf.merge(3, 4);  // 3과 4 연결
    
    // 연결 확인
    if (uf.connected(1, 2)) {
        // ...
    }

    // merge의 리턴값을 이용한 사이클 판별 (크루스칼 알고리즘 등에서 사용)
    if (!uf.merge(1, 2)) {
        cout << "이미 연결되어 있음 (사이클 발생)" << endl;
    }

    uf.merge(2, 3); // {1, 2} 와 {3, 4} 병합 -> {1, 2, 3, 4}

    // 집합의 크기 확인
    cout << uf.size(1); // 출력: 4 (1,2,3,4가 한 집합이므로)
}