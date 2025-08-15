class Splay{
    static constexpr int MAXN = 2e5 + 100;
    #define root e[0].ch[1]

    struct Node{
        // val权值, fa父亲结点
        int val, fa;
        // ch[0]左孩子, ch[1]右孩子, 左小右大
        int ch[2];
        // siz子树大小, rep 自身重复次数
        int siz, rep;
    } e[MAXN];

    // cnt内存池变量, points树大小
    int cnt, points;

    // 更新节点siz
    void update(int x) {
        e[x].siz = e[e[x].ch[0]].siz + e[e[x].ch[1]].siz + e[x].rep;
    }

    // 获取当前结点是父节点的左 / 右孩子 (0左, 1右)
    int identify(int x) {
        return e[e[x].fa].ch[0] == x ? 0 : 1;
    }

    // 将x至于f的id儿子处
    // 该函数没有抹除x原来的父亲结点和x的关系
    void connect(int x, int f, int id) {
        e[x].fa = f;
        e[f].ch[id] = x;
    }

    void rotate(int x) {
        auto y = e[x].fa;
        auto z = e[y].fa;
        auto zson = identify(y);
        auto yson = identify(x);
        auto B = e[x].ch[yson ^ 1];
        // 这里可以同时实现左旋和右旋
        connect(B,y,yson); connect(y,x,(yson^1)); connect(x, z, zson);
        update(y); update(x);
    }

    void splay(int at,int to) {
        to = e[to].fa;
        while (e[at].fa != to) {
            auto up = e[at].fa;
            if (e[up].fa == to) rotate(at);
            else if (identify(up) == identify(at)) { rotate(up); rotate(at); }
            else{ rotate(at); rotate(at); }
        }
    }

    // 建立一个新点并写入基本信息, 返回新点的编号
    int create(int v, int fa) {
        e[++cnt].val = v;
        e[cnt].fa = fa;
        e[cnt].siz = e[cnt].rep = 1;
        return cnt;
    }

    // 摧毁一个结点
    void destory(int x){
        e[x].val = e[x].ch[0] = e[x].ch[1] = e[x].siz = e[x].fa = e[x].rep = 0;
    }

    // 查找值为v的点并返回其编号, 若没找到返回0
    int find(int v){
        auto now = root;
        while (1) {
            if (e[now].val == v) {
                splay(now, root);
                return now;
            }
            int nxt = v > e[now].val;
            if (!e[now].ch[nxt]) return 0;
            now = e[now].ch[nxt];
        }
        return 0;
    }

    // 内部调用的插入函数(不含splay), 返回建立(或增加rep的值)的结点的位置
    int build(int v) {
        points++;
        if(cnt == 0) {
            root = 1;
            create(v, 0);
        }
        else {
            auto now = root;
            while (1) {
                e[now].siz++;
                if (e[now].val == v) {
                    e[now].rep++;
                    return now;
                }
                int nxt = v > e[now].val;
                if(!e[now].ch[nxt]) {
                    create(v, now);
                    e[now].ch[nxt] = cnt;
                    return cnt;
                }
                now = e[now].ch[nxt];
            }
        }
        return 0;
    }
public:
    // 插入v
    void push(int v) {
        int p = build(v);
        splay(p, root);
    }

    // 删除v
    void pop(int v) {
        int x = find(v);
        if (!x) return;
        points--;
        if(e[x].rep > 1) {
            e[x].rep--; e[x].siz--;
            return;
        }
        // 该节点需要被删除的后处理
        // 无左孩子
        if (!e[x].ch[0]) {
            root = e[x].ch[1];
            e[root].fa = 0;
        }
        else {                                                       
            int l = e[x].ch[0];
            while (e[l].ch[1]) l = e[l].ch[1];
            splay(l, e[x].ch[0]);
            int r = e[x].ch[1];
            //r成为l的右儿子，l成为根
            connect(r, l, 1); connect(l, 0, 1);
            update(l);
        }
        destory(x);
    }

    // v是第几小(1 - index)
    int rank(int v) {
        find(v);
		return e[e[root].ch[0]].siz + 1;
    }

    // 获取rank为x元素的值(1 - index)
    int atrank(int x) {
        if (x > points) return -inf;
        int now = root;
        while (1) {
            int lsiz = e[now].siz - e[e[now].ch[1]].siz;
            if (x > e[e[now].ch[0]].siz && x <= lsiz) break;
            if (x < lsiz) now = e[now].ch[0];
            else {
                x -= lsiz;
                now = e[now].ch[1];
            }
        }
        splay(now, root);
        return e[now].val;
    }

    // v的后继, inf代表不存在
    int upper(int v) {
        int now = root;
        int res = inf;
        while (now) {
            if (e[now].val > v && e[now].val < res) res = e[now].val;
            if (v < e[now].val) now = e[now].ch[0];
            else now=e[now].ch[1];
        }
        return res;
    }

    // v的前驱, -inf代表不存在
    int lower(int v) {
        int now = root;
        int res = -inf;
        while (now) {
            if (e[now].val < v && e[now].val > res) res = e[now].val;
            if (v > e[now].val) now = e[now].ch[1];
            else now = e[now].ch[0];
        }
        return res;
    }

    #undef root
};