namespace LCA {
    int n;
    vector f(0, vector(0, 0)), e = f;
    vector dep(0, 0), fa = dep;

    void dfs(int u, int f) {
        fa[u] = f;
        dep[u] = dep[f] + 1;

        for (auto v: e[u]) {
            if (v == f) continue;
            dfs(v, u);
        }
    }

    int lim = 0;
    void init(int n, int rt, vector<vector<int>>& _e) {
        e = move(_e);
        lim = __lg(n) + 1;
        f.assign(lim, vector(n + 1, 0));
        dep = fa = vector(n + 1, 0);

        dfs(rt, 0);

        // 初始化倍增表
        for (int i = 1; i <= n; i++) f[0][i] = fa[i];
        for (int i = 1; i < lim; i++) for (int j = 1; j <= n; j++)
            f[i][j] = f[i - 1][f[i - 1][j]];
    }

    int lca(int u, int v) {
        if (dep[v] > dep[u]) swap(u, v);
        
        // u v 平齐
        for (int i = lim - 1; i >= 0; i--) if (dep[u] - (1 << i) >= dep[v])
            u = f[i][u];
        
        if (u == v) return u;

        // 跳到LCA下方第一个位置
        for (int i = lim - 1; i >= 0; i--) if (f[i][u] != f[i][v]) {
            u = f[i][u]; v = f[i][v];
        }

        return f[0][u];
    }
}