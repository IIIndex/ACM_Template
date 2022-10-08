// dp[u] = max(A(u) + B(v) + K(v)X(u))
namespace CHT{
    using T = ll;
    // 注意double精度问题, 必要时可换成分数类
    constexpr db NEGINF = -1e18;
    struct Line{
        T k, b;
        db x;
        Line(T k, T b, db x = NEGINF): k(k), b(b), x(x) {}
        T operator[](T x) const {return k * x + b;}
        bool operator<(const T& pos) {return x < pos;}
        // 需要保证斜率不相等，否则需要特判
        db insert(const Line& oth) {return (db)(oth.b - b) / (k - oth.k);}
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
        while(dq.back().x > x) dq.pop_back();
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