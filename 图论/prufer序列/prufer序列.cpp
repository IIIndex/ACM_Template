//prufer序列, 父亲节点, 点的度数
int prufer[maxn], fa[maxn], degree[maxn];

//根据父亲序列生成prufer
void faToPrufer(int n){
    //初始化度数
    for(int i = 1; i <= n - 1; i++){
        degree[i]++; degree[fa[i]]++;
    }
    degree[n]++;
    //线性选取当前最小叶子节点
    int p = 1;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 1){
            p = i;
            break;
        }
    int leaf = p, cnt = 0;
    while(cnt < n - 2){
        int ff = fa[leaf];
        prufer[++cnt] = ff;
        degree[ff]--;
        //父亲变成叶子, 回跳并不改变p
        if(degree[ff] == 1 && ff < p) leaf = ff;
        else{
            p++;
            //找到下一个编号最小的叶子节点
            while(degree[p] != 1) p++;
            leaf = p;
        }
    }
}

//根据prufer序列重构树
void pruferToFa(int n){
    //初始化度数
    for(int i = 1; i <= n - 2; i++){
        degree[i]++; degree[prufer[i]]++;
    }
    degree[n - 1]++; degree[n]++;
    //线性选取当前最小叶子节点
    int p = 1;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 1){
            p = i;
            break;
        }
    int leaf = p, cnt = 0;
    while(cnt < n - 2){
        int ff = prufer[++cnt];
        fa[leaf] = ff;
        degree[ff]--;
        //父亲变成叶子, 回跳并不改变p
        if(degree[ff] == 1 && ff < p) leaf = ff;
        else{
            p++;
            //找到下一个编号最小的叶子节点
            while(degree[p] != 1) p++;
            leaf = p;
        }
    }
    //最后剩下一个叶子节点和编号最大的结点
    fa[leaf] = n;
}