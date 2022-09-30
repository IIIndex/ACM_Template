struct edge{
    int v, w;
};

vector<edge> e[maxn];

int dis[maxn], cnt[maxn], inq[maxn];

// O(n ^ 2)
// 返回值为false即为无解
// s为超级源点，记得和其它所有点连一条权值为0的边
// 最后的dis数组即为一组解, dis数组同加 / 减一个数仍为原方程组的解
bool SPFA(int s, int n){
    // 0 ~ n
    for(int i = 0; i <= n; i++) dis[i] = inf, cnt[i] = inq[i] = 0;
    dis[s] = 0;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(cnt[u] > n + 1) return false;
        inq[u] = 0;
        for(auto& eg: e[u]){
            int v = eg.v, w = eg.w;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                if(!inq[v]) {
                    q.push(v); inq[v] = 1;
                    cnt[v]++;
                }
            }
        }
    }
    return true;
}