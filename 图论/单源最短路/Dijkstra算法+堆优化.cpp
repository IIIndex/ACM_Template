#define ll long long
const int inf=1e9+7;
const int INF=1e15;
const int maxn=1e5+100;
ll length[maxn],vis[maxn];                  //length数组代表起点到终点的距离，vis数组代表该点是否已经被处理过
int cnt=1;                                  //对边进行计数
int n,m,s;                                  //n：点的总数，m：边的总数，s：起始点
int head[maxn];                             //链式前向星存图
struct node{
	int v;
	int next;
	ll w;
}nodee[maxn*2];                             //保存边的信息

struct d_node{                              //优先队列元素
	int u;                                  //“当前起始点”
	long long dis;                          //被塞入队列时该点到起点的距离
	bool operator<(const d_node& an)const{  //优先队列比较函数（小顶堆）
		return dis>an.dis;
	}
};

void add(int u,int v, int w){               //加边函数（有向边）
	nodee[cnt].next=head[u];
	nodee[cnt].v=v;
	head[u]=cnt;
	nodee[cnt++].w=w;
}

void Dijkstra(){
	priority_queue<d_node>q;
	for(int i=0;i<=n;i++){
		length[i]=INF;                      //初始化将所有点离起点的距离置为INF
	}
	length[s]=0;                            //起点到起点距离为0
	q.push({s,0});                          //s：起始点，0：距离
	while(!q.empty()){
		d_node tmp=q.top();                 //用d_node保存首元素信息
		q.pop();
		int u=tmp.u;                        //首元素节点编号
		if(vis[u])                          //不重复更新
			continue;
		vis[u]=1;                           //记录以及更新过了
		for(int i=head[u];i;i=nodee[i].next){       //链式前向星遍历
			int w=nodee[i].w,v=nodee[i].v;
			if(w+length[u]<length[v]){              //更新权值
				length[v]=w+length[u];
                if(!vis[v]){
				    q.push({v,length[v]});              //随时更新
			    }
			}
		}
	}
}