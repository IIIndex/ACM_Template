namespace presistent_sgt{
    // 节点最大数量(4e7会超过256MB)
    constexpr int maxv = 4e7 + 100;

    #define val(x) tree[x].val
    #define lc(x)  tree[x].lc
    #define rc(x) tree[x].rc

    // 此处tree其实可以使用vector动态开点
    struct t{
        int lc, rc, val;
    }tree[maxv];

    // top: 已存在的节点最大编号, n: 数组长度
    // 数组下标index: 0 ~ n - 1
    int top = 0, n= 0;
    // a: 原数组, root[i]: 存储第i个版本的根节点
    vector<int> a, root;
    
    int clone(int p){
        tree[++top] = tree[p];
        return top;
    }

    // 建树
    int build(int cl = 0, int cr = n - 1){
        int p = ++top;
        if(cl == cr) {val(p) = a[cl]; return p;}
        int mid = (cl + cr) / 2;
        lc(p) = build(cl, mid);
        rc(p) = build(mid + 1, cr);
        return p;
    }

    // 单点更新
    int update(int p, int pos, int val, int cl = 0, int cr = n - 1){
        p = clone(p);
        if(cl == cr) {val(p) = val; return p;}
        int mid = (cl + cr) / 2;
        if(pos <= mid) lc(p) = update(lc(p), pos, val, cl, mid);
        else rc(p) = update(rc(p), pos, val, mid + 1, cr);
        return p;
    }

    // 单点查询
    int query(int p, int pos, int cl = 0, int cr = n - 1){
        if(cl == cr) return val(p);
        int mid = (cl + cr) / 2;
        if(pos <= mid) return query(lc(p), pos, cl, mid);
        else return query(rc(p), pos, mid + 1, cr);
    }
};