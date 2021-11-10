 int head[maxn],h[maxn];                               			//head：链式前向星存图，h[]：保存顶点的“层数”
int vis[maxn],stored[maxn];										//stored[]：当前节点所暂存的流量
int gap[maxn];													//gap优化
int n,m,s,t;                                                    //n:顶点数 m:边数 s:起始点 t:终点
int cnt=1;                                                      //从e[0]开始保存

struct node{
    int next;
    int to;
    int flow;
}e[250000];                                                    //next：链式前向星存图

void add(int u,int v,int w){                                //添加《有向边》,如果是无向边的话下面得改一改
    e[++cnt].to=v;
    e[cnt].flow=w;
    e[cnt].next=head[u];
    head[u]=cnt;
    e[++cnt].to=u;
    e[cnt].flow=0;                                           //要改的就是这里，无向边的话反向改为w
    e[cnt].next=head[v];
    head[v]=cnt;
}

inline bool bfs(){
	for(register int i=1;i<=n;i++){
		h[i]=inf;									//初始化节点高度
	}
	h[t]=0;											//反向搜索“高度”
	queue<int> q;
	q.push(t);
	while(!q.empty()){
		int tmp=q.front();
		q.pop();
		for(register int i=head[tmp];i;i=e[i].next){
			int v=e[i].to;
			if(e[i^1].flow&&h[v]>h[tmp]+1){			//e[i^1]判断反向边（因为是反向搜索），如果高度有改变就要重新入队
				h[v]=h[tmp]+1;
				q.push(v);
			}
		}
	}
	return(h[s]!=inf);								//存在增广路与否
}

struct cmp{
	inline bool operator()(int xi,int yi)const{		//以结点高度为关键字的优先队列
		return h[xi]<h[yi];
	}
};
priority_queue<int,vector<int>,cmp> pq;

inline void push(int u){							//将“除了起点和终点”以外的可行点放进优先队列（终点和起点需要特别判断）
	for(register int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(e[i].flow&&h[u]==h[v]+1){
			int df=min(stored[u],e[i].flow);
			e[i].flow-=df;							//正向边流量减少
			e[i^1].flow+=df;						//反向边流量增加
			stored[u]-=df;							//当前节点存储流量减少
			stored[v]+=df;							//目标节点存储流量增加
			if(v!=s&&v!=t&&!vis[v]){
				vis[v]=1;
				pq.push(v);
			}
			if(!stored[u])break;					//当前节点被榨干了
		}
	}
}

inline void relabel(int u){
	h[u]=inf;
	for(register int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(e[i].flow&&(h[u]>h[v]+1))h[u]=h[v]+1;					//将一个节点的高度抬高到“恰好”能够流到下一个节点
	}
}

inline ll HLPP(){
	if(!bfs())return 0;
	h[s]=n;
	memset(gap,0,sizeof(gap));
	for(register int i=1;i<=n;i++)if(h[i]!=inf)gap[h[i]]++;			//gap优化：记录当前层有多少节点
	for(register int i=head[s];i;i=e[i].next){						//对原点进行特判，因为原点的容量是无限的（而不是我们定义的INF）
		int v=e[i].to;
		if(int f=e[i].flow){
			e[i].flow-=f;
			e[i^1].flow+=f;
			stored[v]+=f;
			if(v!=s&&v!=t&&!vis[v]){
				pq.push(v);
				vis[v]=1;
			}
		}
	}
	while(!pq.empty()){
		int now=pq.top();											//取出最“高”的结点
		vis[now]=0;
		pq.pop();
		push(now);
		if(stored[now]){
			if(h[now]==inf)continue;
			gap[h[now]]--;
			if(!gap[h[now]]){
				for(register int v=1;v<=n;v++){
					if(v!=s&&v!=t&&h[v]>h[now]&&h[v]<n+1){			//避免改动inf和以及处于n+1位置的结点
						h[v]=n+1;									//如果最高层只有一个，则它直接流回原点
					}
				}
			}
			relabel(now);											//重新贴标签
			gap[h[now]]++;
			pq.push(now);											//重贴标签后推流
			vis[now]=1;
		}
	}
	return stored[t];
}