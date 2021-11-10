    const int maxn = 2e5 + 100;

    const int rt = 1;                           //Trie树入口
    int cnt = 1;                                //记录节点个数

    int ind[maxn], mp[maxn], vis[maxn];         //ind，fail指针图入度，为拓扑优化做准备
                                                //mp[i]为第i个字串在vis中存储的位置
                                                //vis[mp[i]]表示第i个字串出现的次数

    struct node{
        int son[26];                            //对应26个小写字母，可更改
        int fail, flag, ans;                    //fail：失配指针，flag：第一个在该点完结的模式串
    }Trie[maxn];                                //ans：访问该点的次数

    void insert(string &str,int num){           //向Trie树插入新字串
        int now = rt, len =str.length();
        for(int i = 0; i < len; i++){
            int s = str[i] - 'a';               //若不为全小写字母，则此处要更改
            if(!Trie[now].son[s]){
                Trie[now].son[s] = ++cnt;       //新建儿子
            }
            now = Trie[now].son[s];
        }
        if(!Trie[now].flag)Trie[now].flag = num;    //第一次在该节点完结的字串编号
        mp[num] = Trie[now].flag;               //建立对应关系
    }

    void getFail(){
        for(int i = 0; i <26; i++){             //使虚节点'0'所有子节点指向根节点1
            Trie[0].son[i] = 1;
        }
        queue<int> q;
        q.push(rt);                             //bfs
        while(!q.empty()){
            int u = q.front();
            q.pop();
            int Fail = Trie[u].fail;
            for(int i = 0; i < 26; i++){
                int v = Trie[u].son[i];
                if(!v){
                    Trie[u].son[i] = Trie[Fail].son[i]; //没有该子节点直接使用父节点fail指针
                    continue;
                }
                Trie[v].fail = Trie[Fail].son[i];   //指向父节点fail指针的对于儿子
                ind[Trie[v].fail]++;                //为求得次数的拓扑优化做准备
                q.push(v);
            }
        }
    }

    void topo(){
        queue<int> q;
        for(int i = 1; i <= cnt; i++){
            if(!ind[i])q.push(i);
        }
        while(!q.empty()){
            int u = q.front();
            q.pop();
            vis[Trie[u].flag] = Trie[u].ans;        //答案直接存入对应的vis数组中
            int v = Trie[u].fail;
            Trie[v].ans += Trie[u].ans;             //对应的直接fail指针加上相应的访问次数
            ind[v]--;
            if(!ind[v])q.push(v);                   //fail指针构成的图存在拓扑序
        }
    }

    void query(string &str){
        int len = str.length();
        int now = rt;
        for(int i = 0; i < len; i++){
            int s = str[i] - 'a';
            now = Trie[now].son[s];                 //不存在的节点已经直接构造过对应的指针
            Trie[now].ans++;
        }
    }

    void solve(){
        memset(Trie, 0, sizeof(Trie));              //Trie树清空
        cnt = 1;                                    //重置编号
        int n;
        cin>>n;
        string str;
        for(int i = 0; i < n; i++){
            cin>>str;
            insert(str, i + 1);                     //先插入模式串
        }
        getFail();                                  //构建fail指针
        cin>>str;
        query(str);                                 //存入文本串的初始信息
        topo();                                     //拓扑优化统计答案
        for(int i = 1; i <= n; i++){
            cout<<vis[mp[i]]<<'\n';
        }
    }