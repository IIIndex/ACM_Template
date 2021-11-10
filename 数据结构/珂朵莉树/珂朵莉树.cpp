//维护随机化数据 + 有“推平”操作的数据结构(nlogn)
typedef long long ll;
const int inf = 1e9 + 7;
const int maxn = 1e6 + 100;
const ll mod = 1e9 +7;


struct Node{                                    //表示区间l到r的元素权值都是v
    int l, r;
    mutable ll v;
    Node(int L, int R = -1, ll V = 0): l(L), r(R), v(V) {}
    bool operator<(const Node &oth) const{
        return l < oth.l;
    }
};

set<Node> s;                                    //核心

vector<pair<ll, int>> vec;

set<Node>::iterator split(int pos){             //将含有pos的区间分割成[l, pos - 1]和[pos, r]
    auto it = s.lower_bound(Node(pos));
    if(it != s.end() && it->l == pos) return it;    //如果本来l就是某区间的左端点
    --it;
    if(pos > it->r) return s.end();             //l不包含在最大的区间内
    int L = it->l, R = it->r;
    ll V = it->v;
    s.erase(it);
    s.insert(Node(L, pos - 1, V));
    return s.insert(Node(pos, R, V)).first;     //重新建立两个区间，并返回含l区间的迭代器
    //pair<iterator, bool>
}

void add(int l, int r, ll val = 1){             //对[l, r]内的元素加上val
    split(l);
    auto itr = split(r + 1), itl = split(l);    
    for(; itl != itr; itl++) itl->v += val;
}

void assign(int l, int r, ll val = 0){          //将[l, r]内的元素推平（全部设置成val）
    split(l);
    auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(Node(l, r, val));
}

ll myrank(int l, int r, int k, bool reversed = false){      //寻找[l, r]内的第k大的元素（可重复）
    if(reversed) k = r - l + 2 - k;
    split(l);
    auto itr = split(r + 1), itl = split(l);
    vec.clear();
    for(; itl != itr; itl++) vec.push_back({itl->v, itl->r - itl->l + 1});
    sort(vec.begin(), vec.end());
    for(auto i: vec){
        k -= i.second;
        if(k <= 0) return i.first;
    }
    return -1;
}

ll sum(int l, int r, int x){                        //区间元素x次幂求和
    ll rt = 0;
    split(l);
    auto itr = split(r + 1), itl = split(l);
    vec.clear();
    for(; itl != itr; itl++){
        rt += qpow(itl->v, x) * (ll)(itl->r - itl->l + 1);
        rt %= mod;
    }
    return rt;
}