// 树边
vector<int> e[maxn];
// in[u] - 进入u的dfs序（u的dfs序），out[u] - 离开u的dfs序
// siz[u] - 以u为根的子树大小，head[u] - u所在树链的链头
// son[u] - u的重儿子，若为0代表u没有重儿子，f[u] - u的父亲
int in[maxn], out[maxn], siz[maxn], head[maxn], son[maxn], f[maxn];
// dfs序计数器
int cnt;
// 预处理重儿子
void dfs1(int u, int fa){
    siz[u] = 1; f[u] = fa;
    for(auto v: e[u]){
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}
// 进行重链剖分
void dfs2(int u, int fa){
    in[u] = ++cnt;
    if(son[u]){
        head[son[u]] = head[u];
        dfs2(son[u], u);
    }
    for(auto v: e[u]){
        if(v == fa || v == son[u]) continue;
        head[v] = v;
        dfs2(v, u);
    }
    out[u] = cnt;
}

// 调用顺序为dfs1(root, -1); dfs2(root, -1);