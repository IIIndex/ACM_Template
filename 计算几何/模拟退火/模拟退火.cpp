const int maxn=2e5+100;
const long double dt=0.996;
double ansx,ansy,ans;

struct point{
    int x,y,w;
}p[maxn];

long double cal(long double x,long double y){
    /* code here */                     //计算当前状态答案
}

void sa(){
    long double t=3000;
    while(t>1e-15){
        long double X=ansx+((rand()<<1)-RAND_MAX)*t;
        long double Y=ansy+((rand()<<1)-RAND_MAX)*t;
        long double now=cal(X,Y);
        long double dleta=now-ans;              //dleta为当前状态答案和当前最佳答案差值
        if(dleta<0){
            ansx=X,ansy=Y,ans=now;              //当前状态更优，一定接受
        }
        else if(exp(-dleta/t)*RAND_MAX>rand()){ansx=X,ansy=Y;}  //一定概率接受非最优解
        t*=dt;                                  //降温
    }
}

void solve(){
    srand(time(NULL));                      //开头就设定随机数种子，避免sa()内设置相同
    cin>>n;                                 //输入按题
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y>>p[i].w;
        ansx+=p[i].x;
        ansy+=p[i].y;
    }
    ansx/=n,ansy/=n;
    ans=cal(ansx,ansy);                     //左右初始值和ans初始值采用中间位置
    sa();sa();sa();sa();                    //多次模拟退火求最优解
}   