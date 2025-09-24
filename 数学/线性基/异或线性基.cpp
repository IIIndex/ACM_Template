// 值域大小（向量维数）
constexpr int M = 21;
struct XorBase {
    // cnt - 线性基内有几个有效向量
    int cnt;
    // a[x] - 第x位为1的向量（可以为0，代表空）
    vector<int> a;

    XorBase() {
        cnt = 0;
        a.resize(M + 1);
    }

    // 0 - x能够被原有向量表示
    // 1 - x插入线性基
    int insert(int x) {
        for (int i = M; i >= 0; i--) {
            // x的第i位不为1，不需要操作
            if (!((x >> i) & 1)) continue;
            // 该位没有元素，直接作为新向量插入
            if (!a[i]) {
                a[i] = x;
                cnt++;
                return true;
            }
            // 异或上向量，将第i位清零
            x ^= a[i];
        }

        return false;
    }

    // 1 - index
    // 线性基能表示第k大的元素
    int kth(int k) {
        // 越界
        if (k < 1 || k > (1 << cnt)) return -1;
        int x = 0, tot = 1 << cnt;

        for (int i = M; i >= 0; i--) {
            if (!a[i]) continue;
            // k比tot / 2大，说明要往大的半边走
            if (k > tot / 2) {
                // 大的即为第i位置1
                if (!((x >> i) & 1)) x ^= a[i];
                k -= tot / 2;
            }
            else {
                // 小的半边，第i位置于0
                if (((x >> i) & 1)) x ^= a[i];
            }

            tot >>= 1;
        }

        return x;
    }

    // 线性基能表示的，严格小于x的数量
    int less_than(int x) {
        // 不存在比0小第
        if (x <= 0) return 0;
        int tot = 1 << cnt, ret = 0, now = 0;

        for (int i = M; i >= 0; i--) {
            if (a[i]) {
                // x这一位是1
                if ((x >> i) & 1) {
                    // 该位为0的一半都比x小
                    ret += tot / 2;
                    // 将now的第i位置为1
                    if (!((now >> i) & 1)) now ^= a[i];
                }
                // 将now的这一位置为0
                else if ((now >> i) & 1) now ^= a[i];

                tot >>= 1;
            }
            else {
                // 没有首位为i的向量，且x或者now的第i位不同
                if (((x ^ now) >> i) & 1) {
                    // x大，剩下的向量都比x小了
                    if ((x >> i) & 1) return ret + tot;
                    // now大，剩下的向量都比x大
                    else return ret;
                }
            }
        }

        return ret;
    }

    // 小于等于
    int leq(int x) {
        return less_than(x + 1);
    }

    // 从x出发，在线性基意义下的走k步
    int jumpk(int x, int k) {
        auto now = leq(x);
        return kth(now + k);
    }
};