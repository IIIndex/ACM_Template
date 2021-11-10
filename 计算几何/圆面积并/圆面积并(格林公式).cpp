
//*********复杂度n²logn*************

typedef double ld;

const int N = 1010;
const ld pi = acos(-1);
 
int n; ld ans;
 
struct P {
    ld x, y;
    P operator - (const P&a) const {
        return (P) {x - a.x, y - a.y};
    }
    ld len () {
        return sqrt(x * x + y * y);
    }
};
 
struct C {
    P o; ld r;
    bool operator < (const C&a) const {
        if (o.x != a.o.x) return o.x < a.o.x;
        if (o.y != a.o.y) return o.y < a.o.y;
        return r < a.r;
    }
    bool operator == (const C&a) const {
        return o.x == a.o.x && o.y == a.o.y && r == a.r;
    }
    ld oint (ld t1, ld t2) {
        return r * (r * (t2 - t1) + o.x * (sin(t2) - sin(t1)) - o.y * (cos(t2) - cos(t1))); //格林公式求积分
    }
} a[N];
 
struct D {
    ld x; int c;
    bool operator < (const D&a) const {
        return x < a.x;
    }
} pos[N * 2];
 
ld work (int c) {
    int tot = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
    if (i != c) {
        P d = a[i].o - a[c].o; ld dis = d.len();
        if (a[c].r <= a[i].r - dis) return 0;
        if (a[i].r <= a[c].r - dis || a[i].r + a[c].r <= dis) continue;
        ld g = atan2(d.y, d.x), g0 = acos((dis * dis + a[c].r * a[c].r - a[i].r * a[i].r) / (2 * dis * a[c].r)), l = g - g0, r = g + g0;
        if (l < -pi) l += pi * 2;
        if (r >= pi) r -= pi * 2;
        if (l > r) cnt++;
        pos[++tot] = (D) {l, 1};
        pos[++tot] = (D) {r, -1};
    }
    pos[0].x = -pi, pos[++tot].x = pi;
    sort(pos + 1, pos + 1 + tot);                                   //对交点排序
    ld ans = 0;
    for (int i = 1; i <= tot; cnt += pos[i++].c)
        if (cnt == 0) ans += a[c].oint(pos[i - 1].x, pos[i].x);     //求当前弧的积分
    return ans;
}
 
int main () {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf%lf%lf",&a[i].o.x, &a[i].o.y, &a[i].r);
    sort(a + 1, a + 1 + n);
    n = unique(a + 1, a + 1 + n) - a - 1;
    for (int i = 1; i <= n; i++) ans += work(i);
    printf("%.3lf\n", ans / 2);
}