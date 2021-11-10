//本模板是莫队查询区间内不同元素个数（未离散化）
const int maxn=3e5+100;             //数组元素最大值
const int maxm=1e6+100;             //数据范围（可加离散化）
const int maxq=3e5+100;             //查询次数

int sq;

int a[maxn],cnt[maxm],ans[maxn],cur;        //a-原数组，cnt-数据个数，ans-对应每个询问的答案，cur-当前元素个数

struct node{
	int l,r,id;                             //左右区间和询问编号
	bool operator<(const node &oth){        //块内按奇偶分别升/降序排序，块外按l排序
		if(l/sq!=oth.l/sq)return l<oth.l;
		if((l/sq)&1)return r<oth.r;
		else return oth.r<r;
	}
}Q[maxq];

void add(int p){                    //增加数
	cnt[a[p]]++;
	if(cnt[a[p]]==1)cur++;
}

void del(int p){                    //删去数
	cnt[a[p]]--;
	if(!cnt[a[p]])cur--;
}


void solve(){
    int n,q;
	//cin>>n>>q;                    //输入按题目给定格式
	cin>>n;
	sq=sqrt(n);                     //分块
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>q;
	for(int i=1;i<=q;i++)cin>>Q[i].l>>Q[i].r,Q[i].id=i;
	sort(Q+1,Q+q+1);
	int l=0,r=0;                    //初始化
	for(int i=1;i<=q;i++){
		while(l<Q[i].l)del(l++);    //删数不删边界
		while(l>Q[i].l)add(--l);    //加数加边界
		while(r<Q[i].r)add(++r);
		while(r>Q[i].r)del(r--);
		ans[Q[i].id]=cur;           //保存答案信息
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
}