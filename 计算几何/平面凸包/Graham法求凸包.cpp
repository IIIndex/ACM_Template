const int maxn=2e5+100;
typedef double db;
const db eps=1e-8;

struct Node{
	db x,y;
	bool operator <(const Node &oth){
		if(oth.x==x)return y<oth.y;
		return x<oth.x;
	}
}P[maxn],Con[maxn];														//P为原来的点，Con为凸包里的点

db Cross(Node a1,Node a2,Node b1,Node b2){								//向量叉积
	return (a2.x-a1.x)*(b2.y-b1.y)-(b2.x-b1.x)*(a2.y-a1.y);
}

db dis(Node a,Node b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

bool cmp(Node a,Node b){												//a,b叉积<0，b在a的逆时针方向，反之亦然
	db m=Cross(P[1],a,P[1],b);
	if(fabs(m)<eps)return dis(P[0],a)<dis(P[0],b);
	if(m>0)return 1;
	else return 0;
}

void Graham(){
	int top=0;															//模拟栈
	db ans=0;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>P[i].x>>P[i].y;
	}
	sort(P+1,P+n+1);													//选定左下角点
	Con[++top]=P[1];
	sort(P+2,P+n+1,cmp);													//极角排序
	Con[++top]=P[2];
	for(int i=3;i<=n;i++){
		while(top>=2&&Cross(Con[top-1],Con[top],Con[top],P[i])<=0)top--;	//Cross重写可以控制重复点、共线
		Con[++top]=P[i];
	}
	for(int i=1;i<top;i++)ans+=dis(Con[i],Con[i+1]);
	ans+=dis(Con[top],Con[1]);
	printf("%.2lf\n",ans);
}