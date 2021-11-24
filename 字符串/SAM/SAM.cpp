using ll = long long;
namespace sam {
    struct state {
        // len - 当前节点为endpos的最长字符串(u)长度
        // link - u的后缀中，不在该节点结束的最长后缀的endpos位置
        int len, link;
        // int nxt[30];
        // 字符为first时，下一跳的位置
        map<int, int> nxt;
    };
    const int maxlen = 1e5 + 100;
    // 对于长度为n的字符串，sam内最多有2n - 1个结点
    state st[maxlen << 1];
    // sam结点个数、最后一个结点编号 + 1
    int sz, last;
    // 初始化sam
    void init() {
        st[0].len = 0;
        st[0].link = -1;
        sz++;
        last = 0;
    }
    // 在线加入字符
    void extend(int c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        // 不断地往不存在c边的点加入c后缀
        while (p != -1 && !st[p].nxt.count(c)) {
            st[p].nxt[c] = cur;
            p = st[p].link;
        }
        // 指向t0(虚拟首结点)
        if (p == -1)
            st[cur].link = 0;
        else {
            int q = st[p].nxt[c];
            // q = p + c
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else {
                // 克隆虚拟q结点，q = p + c
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].nxt = st[q].nxt;
                st[clone].link = st[q].link;
                // 将虚拟q结点和所有q结点的后缀连接
                while (p != -1 && st[p].nxt[c] == q) {
                    st[p].nxt[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
}
