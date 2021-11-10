int p[maxn],q[maxn];                                          //p是队列，q是辅助（记录队列元素的位置），要开全局变量以免爆栈

void Monotone_Queue_Upper(int *sour,int k,int len){           //sour:数组起始点,k:窗口长度,len:数组长度
    int head=1,tail=0;
    for(int i=1;i<=len;i++){
        while(head<=tail&&sour[i]>p[tail]){                   //这里是求区间最大值，如果要求最小值改变一下符号即可（记住不能加等号）
            tail--;
        }
        p[++tail]=sour[i];
        q[tail]=i;
        while(head<=tail&&q[head]+k<=i){
            head++;
        }
        if(i>=k){
            cout<<p[head]<<" ";
        }
    }
}

void Monotone_Queue_Lower(int *sour,int k,int len){           //sour:数组起始点,k:窗口长度,len:数组长度
    int head=1,tail=0;
    for(int i=1;i<=len;i++){
        while(head<=tail&&sour[i]<p[tail]){                  //这里是求区间最小值，如果要求最小值改变一下符号即可（记住不能加等号）
            tail--;
        }
        p[++tail]=sour[i];
        q[tail]=i;
        while(head<=tail&&q[head]+k<=i){
            head++;
        }
        if(i>=k){
            cout<<p[head]<<" ";
        }
    }
}