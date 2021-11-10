ll x,y;

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

//记住最后得到的x需要进行x=(x%b+b)%b才是最小整数解