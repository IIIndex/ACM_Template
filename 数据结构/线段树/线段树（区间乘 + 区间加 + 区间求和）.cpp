// 记住要初始化N
int N;

class sgt{
public:
    struct tree{
        ll ad {0};
        ll mu {1};
        ll sum {0};
    };
    tree t[maxn << 2];

    void push_down(int p, int len){
        int lc = p << 1, rc = lc | 1;
        if(t[p].mu != 1){
            t[lc].sum *= t[p].mu; t[lc].sum %= mod;
            t[lc].mu *= t[p].mu; t[lc].mu %= mod;
            t[lc].ad *= t[p].mu; t[lc].ad %= mod;

            t[rc].sum *= t[p].mu; t[rc].sum %= mod;
            t[rc].mu *= t[p].mu; t[rc].mu %= mod;
            t[rc].ad *= t[p].mu; t[rc].ad %= mod;
            t[p].mu = 1;
        }
        if(t[p].ad){
            add(t[lc].sum, 1ll * (len + 1) / 2 * t[p].ad);
            add(t[lc].ad, t[p].ad);
            add(t[rc].sum, 1ll * len / 2 * t[p].ad);
            add(t[rc].ad, t[p].ad);
            t[p].ad = 0;
        }
    }

    ll query(int l, int r, int p = 1, int cl = 0, int cr = N){
        if(l > cr || r < cl) return 0;
        if(l <= cl && r >= cr) return t[p].sum;
        push_down(p, cr - cl + 1);
        int lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        return (query(l, r, lc, cl, mid) + query(l, r, rc, mid + 1, cr)) % mod;
    }
    // 左端点，右端点，乘数（无置为1），加数（无置为0）
    void update(int l, int r, ll m, ll a, int p = 1, int cl = 0, int cr = N){
        if(cl > r || cr < l) return;
        if(cl >= l && cr <= r){
            if(m != 1){
                t[p].sum *= m; t[p].sum %= mod;
                t[p].mu *= m; t[p].mu %= mod;
                t[p].ad *= m; t[p].ad %= mod;
            }
            if(a){
                t[p].sum += 1ll * (cr - cl + 1) * a;
                add(t[p].ad, a);
            }
            return;
        }
        push_down(p, cr - cl + 1);
        int lc = p << 1, rc = lc | 1, mid = (cl + cr) >> 1;
        update(l, r, m, a, lc, cl, mid); update(l, r, m, a, rc, mid + 1, cr);
        t[p].sum = (t[lc].sum + t[rc].sum) % mod;
    }

    void clear(){
        int maxx = N << 2;
        for(int i = 0; i < maxx; i++) t[i].ad = t[i].sum = 0, t[i].mu = 1;
    }
};