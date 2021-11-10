//对于一个多项式C, 当C[i] == A[j] * B[k](j(或、与、异或)k == i)时
//FWT(C) = FWT(A) * FWT(B);
//因此我们可以利用IFWT(FWT(A) * FWT(B))得到C
//在FWT_XOR的版本中，如果没有模数的需求，可以利用double数组除二来解决

const int mod = 998244353;

int n, inv2;                                //inv2是2在模mod意义下的逆元

void FWT_OR(ll *a, int opt){                //opt为1表示正向FWT，opt为-1表示逆向FWT（IFWT）
    for(int i = 1; i < n; i <<= 1)
        for(int p = i << 1, j = 0; j < n; j += p)
            for(int k = 0; k < i; k++)
                if(opt == 1)a[i + j + k] = (a[j + k] + a[i + j + k]) % mod;
                else a[i + j + k] = (a[i + j + k] + mod - a[j + k]) % mod;
}

void FWT_AND(ll *a, int opt){               //opt为1表示正向FWT，opt为-1表示逆向FWT（IFWT）
    for(int i = 1; i < n; i <<= 1)
        for(int p = i << 1, j = 0; j < n; j += p)
            for(int k = 0; k < i; k++)
                if(opt == 1)a[j + k] = (a[j + k] + a[i + j + k]) % mod;
                else a[j + k] = (a[j + k] + mod - a[i + j + k]) % mod;
}

void FWT_XOR(ll *a, int opt){               //opt为1表示正向FWT，opt为-1表示逆向FWT（IFWT）
    for(int i = 1; i < n; i <<= 1)
        for(int p = i << 1, j = 0; j < n; j += p)
            for(int k = 0; k < i; k++){
                int X = a[j + k], Y = a[i + j + k];
                a[j + k] = (X + Y) % mod;
                a[i + j + k] = (X + mod - Y) % mod;
                if(opt == -1){
                    a[j + k] = 1ll * a[j + k] * inv2 % mod;
                    a[i + j + k] = 1ll * a[i + j + k] * inv2 % mod;
                }
            }
}