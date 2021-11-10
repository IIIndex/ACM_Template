ll tree[maxn*10];
ll mark[maxn*10];
ll a[maxn];                                                         //特别记住这个模板a要从1开始存

void push_down(ll p,ll len){                                        //将mark向下传递函数
	mark[p*2]+=mark[p];
	mark[p*2+1]+=mark[p];
	tree[p*2]+=mark[p]*(len-len/2);
	tree[p*2+1]+=mark[p]*(len/2);
	mark[p]=0;
}


void build(ll l,ll r,ll p){                                         //建树函数，记得输入完数据之前调用一遍
	if(l==r)
		tree[p]=a[l];
	else{
		ll mid=(l+r)/2;
		build(l,mid,p*2);
		build(mid+1,r,p*2+1);
		tree[p]=tree[p*2]+tree[p*2+1];
	}
}

void update(ll l,ll r,ll d,ll p,ll cl,ll cr){                       //加法更新函数，l/r指的更新区间，d是加数，p是当前区块，cl/cr是当前区块对应区间
	if(cl>r||cr<l)return;                                           //p在调用时一般初始化为1，cl为1，cr为n（a数组长度）
	else if(l<=cl&&r>=cr){
		tree[p]+=(cr-cl+1)*d;
		if(cr>cl)
			mark[p]+=d;
	}
	else{
		ll mid=(cl+cr)/2;
		push_down(p,cr-cl+1);
		update(l,r,d,p*2,cl,mid);
		update(l,r,d,p*2+1,mid+1,cr);
		tree[p]=tree[p*2]+tree[p*2+1];
	}
}

ll query(ll l,ll r,ll p,ll cl,ll cr){                               //查询函数，变量意义同上
	if(cl>r||cr<l)return 0;
	else if(cl>=l&&cr<=r)return tree[p];
	else{
		ll mid=(cl+cr)/2;
		push_down(p,cr-cl+1);
		return query(l,r,p*2,cl,mid)+query(l,r,p*2+1,mid+1,cr);
	}
}