/*这个版本的平衡树可能会出现空树的问题，所以说建议初始化时加入一个inf和-inf
  然后对应的rank和atrank也要进行修改*/

const int maxn=2e5+100;

class Splay{
    #define root e[0].ch[1]                                     //根结点
    class node{
        public:
            int val,fa;                                             //val权值，fa父亲结点
            int ch[2];                                              //ch[0]左孩子，ch[1]右孩子，左小右大
            int sum;                                                //记录自己+自己下级一共多少结点
            int recy;                                               //记录自己被重复了几次
    };
    node e[maxn];
    int n,points;                                                   //n节点数，points总数
    void update(int x){                                             //更新结点x的sum值
        e[x].sum=e[e[x].ch[0]].sum+e[e[x].ch[1]].sum+e[x].recy;
    }

    int identify(int x){                                            //获取当前结点是父节点的左/右孩子(0左，1右)
        return e[e[x].fa].ch[0]==x?0:1;
    }

    void connect(int x,int f,int son){                              //建立f和x的父子关系，其中son标记x是f的哪一个儿子
        e[x].fa=f;
        e[f].ch[son]=x;                                             //****这个函数没有抹除x原来的父亲结点和x的关系，只是单方面抹除了x和它父亲结点的关系
    }

    void rotate(int x){
        int y=e[x].fa;
        int myroot=e[y].fa;
        int myrootson=identify(y);
        int yson=identify(x);
        int B=e[x].ch[yson^1];                                      //这里可以同时实现左旋和右旋
        connect(B,y,yson),connect(y,x,(yson^1)),connect(x,myroot,myrootson);
        update(y),update(x);
    }

    void splay(int at,int to){                                      //树的伸展
        to=e[to].fa;
        while(e[at].fa!=to){
            int up=e[at].fa;
            if(e[up].fa==to)rotate(at);
            else if(identify(up)==identify(at)){
                rotate(up);
                rotate(at);
            }
            else{
                rotate(at);
                rotate(at);
            }
        }
    }

    int crepoint(int v,int father){                                 //建立一个新点并写入基本信息，返回新点的编号
        e[++n].val=v;
        e[n].fa=father;
        e[n].sum=e[n].recy=1;
        return n;
    }

    void destory(int x){                                            //完全摧毁一个结点，并将其信息抹去
        e[x].val=e[x].ch[0]=e[x].ch[1]=e[x].sum=e[x].fa=e[x].recy=0;
        if(x==n)n--;
    }

    int find(int v){                                                //查找值为v的点并返回其编号，若没找到返回0
        int now=root;
        while(1){
            if(e[now].val==v){
                splay(now,root);
                return now;
            }
            int next=v<e[now].val?0:1;
            if(!e[now].ch[next])return 0;
            now=e[now].ch[next];
        }
    }

    int build(int v){                                               //内部调用的插入函数（不含splay），返回建立（或增加recy的值）的结点的位置
        points++;
        if(n==0){
            root=1;
            crepoint(v,0);
        }
        else{
            int now=root;
            while(1){
                e[now].sum++;                                       //节点数肯定增加
                if(e[now].val==v){                                  //节点存在直接recy++
                    e[now].recy++;
                    return now;
                }
                int next=v<e[now].val?0:1;
                if(!e[now].ch[next]){                               //节点不存在创建新节点
                    crepoint(v,now);
                    e[now].ch[next]=n;                              //建立父节点到子节点的关系
                    return n;
                }
                now=e[now].ch[next];
            }
        }
        return 0;
    }
public:
    void push(int v){                                               //插入操作，splay操作维持树结构的随机性
        int p=build(v);
        splay(p,root);
    }

    void pop(int v){                                                //对权值为v的点进行删除
        int x=find(v);
        if(!x)return;
        points--;
        if(e[x].recy>1){                                            //该数据重复出现
            e[x].recy--;
            e[x].sum--;
            return;
        }
        if(!e[x].ch[0]){                                            //如果没有左孩子，直接把它的右孩子当成根
            root=e[x].ch[1];
            e[root].fa=0;
        }
        else{                                                       
            int l=e[x].ch[0];
            while(e[l].ch[1])l=e[l].ch[1];
            splay(l,e[x].ch[0]);                                    //将左子树的最大值旋转至左孩子位置
            int r=e[x].ch[1];
            connect(r,l,1),connect(l,0,1);                          //r成为l的右儿子，l成为根
            update(l);
        }
        destory(x);
    }

    int rank(int v){                                                //值为v的元素在树里是第几小(0表示元素不存在)
        find(v);
		return e[e[root].ch[0]].sum+1;
    }

    int atrank(int x){                                              //获取rank为x（第x小）元素的值
        if(x>points)return -inf;
        int now=root;
        while(1){
            int minuse=e[now].sum-e[e[now].ch[1]].sum;
            if(x>e[e[now].ch[0]].sum&&x<=minuse)break;
            if(x<minuse)now=e[now].ch[0];
            else{
                x-=minuse;
                now=e[now].ch[1];
            }
        }
        splay(now,root);
        return e[now].val;
    }

    int upper(int v){                                               //寻找v的后继(大于v且最接近v)
        int now=root;
        int res=inf;
        while(now){
            if(e[now].val>v&&e[now].val<res)res=e[now].val;
            if(v<e[now].val)now=e[now].ch[0];
            else now=e[now].ch[1];
        }
        return res;
    }

    int lower(int v){                                               //寻找v的前驱(小于v且最接近v)
        int now=root;
        int res=-inf;
        while(now){
            if(e[now].val<v&&e[now].val>res)res=e[now].val;
            if(v>e[now].val)now=e[now].ch[1];
            else now=e[now].ch[0];
        }
        return res;
    }

    #undef root
};