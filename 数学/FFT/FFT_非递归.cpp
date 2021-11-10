const int maxn=2e5+100;

const double Pi=acos(-1.0);

struct Complex
{
    double x,y;
    Complex (double xx=0,double yy=0){x=xx,y=yy;}
}a[maxn],b[maxn];                                                               //a和b分别为原来的多项式，结果存储在A中
Complex operator + (Complex a,Complex b){ return Complex(a.x+b.x , a.y+b.y);}
Complex operator - (Complex a,Complex b){ return Complex(a.x-b.x , a.y-b.y);}
Complex operator * (Complex a,Complex b){ return Complex(a.x*b.x-a.y*b.y , a.x*b.y+a.y*b.x);}//不懂的看复数的运算那部分 
int N,M;
int l,r[maxn];
int limit=1;


void fft(Complex *A,int type)
{
    for(int i=0;i<limit;i++) 
        if(i<r[i]) swap(A[i],A[r[i]]);//求出要迭代的序列 
    for(int mid=1;mid<limit;mid<<=1)//待合并区间的中点
    {
        Complex Wn( cos(Pi/mid) , type*sin(Pi/mid) ); //单位根 
        for(int R=mid<<1,j=0;j<limit;j+=R)//R是区间的右端点，j表示前已经到哪个位置了 
        {
            Complex w(1,0);//幂 
            for(int k=0;k<mid;k++,w=w*Wn)//枚举左半部分 
            {
                 Complex x=A[j+k],y=w*A[j+mid+k];//蝴蝶效应 
                A[j+k]=x+y;
                A[j+mid+k]=x-y;
            }
        }
    }
}

void solve(){
    cin>>N>>M;
    for(int i=0;i<=N;i++)cin>>a[i].x;
    for(int i=0;i<=M;i++)cin>>b[i].x;
    while(limit<=N+M) limit<<=1,l++;
    for(int i=0;i<limit;i++)
        r[i]= ( r[i>>1]>>1 )| ( (i&1)<<(l-1) ) ;
    fft(a,1);
    fft(b,1);
    for(int i=0;i<=limit;i++) a[i]=a[i]*b[i];
    fft(a,-1);
    for(int i=0;i<=N+M;i++)cout<<(int)(a[i].x/limit+0.5)<<" ";
}