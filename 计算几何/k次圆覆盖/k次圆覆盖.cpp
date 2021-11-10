const int maxn=2e5+100;
typedef double db;
const db eps=1e-8;
const db PI=acos(-1);

int dcmp(db x){
	return fabs(x)<eps?0:(x<0?-1:1);
}

struct Circle{
	db x,y,r,angle;
	int d;
	Circle(){};
	Circle(db x,db y,db angle=0,int d=0)
		:x(x),y(y),angle(angle),d(d){};
};

Circle cir[maxn],tp[maxn<<1];				//cir存输入圆，下标[0,n)

db area[maxn];								//area[i]存被i个圆覆盖的面积大小

db pow2(db x){return x*x;}

db dis(Circle a,Circle b){return sqrt(pow2(a.x-b.x)+pow2(a.y-b.y));}

db cross(Circle a,Circle b,Circle c){
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

int CirCrossCir(Circle p1,db r1,Circle p2,db r2,Circle &cp1,Circle &cp2){
	db mx=p2.x-p1.x,sx=p2.x+p1.x,mx2=mx*mx;
	db my=p2.y-p1.y,sy=p2.y+p1.y,my2=my*my;
	db sq=mx2+my2,d=-(sq-pow2(r1-r2))*(sq-pow2(r1+r2));
	if(d+eps<0)return 0;
	if(d<eps)d=0;
	else d=sqrt(d);
    db x =mx*((r1+r2)*(r1-r2)+mx*sx)+sx*my2;
    db y =my*((r1+r2)*(r1-r2)+my*sy)+sy*mx2;
	db dx=mx*d,dy=my*d;
	sq*=2;
	cp1.x=(x-dy)/sq;
	cp1.y=(y+dx)/sq;
	cp2.x=(x+dy)/sq;
	cp2.y=(y-dx)/sq;
	if(d>eps)return 2;
	return 1;
}

bool circmp(Circle a,Circle b){
	return dcmp(a.r-b.r)<0;
}

bool cmp(const Circle &a,const Circle &b){
	if(dcmp(a.angle-b.angle))return a.angle<b.angle;
	return a.d>b.d;
}

double calc(Circle cir,Circle cp1,Circle cp2){
	double ans=(cp2.angle-cp1.angle)*pow2(cir.r)
				-cross(cir,cp1,cp2)+cross(Circle(0,0),cp1,cp2);
	return ans/2.0;
}

void CircleUnion(Circle *cir,int n){
	Circle cp1,cp2;
	sort(cir,cir+n,circmp);
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(dcmp(dis(cir[i],cir[j])+cir[i].r-cir[j].r)<=0)
				cir[i].d++;
		}
	}
	for(int i=0;i<n;i++){
		int tn=0,cnt=0;
		for(int j=0;j<n;j++){
			if(i==j)continue;
			if(CirCrossCir(cir[i],cir[i].r,cir[j],cir[j].r,cp2,cp1)<2)continue;
			cp1.angle=atan2(cp1.y-cir[i].y,cp1.x-cir[i].x);
			cp2.angle=atan2(cp2.y-cir[i].y,cp2.x-cir[i].x);
			cp1.d=1;
			tp[tn++]=cp1;
			cp2.d=-1;
			tp[tn++]=cp2;
			if(dcmp(cp1.angle-cp2.angle)>0)cnt++;
		}
		tp[tn++]=Circle(cir[i].x-cir[i].r,cir[i].y,PI,-cnt);
		tp[tn++]=Circle(cir[i].x-cir[i].r,cir[i].y,-PI,cnt);
		sort(tp,tp+tn,cmp);
		int p,s=cir[i].d+tp[0].d;
		for(int j=1;j<tn;j++){
			p=s;
			s+=tp[j].d;
			area[p]+=calc(cir[i],tp[j-1],tp[j]);
		}
	}
}

int n;

void work(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>cir[i].x>>cir[i].y>>cir[i].r;
		cir[i].d=1;
	}
	memset(area,0,sizeof(area));
	CircleUnion(cir,n);
	for(int i=1;i<=n;i++){
		area[i]-=area[i+1];							//每次要减去比它多一个圆覆盖的面积
		//printf("[%d] = %.3lf\n",i,area[i]);
	}
}