// 用于找到 ax + by = gcd(a, b) 的一组解
auto exgcd = [](auto&& self, ll a, ll b, ll& x, ll& y) -> void {
    if (!b) {
        // 此时 a = gcd(a, b)
        x = 1, y = 0;
        return;
    }

    self(self, b, a % b, x, y);
    // ax + by = gcd(a, b) = gcd(b, a % b) = bx_2 + (a % b)y_2
    // = bx_2 + (a - b * floor(a / b))
    // ax = ay_2, by = bx_2 - b * floor(a * b) * y_2
    // x = y_2, y = x_2 - floor(a * b) * y_2
    auto t = x;
    x = y;
    y = t - a / b * y;
};