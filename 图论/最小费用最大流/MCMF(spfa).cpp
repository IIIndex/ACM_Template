const int maxn=1e4+1000;
const int inf=1e9+7;
const ll INF=1e15+7;
int pree[maxn],pren[maxn];					//pree[i]——通往i的最短路的边（边从pren[i]到i，这条边的编号为pree[i]）；
											//pren[i]——通往i的最短路的边的出点（边从pren[i]到i，这条边的编号为pree[i]）；
ll flow[maxn];                              //保存“当前汇到这个结点的流量”
ll length[maxn],vis[maxn];                  //length数组代表起点到终点的距离，vis数组代表该点是否已经被处理过
int cnt=1;                                  //对边进行计数
int n,m,s,t;                                //n：点的总数，m：边的总数，s：源点，t：汇点
ll max_flow=0,min_cost=0;					//累加最大流量和最小花费
int head[maxn];                             //链式前向星存图

struct node{
	int v;
	int next;
	ll w;
	ll flow;
}e[maxn*10];                                    //保存边的信息

void add(int u,int v, int w,int flow){              //加边函数
	e[++cnt].next=head[u];						//一定要++cnt，否则异或访问边和我们添加的反向边时会出问题
	e[cnt].v=v;
	e[cnt].flow=flow;	
	head[u]=cnt;	
	e[cnt].w=w;

	e[++cnt].next=head[v];
	e[cnt].v=u;
	e[cnt].flow=0;
	head[v]=cnt;
	e[cnt].w=-w;
}

bool spfa(){
    for(int i=1;i<=n;i++){
        length[i]=inf;                                          //初始化距离，流量和访问记录
        vis[i]=0;
        flow[i]=inf;
    }
    queue<int> q;
    q.push(s);vis[s]=1;
    length[s]=0;pren[t]=-1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].v;
            if(e[i].flow&&length[u]+e[i].w<length[v]){                  //找到更短路径
                length[v]=length[u]+e[i].w;
                pree[v]=i;
                pren[v]=u;                                              //保存更短路径信息
                flow[v]=min(flow[u],e[i].flow);                         //流量取一路上的最小值
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);                                          //未入队的入队
                }
            }
        }
    }
    return pren[t]!=-1;
}

void MCMF(){
    while(spfa()){
        max_flow+=flow[t];
        min_cost+=flow[t]*length[t];
        for(int i=t;i!=s;i=pren[i]){
            e[pree[i]].flow-=flow[t];
            e[pree[i]^1].flow+=flow[t];
        }
    }
}