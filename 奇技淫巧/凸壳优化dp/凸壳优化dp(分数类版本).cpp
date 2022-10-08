// dp[u] = max(A(u) + B(v) + K(v)X(u))
namespace CHT{
    using T = __int128_t;

    T sgn(T x) { return (x > 0) - (x < 0); }
    T abs(const T& a) {return a > 0 ? a : -a;}

    struct frac{
        T x, y;
        frac(T x, T y = 1): x(sgn(x ^ y) * abs(x)), y(abs(y)) {}
        bool operator<=(const frac& oth) const{
            return x * oth.y <= y * oth.x;
        }
    };

    const frac NEGINF = {(T)-1e18, 1};

    struct Line{
        T k, b;
        frac x;
        Line(T k, T b, frac x = NEGINF): k(k), b(b), x(x) {}
        T operator[](T x) const {return k * x + b;}
        // 需要保证斜率不相等，否则需要特判
        frac insert(const Line& oth) {return {oth.b - b, k - oth.k};}
    };

    deque<Line> dq;

    void update(Line l){
        auto x = NEGINF;
        while(!dq.empty() && (x = dq.back().insert(l)) <= dq.back().x) dq.pop_back();
        dq.push_back({l.k, l.b, x});
    }

    // 从大到小query(基于dq内Line.x的单调性)
    // 若需要随机query则需要使用lower_bound
    T query(T x){
        frac xx = {x};
        while(xx <= dq.back().x) dq.pop_back();
        return dq.back()[x];
    }

    void clear() {dq.clear();}

    // 原始表达式: dp[u] = max(A(u) + B(v) + K(v)X(u))
    // Line[x] = {K[x], B[x]}
    // ans[x] = A[x] + query(x)
    T A(T x) {/* code here */}
    T B(T x) {/* code here */}
    T K(T x) {/* code here */}
    T X(T x) {/* code here */}
}