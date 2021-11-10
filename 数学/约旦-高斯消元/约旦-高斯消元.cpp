const int maxn = 200;
const double eps = 1e-5;
double A[maxn][maxn];

int Gauss(int n){
    for(int i = 1; i <= n; i++){
        int maxx = i;
        for(int j = i + 1; j <= n; j++){                            //选择当前这列最大的行
            if(fabs(A[maxx][i]) < fabs(A[j][i]))maxx = j;
        }
        for(int j = 1; j <= n + 1; j++)swap(A[i][j], A[maxx][j]);   //将列系数最大的行交换至当前行
        if(fabs(A[i][i]) < eps)return false;                        //无解或多解
        for(int j = 1; j <= n; j++){
            if(j == i)continue;
            double rate = A[j][i] / A[i][i];
            for(int k = i; k <= n + 1; k++){                        //其他行的当前列消元
                A[j][k] -= rate * A[i][k];
            }
        }
    }
    for(int i = 1; i <= n; i++){                                    //系数规范化
        A[i][n + 1] /= A[i][i];
        A[i][i] = 1.0;
    }
    return true;
}