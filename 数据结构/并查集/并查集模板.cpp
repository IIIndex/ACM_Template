namespace DSU {

vector fa(0, 0);

void init(int n) {
    fa = vector(n + 1, 0);
    iota(all(fa), 0);
}

int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

int merge(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return 0;
    fa[u] = v;
    return 1;
}

}