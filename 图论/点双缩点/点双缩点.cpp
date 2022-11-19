// 点双缩点
namespace tarjan{
    constexpr int maxn = 5e5 + 100;
    // e - 存边, ans - 缩点后的新标号对应的原点双内节点
    vector<int> e[maxn], ans[maxn];
    // 模拟stack
    vector<int> stk;
    // n - 节点数量, idx - dfs序计数器, bcc - 点双缩点形成新点计数器
    // dfn - dfn序, low - 当前节点能够到达的dfs序最小的点
    int n, idx, bcc, low[maxn], dfn[maxn];

    void tarjan(int u, int fa){
        stk.push_back(u);
        low[u] = dfn[u] = ++idx;
        // 判断是不是孤立点
        int son = 0;
        for(auto v: e[u]){
            if(!dfn[v]){
                son++;
                tarjan(v, u);
                cmin(low[u], low[v]);
                // u的以v为根的这颗子树无法抵达比u的dfn序更小的点, u为一个割点
                if(low[v] >= dfn[u]){
                    bcc++;
                    // 将v及其子树全部弹出
                    while(stk.back() != v){
                        ans[bcc].push_back(stk.back());
                        stk.pop_back();
                    }
                    ans[bcc].push_back(stk.back()); stk.pop_back();
                    // u也处于这个点双连通分量内
                    ans[bcc].push_back(u);
                }
            }
            // 前向边
            else if(v != fa) cmin(low[u], dfn[v]);
        }
        // u是孤立点
        if(fa == 0 && son == 0) ans[++bcc].push_back(u);
    }

    // 对所有点进行点双缩点
    void v_dcc(){
        for(int i = 1; i <= n; i++){
            if(!dfn[i]){
                stk.clear();
                tarjan(i, 0);
            }
        }
    }

    void clear(){
        idx = bcc = 0; stk.clear();
        for(int i = 1; i <= n; i++){
            e[i].clear(); ans[i].clear();
            low[i] = dfn[i] = 0;
        }
    }
}