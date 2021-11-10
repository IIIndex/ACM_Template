//计算任意多边形面积
const int maxn=2e5+100;

struct P{
    double x,y;             //存顶点坐标（下标从1开始）
}p[maxn];

double Area(int n){         //n为顶点总数
    double rt=0;
    for(int i=1;i<n;i++){
        rt+=p[i].x*p[i+1].y-p[i].y*p[i+1].x;
    }
    rt=fabs(rt);
    rt+=fabs(p[1].x*p[n].y-p[1].y*p[n].x);
    rt/=2.0;
    return rt;
}