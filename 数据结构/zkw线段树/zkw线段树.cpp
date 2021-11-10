const int maxn = 1e6 + 100;

// 使用前记得初始化n
class zkw_sgt{
public:
    struct node{
        int sum, minn, maxx;
        int add;
    }tree[maxn];

    // data - 原始数据，n - 节点个数，m - n的upper_bound
    int data[maxn], n, m;

    zkw_sgt(){};

    void cmin(int& a, const int& b){
        if(a > b) a = b;
    }

    void cmax(int& a, const int& b){
        if(a < b) a = b;
    }

    void build(){
        // 初始化m
        for(m = 1; m <= n; m <<= 1);
        // 初始化叶节点
        for(int i = 1; i <= n; i++)
            tree[i + m] = {data[i], data[i], data[i], 0};
        
        //初始化非叶节点
        for(int i = m - 1; i >= 1; i--){
            tree[i].sum = tree[i << 1].sum + tree[i << 1 | 1].sum;

            tree[i].maxx = max(tree[i << 1].maxx, tree[i << 1 | 1].maxx);
            tree[i << 1].maxx -= tree[i].maxx; tree[i << 1 | 1].maxx -= tree[i].maxx;

            tree[i].minn = min(tree[i << 1].minn, tree[i << 1 | 1].minn);
            tree[i << 1].minn -= tree[i].minn; tree[i << 1 | 1].minn -= tree[i].minn;
        }
    }

    void update_node(int pos, int v, int A = 0){
        // 直接对叶节点更新
        pos += m; tree[pos].minn += v; tree[pos].maxx += v;
        for(; pos > 1; pos >>= 1){
            // 一路更新回根节点
            tree[pos].sum += v;

            A = min(tree[pos].minn, tree[pos ^ 1].minn);
            tree[pos].minn -= A; tree[pos ^ 1].minn -= A; tree[pos >> 1].minn += A;

            A = max(tree[pos].maxx, tree[pos ^ 1].maxx);
            tree[pos].maxx -= A; tree[pos ^ 1].maxx -= A; tree[pos >> 1].maxx += A;
        }
    }

    void update_part(int l, int r, int v){
        // lc、rc是l和r两个节点下辖的更新区间长度
        int A = 0, lc = 0, rc = 0, len = 1;
        // l和r同为某个点的两个儿子时结束
        for(l += m - 1, r += m + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1){
            // 是左节点，对右节点完全更新
            if(l & 1 ^ 1){
                tree[l ^ 1].add += v;
                tree[l ^ 1].minn += v; tree[l ^ 1].maxx += v;
                lc += len;
            }
            // 是右节点，对左节点完全更新
            if(r & 1){
                tree[r ^ 1].add += v;
                tree[r ^ 1].minn += v; tree[r ^ 1].maxx += v;
                rc += len;
            }

            // 更新父节点的sum、min、max
            tree[l >> 1].sum += v * lc; tree[r >> 1].sum += v * rc;

            A = min(tree[l].minn, tree[l ^ 1].minn);
            tree[l].minn -= A; tree[l ^ 1].minn -= A; tree[l >> 1].minn += A;
            A = min(tree[r].minn, tree[r ^ 1].minn);
            tree[r].minn -= A; tree[r ^ 1].minn -= A; tree[r >> 1].minn += A;

            A = max(tree[l].maxx, tree[l ^ 1].maxx);
            tree[l].maxx -= A; tree[l ^ 1].maxx -= A; tree[l >> 1].maxx += A;
            A = max(tree[r].maxx, tree[r ^ 1].maxx);
            tree[r].maxx -= A; tree[r ^ 1].maxx -= A; tree[r >> 1].maxx += A;
        }

        // 两节点汇合，一路更新回根节点
        for(lc += rc; l > 1; l >>= 1){
            tree[l >> 1].sum += v * lc;

            A = min(tree[l].minn, tree[l ^ 1].minn);
            tree[l].minn -= A; tree[l ^ 1].minn -= A; tree[l >> 1].minn += A;

            A = max(tree[l].maxx, tree[l ^ 1].maxx);
            tree[l].maxx -= A; tree[l ^ 1].maxx -= A; tree[l >> 1].maxx += A;
        }
    }

    int query_node(int pos){
        int ans = 0;
        // 一路加和回根节点
        for(pos += m; pos; pos >>= 1) ans += tree[pos].maxx;
        return ans;
    }

    int query_sum(int l, int r){
        int ans = 0, lc = 0, rc = 0, len = 1;
        // 开区间求和
        for(l += m - 1, r += m + 1; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1){
            // 是左节点，故右节点全在区间内
            if(l & 1 ^ 1) ans += tree[l ^ 1].sum + len * tree[l ^ 1].add, lc += len;
            // 是右节点，故左节点全在区间内
            if(r & 1) ans += tree[r ^ 1].sum + len * tree[r ^ 1].add, rc += len;
            // lazy tag加和
            ans += tree[l >> 1].add * lc;
            ans += tree[r >> 1].add * rc;
        }
        // 处理直至根节点的lazy tag
        for(lc += rc, l >>= 1; l; l >>= 1)
            ans += tree[l].add * lc;
        return ans;
    }

    // 和query_max类似
    int query_min(int l, int r){
        if(l == r) return query_node(l);
        int L = 0, R = 0, ans = 0;
        for(l += m, r += m; l ^ r ^ 1; l >>= 1, r >>= 1){
            L += tree[l].minn; R += tree[r].minn;
            if(l & 1 ^ 1) cmin(L, tree[l ^ 1].minn);
            if(r & 1) cmin(R, tree[r ^ 1].minn);
        }
        L += tree[l].minn; R += tree[r].minn;
        for(ans = min(L, R), l >>= 1; l; l >>= 1) ans += tree[l].minn;
        return ans;
    }

    int query_max(int l, int r){
        // l == r时避免l和r不是相邻节点进入死循环
        if(l == r) return query_node(l);
        int L = 0, R = 0, ans = 0;
        // l和r不置为开区间，避免受到其它影响
        for(l += m, r += m; l ^ r ^ 1; l >>= 1, r >>= 1){
            // 一路累加
            L += tree[l].maxx; R += tree[r].maxx;
            // 是左节点，故右节点全部处于区间内
            if(l & 1 ^ 1) cmax(L, tree[l ^ 1].maxx);
            // 是右节点，故左节点全部处于区间内
            if(r & 1) cmax(R, tree[r ^ 1].maxx);
        }
        // 加入当前权值
        L += tree[l].maxx; R += tree[r].maxx;
        // 直到回到根节点
        for(ans = max(L, R), l >>= 1; l; l >>= 1) ans += tree[l].maxx;
        return ans;
    }

};