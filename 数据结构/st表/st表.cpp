template<typename T>
class st{
public:
    int n;
    T f[__lg(maxn) + 1][maxn];
    // 0 - index
    void init(const vector<T>& a){
        n = a.size();
        int t = __lg(n) + 1;
        for(int i = 0; i < n; i++) f[0][i] = a[i];
        for(int i = 1; i < t; i++) for(int j = 1; j < n; j++){
            if(j + (1 << i) > n) break;
            // 此处函数换为自己的
            f[i][j] = __gcd(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
        }
    }

    T query(int l, int r){
        int pp = __lg(r - l + 1);
        // 此处函数换为自己的
        return __gcd(f[pp][l], f[pp][r - (1 << pp) + 1]);
    }

    void clear(){
        int t = __lg(n) + 1;
        for(int i = 1; i < t; i++) for(int j = 1; j < n; j++){
            if(j + (1 << i) > n) break;
            f[i][j] = __gcd(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
        }
    }
};