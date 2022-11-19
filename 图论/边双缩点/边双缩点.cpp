// 边双缩点
namespace tarjan{
    constexpr int maxn = 5e5 + 100;
    constexpr int maxm = 4e6 + 100;
    
    struct edge{
        int v, nxt, is_bridge;
    };
    // e - 存边, ans - 缩点后的新标号对应的原点双内节点
    edge e[maxm];
    vector<int> ans[maxn];
    // 模拟stack
    vector<int> stk;
    // cnt - 边的计数器, n - 节点数量, idx - dfs序计数器, dcc - 边双缩点形成新点计数器
    // dfn - dfn序, low - 当前节点能够到达的dfs序最小的点
    int cnt = 1, n, idx, dcc, low[maxn], dfn[maxn], col[maxn], head[maxn];

    void add(int u, int v, bool bidirectional = true){
        e[++cnt] = {v, head[u], 0};
        head[u] = cnt;
        if(bidirectional){
            e[++cnt] = {u, head[v], 0};
            head[v] = cnt;
        }
    }

    // 将所有桥标记出来
    void tarjan(int u, int fa){
        stk.push_back(u);
        low[u] = dfn[u] = ++idx;
        for(int i = head[u]; i; i = e[i].nxt){
            auto [v, nxt, _br] = e[i];
            if(!dfn[v]){
                tarjan(v, i);
                cmin(low[u], low[v]);
                // 若不存在重边, 则可以改成 >=
                if(low[v] > dfn[u]){
                    e[i].is_bridge = e[i ^ 1].is_bridge = 1;
                }
            }
            // 不为当前边(的反向边)
            else if(i != (fa ^ 1)) cmin(low[u], dfn[v]);
        }
    }

    // dfs时不经过桥
    void dfs(int u){
        col[u] = dcc;
        ans[dcc].push_back(u);
        for(int i = head[u]; i; i = e[i].nxt){
            auto [v, nxt, br] = e[i];
            if(br) continue;
            if(col[v]) continue;
            dfs(v);
        }
    }

    // 对所有点进行边双缩点
    void e_dcc(){
        // 标记桥
        for(int i = 1; i <= n; i++){
            if(!dfn[i]){
                stk.clear(); tarjan(i, 0);
            }
        }
        // 缩点
        for(int i = 1; i <= n; i++){
            if(!col[i]) ++dcc, dfs(i);
        }
    }
}