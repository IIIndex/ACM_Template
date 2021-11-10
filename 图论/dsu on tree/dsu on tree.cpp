const int maxn = 1e5 + 100;

vector<int> e[maxn];
int siz[maxn], L[maxn], R[maxn], son[maxn], no[maxn], ans[maxn];

void dfs(int now,int f){
    siz[now] = 1;                               //初始化size
    L[now] = ++cnt, no[cnt] = now;              //记录以now为根的子树dfs序的左端点和dfs序对应的点序号
    for(auto v: e[now]){
        if(v != f){
            dfs(v, now);
            siz[now] += siz[v];
            if(siz[v] > siz[son[now]]) son[now] = v;        //挑选重儿子
        }
    }
    R[now] = cnt;                               //记录以now为根的子树dfs序的右端点
}


void dsu(int u, int keep){
    if(!u) return;
    for(auto v: e[u]){
        if(v != fa[u][0] && v != son[u])
            dsu(v, 0);                          //先遍历轻儿子并不保存
    }
    dsu(son[u], 1);                             //遍历重儿子并保存
    b.update(T[u], 1);                          //将该节点的影响加入
    for(auto v: e[u]){
        if(v != fa[u][0] && v != son[u]){
            for(int i = L[v]; i <= R[v]; i++){
                b.update(T[no[i]], 1);          //将轻儿子的影响重新加入
            }
        }
    }
    for(auto i: Q[u]){                          //处理该点的答案
        int no = get<0>(i), l = get<1>(i), r = get<2>(i);
        ans[no] = b.query(r) - b.query(l - 1);
    }
    if(!keep){                                  //如果不保存，则根据dfs序清空此树的所有影响
        for(int i = L[u]; i <= R[u]; i++){
            b.update(T[no[i]], -1);
        }
    }
}