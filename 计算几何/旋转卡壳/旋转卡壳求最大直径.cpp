//旋转卡壳求最大直径
//因为旋转卡壳前一般要求凸包，故此处函数和结构体定义与Graham法求凸包相同
db RotateCalipers(Node *a,int n){									//a为凸包点集，n为点总数（从下标1开始存）
	db ans=-inf;													//ans表示最长边
	int q=2;														//从第二个点算起（第一个点已经排在最后）
	a[n+1]=a[1];
	for(int i=1;i<=n;i++){
		while(Cross(a[q],a[i+1],a[i],a[i+1])<Cross(a[q+1],a[i+1],a[i],a[i+1])){q++;if(q>n)q-=n;}
		ans=max(ans,max(dis(a[q],a[i]),dis(a[q+1],a[i+1])));		//while循环旋转，max判断最长边
	}
	return ans;
}