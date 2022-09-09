// ans[i]代表匹配串和模式串以模式串的第i个字符(0 - index)为止的最长前缀
vector<int> pmt, ans;

void get_pmt(const string& str){
    pmt.resize(str.length());
    // 获取pmt数组
    for(int i = 1, j = 0; i < str.length(); i++){
        // 不断前跳
        while(j && str[i] != str[j]) j = pmt[j - 1];
        if(str[i] == str[j]) j++;
        pmt[i] = j;
    }
}

// s - 模式串，p - 匹配串
void kmp(const string& s, const string& p){
    get_pmt(p);
    ans.resize(s.length());
    for(int i = 0, j = 0; i < s.length(); i++){
        // 不断前跳
        while(j && s[i] != p[j]) j = pmt[j - 1];
        if(s[i] == p[j]) j++;
        ans[i] = j;
    }
}