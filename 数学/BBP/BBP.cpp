//BBP算法：nlogn计算pi的第n位数字（十六进制）


ll qpow(ll x, ll a, ll mod){                    //自定义余数的快速幂
    ll base = x, rt = 1;
    while(a){
        if(a & 1) {rt *= base; rt %= mod;}
        base *= base;
        base %= mod;
        a >>= 1;
    }
    return rt;
}

//单项求和

double BBP(int n, int a, int b){
    double rt = 0.0;
    for(int i = 0; i <= n; i++){                //计算k = 0到k = n的项
        rt += qpow(16, n - i, 8 * i + b) / (8.0 * i + b);
    }
    return rt * a;
}

//pi = \sigma{k = 0, \inf} 1 / 16 ^ k * (4 / (8k + 1) - 2 / (8k + 4) - 1 / (8k + 5) - 1 / (8k + 6))

double BBPFormular(int n){
    return BBP(n, 4, 1) + BBP(n, -2, 4) + BBP(n, -1, 5) + BBP(n, -1, 6);
}

void solve(){
    static int t = 0;
    int n;
    cin >> n;
    n--;                            //因为计算了整数位，所以说是0-index
    double res = BBPFormular(n);
    res -= (int)res;
    if(res < 0.0) res += 1.0;       //出现负数则加一
    res *= 16;
    int ans = res;
    cout << (char)(ans >= 10 ? (ans - 10 + 'A') : (ans + '0')) << endl;
}