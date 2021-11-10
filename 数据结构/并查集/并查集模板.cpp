/*一定一定记得开始的时候初始化fa[i]=i*/

int fa[maxn];

int find(int x){                                            //寻找x的集合“老大”
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);                          //顺便更新x一路上的，使其成为老大的直接下属
}

void unionn(int x,int y){                                   //将x和y置于同一集合
	int fx=find(x),fy=find(y);
	if(fx==fy)return;                                       //如果本来就在一个集合，直接返回
	else fa[fx]=fy;                                         //这里可以优化，具体见下
}

/*在连接两个集合的时候，如果把小集合链接到大集合下面，可以减小以后查询的时候的更新时间，这就要用到辅助数组，辅助数组直接依附于集合最顶元素（也
就是x=fa[x]的x，辅助数组的大小就是依附于x（包括x）的元素的个数*/