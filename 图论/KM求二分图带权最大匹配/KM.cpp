const ll INF = 1e18 + 7;
const int maxn = 5e2 + 100;

int n, m;
ll e[maxn][maxn];
//lx, ly分别为左右点的顶标，lx[u] + ly[v] >= e[u][v]
//slack[i]表示指向右部点i的所有点, min(lx[u] + ly[i] - e[u][i])的值，即松弛量
ll lx[maxn], ly[maxn], slack[maxn];
//px, py分别为左右部点匹配
int px[maxn], py[maxn], pre[maxn];
//vx, vy分别为左右点遍历标记
bool vx[maxn], vy[maxn];

queue<int> q;

//循环更新匹配边
void aug(int v){
    int t;
    while(v){
        t = px[pre[v]];
        px[pre[v]] = v;
        py[v] = pre[v];
        v = t;
    }
}

void bfs(int s){
    memset(vx, 0, sizeof(vx));
    memset(vy, 0, sizeof(vy));
    memset(pre, 0, sizeof(pre));
    //初始化松弛量
    fill(slack + 1, slack + n + 1, INF);
    // cout << s << endl;

    while(!q.empty()) q.pop();
    q.push(s);

    while(1){
        while(!q.empty()){
            // if(s == 498) cerr << q.size() << endl;
            int u = q.front(); q.pop();
            vx[u] = true;
            for(int i = 1; i <= n; i++){
                if(!vy[i] && e[u]){
                    if(lx[u] + ly[i] - e[u][i] < slack[i]){
                        //lx[u] + ly[i] = e[u][i]的边称为相等边
                        slack[i] = lx[u] + ly[i] - e[u][i];
                        pre[i] = u;
                        //找到了增广边
                        if(!slack[i]){
                            vy[i] = true;
                            if(!py[i]) {aug(i); return;}
                            q.push(py[i]);
                        }
                    }
                }
            }
        }

        ll d = INF;
        for(int i = 1; i <= n; i++)
            if(!vy[i]) d = min(d, slack[i]);    //找到和slack差距最小的地方
        for(int i = 1; i <= n; i++){
            //根据点是否被访问过决定是否修改顶标
            if(vx[i]) lx[i] -= d;
            if(vy[i]) ly[i] += d;
            else slack[i] -= d;
        }

        for(int i = 1; i <= n; i++){
            if(!vy[i]){
                if(!slack[i]){
                    //找到了增广边
                    vy[i] = true;
                    if(!py[i]) {aug(i); return;}
                    q.push(py[i]);
                }
            }
        }
        
    }
}

//注意在输入边权之前将所有边权置为-INF
ll km(){
    ll rt = 0;
    //初始化顶标
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            lx[i] = max(lx[i], e[i][j]);
    for(int i = 1; i <= n; i++) bfs(i);
    //必然存在完美匹配的情况
    for(int i = 1; i <= n; i++)
        rt += e[i][px[i]];
    //如果不保证存在完美匹配，我们保证左部点个数小于等于右部点个数
    //即往右部添加虚点和虚边
    //若允许某些点空缺，则虚边权值置为0，表示空匹配
    //若不允许非完美匹配，虚边值置为-INF，若选中虚边，则代表不存在完美匹配
    return rt;
}