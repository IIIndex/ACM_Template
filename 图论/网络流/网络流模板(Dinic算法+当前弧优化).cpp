
int head[maxn],l[maxn],now[maxn];                               //head：链式前向星存图，l[]：保存顶点的“层数”，now：进行当前弧优化
int n,m,s,t;                                                    //n:顶点数 m:边数 s:起始点 t:终点
int cnt=1;                                                      //从e[1]开始保存

struct node{
    int next;
    int to;
    int val;
}e[maxm];                                                    //next：链式前向星存图


const int inf=1e9+7;
const long long INF=1e15+100;


void add(int u,int v,int w){                                //添加《有向边》,如果是无向边的话下面得改一改
    e[++cnt].to=v;
    e[cnt].val=w;
    e[cnt].next=head[u];
    head[u]=cnt;
    e[++cnt].to=u;
    e[cnt].val=0;                                           //要改的就是这里，无向边的话反向改为w
    e[cnt].next=head[v];
    head[v]=cnt;
}

int bfs(){                                                  //每次bfs查询是否有起始点到终点的增广路
    for(int i=1;i<=n;i++){
        l[i]=inf;
    }
    queue<int> q;
    l[s]=0;
    q.push(s);
    now[s]=head[s];                                         //把能联通的边的now[]进行更新
    while(!q.empty()){
        int n=q.front();
        q.pop();
        for(int i=head[n];i;i=e[i].next){
            int v=e[i].to;
            if(l[v]==inf&&e[i].val>0){
                q.push(v);
                l[v]=l[n]+1;
                now[v]=head[v];
                if(v==t)return 1;                           //增广路存在，函数返回并开始dfs
            }
        }
    }
    return 0;
}

long long dfs(int x,long long tot){                         //x是当前所查找到的结点，tot是《当前结点能提供的总流量》
    if(x==t){
        return tot;
    }
    long long used=0;
    for(int i=now[x];i&&tot;i=e[i].next){                   //这里的now数组是进行当前弧优化，在now之前《已经使用完全》的弧没必要dfs
        now[x]=i;
        int v=e[i].to;
        if(e[i].val>0&&l[x]+1==l[v]){
            long long k=dfs(v,min((long long)e[i].val,tot));        //下一个结点的最大流量由当前结点的最大流量和这两个结点之间边所能承受的最大流量
            if(k==0)l[v]=inf;
            e[i].val-=k;
            e[i^1].val+=k;
            used+=k;
            tot-=k;
        }
    }
    return used;                                            //所有《当前节点的》下一层结点使用的流量总和
}

long long flow(){
    long long ans=0;
    while(bfs()){
        ans+=dfs(s,INF);
    }
    return ans;
}
