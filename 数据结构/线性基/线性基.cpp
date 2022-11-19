namespace LinerBase{
    constexpr int maxn = 62;
    using T = ll;
    T a[maxn + 1], tmp[maxn + 1];
    // 线性基能否表示0
    bool flag = false;

    // 添加元素
    void insert(T x){
        for(int i = maxn; i >= 0; i--){
            if((x >> i) & 1){
                if(!a[i]) {a[i] = x; return;}
                x ^= a[i];
            }
        }
        flag = true;
    }

    // x是否能被线性基表示出来
    bool check(T x){
        for(int i = maxn; i >= 0; i--){
            if((x >> i) & 1){
                if(!a[i]) return false;
                x ^= a[i];
            }
        }
        return true;
    }

    // 查询最大值
    T qry_max(){
        T rt = 0;
        for(int i = maxn; i >= 0; i--) cmax(rt, rt ^ a[i]);
        return rt;
    }

    // 查询最小值
    T qry_min(){
        if(flag) return 0;
        for(int i = 0; i <= maxn; i++) if(a[i]) return a[i];
        // 线性基为空
        return -1;
    }

    // 查询第k小的数
    T qry_kth(T k){
        T rt = 0;
        int cnt = 0;
        k -= flag; if(!k) return 0;
        for(int i = 0; i <= maxn; i++){
            for(int j = i - 1; j >= 0; j--){
                if((a[i] >> j) & 1) a[i] ^= a[j];
            }
            if(a[i]) tmp[cnt++] = a[i];
        }
        if(k >= (1ull << cnt)) return -1;
        for(int i = 0; i <= maxn; i++) if((k >> i) & 1) rt ^= tmp[i];
        return rt;
    }

    void clear(){
        flag = 0;
        memset(a, 0, sizeof(a));
    }
}