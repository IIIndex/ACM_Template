//对于某个集合S, f[S] = \sigma f[T], T ⊆ S
//也就是说, f[S]代表着S及其所有子集的权值之和

void SOSdp(){
    //val - 初始权值
    for(int i = 0; i < n; i++) f[i] = val[i];
    // m为二进制位数最大值, n = 1 << m
    for(int i = 0; i < m; i++){
        for(int mask = 0; mask < n; mask++){
            if(mask & 1 << i) f[mask] += f[mask ^ (1 << i)];
        }
    }
}

