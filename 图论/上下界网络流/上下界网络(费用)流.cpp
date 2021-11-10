/********本篇的flow()函数基于Dinic模板***********/
void solve(){
    int s1,t1;                  //s1,t1为原图的源点/汇点
    cin>>n>>m>>s1>>t1;
    s=n+1,t=n+2;                //新建源点/汇点
    n+=2;
    for(int i=0;i<m;i++){
        int u,v,w1,w2;          //w1流量下界，w2流量上界，直接在残差网络上建图
        cin>>u>>v>>w1>>w2;
        add(u,v,w2-w1);
        d[u]-=w1;               //更新下界网络每个结点的出入度（下界网络+部分残差网络出入度均衡）
        d[v]+=w1;
    }

    add(t1,s1,inf);             //汇点连向源点（转化成无源汇上下界可行流）

    for(int i=0;i<=n;i++){      //保持出入度均衡
        if(d[i]>0){
            add(s,i,d[i]);      
        }
        else if(d[i]<0){
            add(i,t,-d[i]);
        }
    }

    flow();                     //用新的源点/汇点跑一次网络流

    for(int i=head[s];i;i=e[i].next){   //某个出入度均衡边未跑满说明不存在可行流
        if(e[i].val){
            cout<<"please go home to sleep"<<endl;
            return;
        }
    }

    s=s1,t=t1,n-=2;             //在剩余网络上再跑一遍网络最大流得到有源汇上下界最大流
                                //如果要跑有源汇上下界最小流的话，s和t交换即可

    int ans=0;
    for(int i=head[t];i;i=e[i].next){   //删除源点和汇点的连边，并得到之前源点和汇点的流量
        if(e[i].to=s){
            ans=e[i^1].val;
            e[i].val=0;
            e[i^1].val=0;
            break;
        }
    }

    cout<<ans+flow()<<endl;     //将残余网络榨干
}


//上下界最小费用**可行**流原理相同，首先把附加边的费用置为0，然后将下界网络满流的费用求和，
//再加上在残差网络上跑的MCMF的最小费用即为所求