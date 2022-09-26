namespace NTT{
    // 998244353 - 1 = 2 ^ 23 * 119
    // g为998244353的原根，gi为g在模998244353意义下的逆元
    constexpr int maxn = (1 << 22) + 100, g = 3, gi = 332748118, mod = 998244353;
    // n为a数组长度(0 ~ n)，m为b数组长度(0 ~ m)rev[i]为i的二进制翻转
    int n, m, rev[maxn];
    ll a[maxn], b[maxn];

    void NTT(ll* a, int n, int type){
        for(int i = 0; i < n; i++) if(i < rev[i]) swap(a[i], a[rev[i]]);
        for(int i = 1; i < n; i <<= 1){
            ll gn = qpow(type ? g : gi, (mod - 1) / (i << 1));
            for(int j = 0; j < n; j += (i << 1)){
                ll g0 = 1;
                for(int k = 0; k < i; ++k, g0 = g0 * gn % mod){
                    ll x = a[j + k], y = g0 * a[i + j + k] % mod;
                    a[j + k] = (x + y) % mod;
                    a[i + j + k] = (x - y + mod) % mod;
                }
            }
        }
    }

    // 调用之前输入a, b数组, 更新n, m
    void mul(){
        int len = 1 << max((int)ceil(log2(n + m)), 1);
        for(int i = 0; i < len; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (max((int)ceil(log2(n + m)), 1) - 1));
        NTT(a, len, 1); NTT(b, len, 1);
        for(int i = 0; i <= len; i++) a[i] = a[i] * b[i] % mod;
        NTT(a, len, 0);
        ll inv_len = inv(len);
        for(int i = 0; i <= n + m; i++) a[i] = a[i] * inv_len % mod;
    }
};
