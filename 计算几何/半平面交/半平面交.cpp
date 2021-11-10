const int maxn=2e5+100;
typedef double db;
const db eps=1e-5;

int st,ed,tot;				//st,ed队首/队尾[st,ed];tot,边的总数[1,tot]

struct Vec{
	db x,y;
	Vec(db a=0,db b=0){x=a,y=b;}
	Vec operator+(const Vec&a)const{return Vec(x+a.x,y+a.y);}	//向量加减
	Vec operator-(const Vec&a)const{return Vec(x-a.x,y-a.y);}
	void operator+=(const Vec&a){(this->x)+=a.x;(this->y)+=a.y;}
	void operator-=(const Vec&a){(this->x)-=a.x;(this->y)-=a.y;}
	Vec operator*(const db&a){return Vec(x*a,y*a);}				//向量与实数的乘除
	Vec operator/(const db&a){return Vec(x/a,y/a);}
	void operator*=(const db&a){(this->x)*=a;(this->y)*=a;}
	void operator/=(const db&a){(this->x)/=a;(this->y)/=a;}
};

Vec Q[maxn],M[maxn];		//Q:暂存点坐标，M:最后平面交的顶点坐标

db crossPow(Vec a,Vec b){			//叉乘
	return a.x*b.y-a.y*b.x;
}

db pointPow(Vec a,Vec b){			//点乘
	return a.x*b.x+a.y*b.y;
}

struct Line{
	Vec s,v;			//s:起点,v:方向
	db k;				//k:极角
	Line(){};
	Line(Vec a,Vec b):s(a),v(b){k=atan2(b.y,b.x);}
	bool operator<(const Line&a){return k<a.k;}
};

Line P[maxn],T[maxn];		//P:所有线[1,tot],T:队列内的线[st,ed]


Vec getCrossPoint(Line a,Line b){
	Vec c=a.s-b.s;
	db t=crossPow(b.v,c)/crossPow(a.v,b.v);
	return Vec(a.s+a.v*t);
}

bool halfPlaneIntersection(){	//bool表示交平面是否存在(面积是否为0)
	sort(P+1,P+tot+1);			//极角排序
	st=ed=1;					//初始化队首队尾
	T[st]=P[1];					//第一根线入队
	for(int i=2;i<=tot;i++){
		while(st<ed&&crossPow(P[i].v,M[ed-1]-P[i].s)<=eps)ed--;		//交点在当前边右侧，踢出队尾
		while(st<ed&&crossPow(P[i].v,M[st]-P[i].s)<eps)st++;		//交点在当前边右侧，踢出队首
		T[++ed]=P[i];
		if(fabs(crossPow(T[ed].v,T[ed-1].v))<=eps){					//平行边
			ed--;
			if(crossPow(T[ed].v,P[i].s-T[ed].s)>eps)T[ed]=P[i];		//取偏左那个
		}
		if(st<ed){													//多个点在队列中，求交点进入M
			M[ed-1]=getCrossPoint(T[ed-1],T[ed]);
		}
	}
	while(st<ed&&crossPow(T[st].v,M[ed-1]-T[st].s)<=eps)ed--;
	if(ed-st<=1)return false;
	M[ed]=getCrossPoint(T[st],T[ed]);
	return true;
}

double Area(){
    double ans=0;
	for(int i=st;i<=ed;i++){
		ans+=crossPow(M[i],M[(i==ed?st:i+1)]);	//向量叉乘表示面积
	}
	return ans/2.0;
}