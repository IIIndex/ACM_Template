ll mod;                                         //mod一定要是质数!!!

ll x,y;                                         //最后的答案是x

void exgcd(ll a,ll b){
    if(b==0){
        x=1,y=0;
        return;
    }
    exgcd(b,a%b);
    ll tmp=x;
    x=y;
    y=tmp-a/b*y;
}

void rational_mod(ll a,ll b){                   //a分子，b分母
    exgcd(b,mod);
    x=(x%mod+mod)%mod;
    x*=a;
    x%=mod;
}


inline int read(){                              //读入时顺便取余
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',x%=mod,ch=getchar();
    return x*f;
}