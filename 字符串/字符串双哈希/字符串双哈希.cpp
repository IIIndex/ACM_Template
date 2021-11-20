typedef long long ll;
const int maxn = 2e3 + 100;

struct Hash{
    const static int M1 = 1572869, M2 = 3145769, B = 129;
    int x1, x2;
    Hash(int x1 = 0, int x2 = 0): x1(x1), x2(x2) {}
    Hash add(char ch){
        return {(x1 * B + ch) % M1, (x2 * B + ch) % M2};
    }
    bool operator==(const Hash& oth) const{
        return (x1 == oth.x1 && x2 == oth.x2);
    }
    bool operator!=(const Hash& oth) const{
        return !(x1 == oth.x1 && x2 == oth.x2);
    }
    Hash operator-(const Hash& oth) const{
        return {(x1 - oth.x1 + M1) % M1, (x2 - oth.x2 + M2) % M2};
    }
    Hash operator*(int y) const{
        return {x1 * y % M1, x2 * y % M2};
    }
    Hash operator*(const Hash& oth) const{
        return Hash((ll)x1 * oth.x1 % M1, (ll)x2 * oth.x2 % M2);
    }
}H[maxn][maxn], V[maxn][maxn], powB[maxn];

void init(){
    Hash cur = {1, 1};
    for(int i = 0; i < maxn; i++){
        powB[i] = cur;
        cur = cur * Hash::B;
    }
}

Hash getHashH(int i, int l, int r){
    return H[i][r] - H[i][l - 1] * powB[r - l + 1];
}

Hash getHashV(int i, int l, int r){
    return V[r][i] - V[l - 1][i] * powB[r - l + 1];
}

int cal(const vector<Hash>& h){
    vector<int> bf(h.size());
    for(int i = 1, j = 0; i < h.size(); i++){
        while(j && h[i] != h[j]) j = bf[j - 1];
        if(h[i] == h[j]) j++;
        bf[i] = j;
    }
    return h.size() - bf.back();
}

string mp[maxn];

void solve(){
    init();
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> mp[i];
        for(int j = 1; j <= n; j++){
            H[i][j] = H[i][j - 1].add(mp[i][j - 1]);
            V[i][j] = V[i - 1][j].add(mp[i][j - 1]);
        }
    }
    while(q--){
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        vector<Hash> HH, VV;
        for(int i = x1; i <= x2; i++) HH.push_back(getHashH(i, y1, y2));
        for(int i = y1; i <= y2; i++) VV.push_back(getHashV(i, x1, x2));
        cout << cal(HH) * cal(VV) << '\n';
    }
}