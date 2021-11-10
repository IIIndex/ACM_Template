const int maxn = 3e6 + 100;
const int rt = 1;           //trie树入口
int cnt = 1;                //子节点由2开始存

struct node{
    int l, r;               //l表示0，r表示1
}P[maxn];

void add(int x){
    int p = rt;
    int now = 1 << 30;              //此处和下一排30根据数据大小决定
    for(int i = 30; i>= 0; i--){   
        if(x & now){                //此位为1
            if(!P[p].r){            //不存在便新加节点
                P[p].r = ++cnt;
            }
            p = P[p].r;             //进入下一层
        }
        else{                       //此位为0
            if(!P[p].l){
                P[p].l = ++cnt;
            }
            p = P[p].l;
        }
        now >>= 1;
    }
}

int find_max(int x){                //如果是找最小值，只需要更改l/r的寻路逻辑
    int p = rt;                     //从入口进入
    int max = 0;
    int now = 1 << 30;              //此处30同上
    for(int i = 30; i >= 0; i--){
        max <<= 1;                  //字典树是从高到低位存储的（保证树深度）
        if(x & now){
            if(P[p].l){             //能让此位为1
                max++;
                p = P[p].l;
            }
            else{                   //不能让此位为1
                p = P[p].r;
            }
        }
        else{
            if(P[p].r){             //同上
                max++;
                p = P[p].r;
            }
            else{
                p = P[p].l;
            }
        }
        now >>= 1;
    }
    return max;
}