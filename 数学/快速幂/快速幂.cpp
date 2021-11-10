ll mod=1e9+7;                                               //余数

ll qpow(ll a,ll k){                                         //a为底，k为幂
    ll base=a,ans=1;a%=mod;
    while(k){
        if(k&1)ans=ans*base%mod;
        base=base*base%mod;
        k>>=1;
    }
    return ans%mod;
}