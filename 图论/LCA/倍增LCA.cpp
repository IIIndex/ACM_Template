const int maxn=5e5+100;

vector<int>e[maxn];                                             //存边（加边注意一般是无向图要加两次）

int lg[maxn],depth[maxn];                                       //lg[i]预处理log2(i)+1的值，depth为节点深度

int fa[maxn][20];                                               //fa[i][j]表示节点i的2^j祖先

void init(int n){                                               //预处理log2(i)+1的值
    for(int i=1;i<=n;i++)
        lg[i]=lg[i-1]+(1<<lg[i-1]==i);
}

void dfs(int now,int f){                                        //now当前节点，f当前节点的父亲
    fa[now][0]=f;depth[now]=depth[f]+1;                         //处理深度以及直接父亲
    int len=e[now].size();
    for(int i=1;i<=lg[depth[now]];i++){
        fa[now][i]=fa[fa[now][i-1]][i-1];                       //两次上跳2^(i-1)就得到2^i
    }
    for(int i=0;i<len;i++){
        int v=e[now][i];
        if(!depth[v])dfs(v,now);
    }
}

int lca(int x,int y){
    if(depth[x]>depth[y])swap(x,y);                             //保证y比x深
    while(depth[x]<depth[y]){
        y=fa[y][lg[depth[y]-depth[x]]-1];                       //保证x和y同一深度开始上跳
    }
    if(x==y)return x;
    for(int k=lg[depth[x]]-1;k>=0;k--){
        if(fa[x][k]!=fa[y][k]){x=fa[x][k];y=fa[y][k];}          //保证上跳到x和y的LCA的子节点（避免跳过）
    }
    return fa[y][0];                                            //即为所求
}