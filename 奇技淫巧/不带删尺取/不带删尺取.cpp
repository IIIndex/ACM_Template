namespace bakas_trick{
    using T = ll;
    vector<T> vec;
    vector<T> resl;

    // 在merge常数大, 但给出两个判断是否valid常数显著小于merge时使用
    bool valid(const T& a, const T& b){
        /* code here */
    }

    // 是否合法
    bool valid(const T& a){
        /* code here */
    }

    // 合并区间
    // 若T为矩阵, 注意乘法顺序
    T merge(T& a, T& b){
        /* code here */
    }
    
    int solve(){
        // 数据所在范围[1, n], 初始化时记得开大1, 或者利用其它方式给n赋值
        int n = vec.size() - 1;
        int l = 0, r = 0, mid = 0, ans = 0;
        T resr;
        resl.clear(); resl.resize(n + 1);
        // resl[0]设置为非法值
        resl[0] = 1;
        
        while(r < n){
            // 移动右指针
            r++; resr = (r == mid + 1 ? vec[r] : merge(resr, vec[r]));
            // 移动左指针直到合法
            while(l <= mid && !valid(resl[l], resr)) l++;
            // 若越过mid, 则mid移动到r, 左指针从r开始往左更新(不会越过上次的mid)
            if(l > mid){
                mid = r; l = r; resl[l] = vec[l];
                while(l > 1 && valid(resl[l - 1] = merge(vec[l - 1], resl[l]))) l--;
            }
            // 取最长区间, 区间长度为1时特判
            if(r != l || valid(vec[l])) cmax(ans, r - l + 1);
        }
        return ans;
    }
};