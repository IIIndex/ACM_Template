//********本模板只适用于积分收敛情况**********

typedef double db;
const db eps_origon=1e-8;                          	//初始eps，根据需要调整精度


db f(db x){
	/* code here */                                 //待积分函数
}

db simpson(db l,db r){
	double mid=(l+r)/2;
	return (r-l)*(f(l)+f(r)+4*f(mid))/6.0;			//辛普森积分本体
}

db work(db l,db r,db eps){
	db mid=(l+r)/2;
	db rt=simpson(l,r);
	db left=simpson(l,mid);
	db right=simpson(mid,r);
	if(fabs(rt-left-right)<15*eps)return left+right+(left+right-rt)/15.0;			//避免递归层数过深
	else return work(l,mid,eps/2)+work(mid,r,eps/2);
}

void solve(){
	db l,r;											//l,r分别为积分下界和积分上界						
	db ans=work(l,r,eps_origon);
}