auto dfs = [&](auto&& self, int u) -> void {
    if (vis[u]) return;
    vis[u] = true;
    for (int v : adj[u]) {
        self(self, v); // 자기 자신을 첫 번째 인자로 넘김
    }
};