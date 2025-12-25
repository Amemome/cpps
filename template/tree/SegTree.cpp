
template <typename T>
struct SegTree {
    int n;          // 리프 노드의 개수 (2의 거듭제곱)
    vector<T> tree;
    T identity;     // 항등원 (덧셈:0, 곱셈:1, Min:INF, Max:-INF)

    T merge(T a, T b) {
        return a + b;
    }

    SegTree(int size, T id = 0) {
        identity = id;
        n = 1;
        while (n < size) n *= 2;
        tree.assign(n * 2, identity); // 초기화
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