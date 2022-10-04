// exgcd(a, b)能找到 ax + by = gcd(a, b)的一组特解
pair<ll, ll> exgcd(ll a,ll b){
    if(b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a % b);
    ll tmp = x;
    x = y;
    y = tmp - a / b * y;
    return {x, y};
}

//记住最后得到的x需要进行x=(x%b+b)%b才是最小整数解