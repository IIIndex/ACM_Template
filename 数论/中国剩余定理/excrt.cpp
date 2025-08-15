// CRT 用于解决模数互质的同余方程
// EXCRT 用于解决模数不互质的同余方程

// [f, s] => x \equiv s (mod f)
auto excrt = [&](vector<pair<ll, ll>>& a) -> i128 {
    i128 N = 1, res = 0;
    for (auto [f, s]: a) {
        // x \equiv res (mod N)
        // x \equiv s (mod f) =>
        // res + xN = s + yf => xN - yf = s - res
        auto g = gcd((ll)N, f);
        if ((s - res) % g) return -1;
        ll x, y;
        exgcd(exgcd, f, N, x, y);
        // x = res + xN
        // x \equiv res + xN (mod lcm(N, f))
        res = res + y * (s - res) / g * N;
        N = lcm((ll)N, f);
        res = ((res % N) + N) % N;
    }
    return res;
};