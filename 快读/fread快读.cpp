inline char get(void) {
    static char buf[100000], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 100000, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}
inline void read(int &x) {
    x = 0; static char c; bool minus = false;
    for (; !(c >= '0' && c <= '9'); c = get()) if (c == '-') minus = true;
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get()); if (minus) x = -x;
}