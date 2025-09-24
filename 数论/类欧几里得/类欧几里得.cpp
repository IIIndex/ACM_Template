// \sum_{i = 0}^{n} floor((ai + b) / c)
// O(log min{a, b, m})
ll floor_sum(ll a, ll b, ll c, ll n) {
    // find k where x - km \in [0, m)
    auto upper_zero = [&](ll x, ll m) {
        return x / m - (x < 0 && x % m);
    };

    auto na = upper_zero(a, c), nb = upper_zero(b, c);
    a -= na * c; b -= nb * c;
    ll res = na * n * (n + 1) / 2 + nb * (n + 1);

    // then 0 <= a, b < c
    if (!a || n < 0) return res;

    // let m = floor((an + b) / c)
    // \sum_{i = 0}^{n} floor((ai + b) / c)
    // = \sum_{i = 0}^{n} \sum_{j = 0}^{m - 1} [j < floor((ai + b) / c)]
    // = \sum_{i = 0}^{n} \sum_{j = 0}^{m - 1} [j < ceil((ai + b + 1) / c) - 1]
    // = \sum_{i = 0}^{n} \sum_{j = 0}^{m - 1} [j + 1 < ceil((ai + b + 1) / c)]
    // = \sum_{i = 0}^{n} \sum_{j = 0}^{m - 1} [j + 1 < (ai + b + 1) / c]
    // = \sum_{i = 0}^{n} \sum_{j = 0}^{m - 1} [cj + c - b - 1 < ai]
    // = \sum_{i = 0}^{n} \sum_{j = 0}^{m - 1} [(cj + c - b - 1) / a < i]
    // = \sum_{i = 0}^{n} \sum_{j = 0}^{m - 1} [floor((cj + c - b - 1) / a) < i]
    // = \sum_{j = 0}^{m - 1} \sum_{i = 0}^{n} [floor((cj + c - b - 1) / a) < i]
    // = \sum_{j = 0}^{m - 1} [n - floor((cj + c - b - 1) / a)]
    // = nm - \sum_{j = 0}^{m - 1} floor((cj + c - b - 1) / a)
    // = nm - floor_sum(c, c - b - 1, a, m - 1)

    auto m = (a * n + b) / c;
    return res + n * m - floor_sum(c, c - b - 1, a, m - 1);
}