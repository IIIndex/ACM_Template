//O(n ^ 2)求已知前n项的数列的递推式
typedef long long ll;
const ll mod = 1e9 + 7;

ll qpow(ll x, ll a){
    ll base = x, rt = 1;
    while(a){
        if(a & 1){
            rt *= base;
            rt %= mod;
        }
        base *= base;
        base %= mod;
        a >>= 1;
    }
    return rt;
}

ll inv(ll x){
    x %= mod;
    return qpow(x, mod - 2);
}

//R[i]表示经过i次更新后的递推式
//对于某个具体的R[id]而言
//a[i] = a[i - 1] * R[id][0] + a[i - 2] * R[id][1]... + a[i - R[id].size()] * R[id][R[id].size() - 1]
//ans就是最后的结果
vector<ll> R[maxn], ans;

//a: 初始数组，fail[i]表示R[i]在哪里失效(第一个不满足R[i]递推式的地方)
//delta[i]表示R[i]失效时a[i]和计算所得的差值
ll a[maxn], fail[maxn], delta[maxn];

void add(ll &a, ll b){
    if((a += b) >= mod) a -= mod;
}

void del(ll &a, ll b){
    if((a -= b) < 0) a += mod;
}

void bm(int n){         //n表示已知数列长度
    int cnt = 0;        //cnt表示当前是R[cnt]
    R[0].clear();
    for(int i = 1; i <= n; i++){
        if(cnt == 0){
            if(a[i]){   //0, 0, ... 0, a[i]
                fail[cnt++] = i;
                delta[i] = a[i];
                R[cnt].resize(0);
                R[cnt].resize(i, 0);    //前面都是0
            }
            continue;
        }
        ll sum = 0; int m = R[cnt].size();
        //随时更新当前版本的fail，计算差值
        delta[i] = a[i]; fail[cnt] = i;
        for(int j = 0; j < m; j++){
            add(sum, a[i - j - 1] * R[cnt][j] % mod);
        }
        del(delta[i], sum);
        //数列能够匹配得上
        if(!delta[i]) continue;
        //找到长度最短的递推
        int id = cnt - 1, v = i - fail[id] + R[id].size();
        for(int j = 0; j < cnt - 1; j++){
            if(i - fail[j] + R[j].size() < v){
                id = j; v = i - fail[j] + R[id].size();
            }
        }
        //构造R' = {0, 0, ... 0, tmp, -tmp * R[id][0], ... -tmp * R[id][R[id].size() - 1]}
        //tmp = delta[i] / delta[id]
        //R[cnt + 1] = R[cnt] + R'
        ll tmp = inv(delta[fail[id]]) * delta[i] % mod;
        R[cnt + 1] = R[cnt];
        while(R[cnt + 1].size() < v) R[cnt + 1].push_back(0);
        add(R[cnt + 1][i - fail[id] - 1], tmp);
        for(int j = 0; j < R[id].size(); j++) 
            del(R[cnt + 1][i - fail[id] + j], tmp * R[id][j] % mod);
        cnt++;
    }
    ans = R[cnt];
}


void solve(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    bm(n);
    cout << ans.size() << '\n';
    for(auto v: ans) cout << v << ' ';
    cout << endl;
}