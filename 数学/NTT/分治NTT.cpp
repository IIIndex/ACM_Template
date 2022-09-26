// 分治NTT可以以nlog^2n用于求解以下形式的f数组
// f_i = \sigma_{j = 1}^{i} f_{i - j} \times g_{j}
// f[0]要求已知
// 多组数据clear时将F / G数组清零
namespace NTT{
    // 998244353 - 1 = 2 ^ 23 * 119
    // g为998244353的原根，gi为g在模998244353意义下的逆元
    constexpr int maxn = (1 << 22) + 100, g = 3, gi = 332748118, mod = 998244353;
    // n为a数组长度(0 ~ n)，m为b数组长度(0 ~ m)rev[i]为i的二进制翻转
    int n, m, rev[maxn];
    // a, b为ntt暂存数组, f为待求数组, g为已知数组
    ll a[maxn], b[maxn], F[maxn], G[maxn];

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

    // f_i = \sigma_{j = 1}^{i} f_{i - j} \times g_{j}
    // f[0] = 1
    void CDQ_mul(int l, int r){
        if(l == r) {
            // 特殊情况处理
            if(!l) F[l] = 1;
            return;
        }

        int mid = (l + r) >> 1, lena = mid - l + 1, lenb = r - l;
        int bit = 0;
        while(1 << bit < lena + lenb) ++bit;

        CDQ_mul(l, mid);

        for(int i = 0; i < (1 << bit); i++) a[i] = (i < lena ? F[i + l] : 0);
        for(int i = 0; i < (1 << bit); i++) b[i] = (i < lenb ? G[i + 1] : 0);

        for(int i = 0; i < (1 << bit); i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (max(bit, 1) - 1));
        
        NTT(a, (1 << bit), 1); NTT(b, (1 << bit), 1);
        for(int i = 0; i <= (1 << bit); i++) a[i] = a[i] * b[i] % mod;
        NTT(a, (1 << bit), 0);
        ll inv_len = inv(1 << bit);
        for(int i = 0; i <= (1 << bit); i++) a[i] = a[i] * inv_len % mod;

        for (int i = mid + 1; i <= r; i++) add(F[i], a[i - l - 1]); 
        CDQ_mul(mid + 1, r);
    }
};