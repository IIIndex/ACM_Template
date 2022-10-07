// phi[i]表示\sum_{j = 1}^{i - 1} gcd(i, j) == 1
// 即比i小且和i互质的数的个数
int phi[maxn];
vector<int> prime, np;

void init(){
    np.resize(maxn);
    phi[1] = 1;
    for(int i = 2; i < maxn; i++){
        if(!np[i]) {prime.push_back(i); phi[i] = i - 1;}
        for(auto v: prime){
            if(v * i >= maxn) break;
            np[v * i] = 1;
            if(i % v == 0) {phi[i * v] = phi[i] * v; break;}
            else phi[i * v] = phi[i] * phi[v];
        }
    }
}