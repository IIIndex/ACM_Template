struct BIT{
    int tree[maxn];
    vector<pair<int, int>> op;

    void update(int p, int x){
        op.emplace_back(p, -x);
        while(p < maxn) {
            tree[p] += x;
            p += lowbit(p);
        }
    }

    int qry(int p){
        int rt = 0;
        while(p) rt += tree[p], p -= lowbit(p);
        return rt;
    }

    void clear(){
        for(auto [p, x]: op) update(p, x);
        op.clear();
    }
};