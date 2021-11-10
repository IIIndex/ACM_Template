#define ll long long
const int inf=1e9+7;
const ll INF=1e15;
const int maxn=1e4+100;
int pree[maxn],pren[maxn];					//pree[i]——通往i的最短路的边（边从pren[i]到i，这条边的编号为pree[i]）；
											//pren[i]——通往i的最短路的边的出点（边从pren[i]到i，这条边的编号为pree[i]）；
ll h[maxn];									//势h，保证dijkstra跑图时权值非负（见README）
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
}nodee[maxn*10];                                    //保存边的信息

struct d_node{                                      //优先队列元素
	int u;                                          //“当前起始点”
	long long dis;                                  //被塞入队列时该点到起点的距离
	bool operator<(const d_node& an)const{          //优先队列比较函数（小顶堆）
		return dis>an.dis;
	}
};

void add(int u,int v, int w,int flow){              //加边函数
	nodee[++cnt].next=head[u];						//一定要++cnt，否则异或访问边和我们添加的反向边时会出问题
	nodee[cnt].v=v;
	nodee[cnt].flow=flow;	
	head[u]=cnt;	
	nodee[cnt].w=w;

	nodee[++cnt].next=head[v];
	nodee[cnt].v=u;
	nodee[cnt].flow=0;
	head[v]=cnt;
	nodee[cnt].w=-w;
}

bool Dijkstra(){
	priority_queue<d_node>q;
	for(int i=1;i<=n;i++){
		length[i]=INF;                                              //初始化将所有点离起点的距离置为INF
		vis[i]=0;                                                   //清空访问记录
	}
	pren[t]=-1;
	length[s]=0;                                                    //起点到起点距离为0
	q.push({s,0});                                                  //s：起始点，0：距离
	while(!q.empty()){
		d_node tmp=q.top();                                         //用d_node保存首元素信息
		q.pop();
		int u=tmp.u;                                                //首元素节点编号
		if(vis[u])                                                  //不重复更新
			continue;
		vis[u]=1;                                                   //记录以及更新
		for(int i=head[u];i;i=nodee[i].next){                       //链式前向星遍历
			int v=nodee[i].v,w=nodee[i].w+h[u]-h[v];				//w加上势之差（出点减入点）后保证length数组非负
			if(nodee[i].flow>0&&w+length[u]<length[v]){             //更新权值
				length[v]=w+length[u];
				pren[v]=u;
				pree[v]=i;											//更新前点和连接前点的边
                if(!vis[v]){
				    q.push({v,length[v]});                          //随时更新
			    }
			}
		}
	}
	if(pren[t]!=-1)return true;										//存在增广路
	else return false;
}

void MCMF(){
	while(Dijkstra()){
		ll minum=INF;
		for(int i=t;i!=s;i=pren[i]){
			minum=min(minum,nodee[pree[i]].flow);						//找到能容纳的最大流量
		}
		for(int i=t;i!=s;i=pren[i]){									//减流（反向边加流）
			nodee[pree[i]].flow-=minum;
			nodee[pree[i]^1].flow+=minum;
		}
		max_flow+=minum;
		min_cost+=minum*(length[t]+h[t]);								//记得加上势
		for(int i=1;i<=n;i++){
			h[i]=min(h[i]+length[i],INF);								//势每次更新是和新的length相加
		}
	}
}