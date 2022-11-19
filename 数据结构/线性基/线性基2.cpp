namespace LinerBase{
    using T = ll;
    vector<T> B;
    // 线性基能否表示0
    bool flag = false;

    // 添加元素
    void insert(T x){
        for(auto b: B) cmin(x, b ^ x);
        for(auto& b: B) cmin(b, b ^ x);
        if(x) B.push_back(x);
        else flag = true;
    }

    // x是否能被线性基表示出来
    bool check(T x){
        for(auto b: B) cmin(x, b ^ x);
        if(x) return false;
        return true;
    }

    // 查询最大值
    T qry_max(){
        T rt = 0;
        for(auto b: B) rt ^= b;
        return rt;
    }

    // 查询最小值
    T qry_min(){
        if(flag) return 0;
        return *min_element(B.begin(), B.end());
    }

    // 查询第k小的数
    T qry_kth(T k){
        sort(B.begin(), B.end());
        ull ans = 0;
        if (flag) k--;
        for (auto b : B) {
            if(k & 1) ans ^= b;
            k >>= 1;
        }
        if(k == 0) return ans;
        else return -1;
    }

    void clear(){
        flag = false;
        B.clear();
    }
}