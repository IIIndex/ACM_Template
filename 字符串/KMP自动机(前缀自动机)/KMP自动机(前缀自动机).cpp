namespace KMP_AUTOMATON{
    vector<int> pmt;
    // 字符集大小
    constexpr int M = 26;

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

    // res[i][j]表示前i个字符已经匹配上, 在此基础上添加j字符的pmt值
    // 若j == str[i + 1], res[i][j] == i + 1
    void build(string& str, vector<vector<int>>& res){
        // 此处字符串处理根据题意自行分析
        // str += '#'; 
        get_pmt(str);
        int n = str.length();
        res.assign(n, vector<int>(M));
        for(int i = 0; i < n; i++) for(int c = 0; c < M; c++){
            if(i > 0 && 'a' + c != str[i]) res[i][c] = res[pmt[i - 1]][c];
            else res[i][c] = i + ('a' + c == str[i]);
        }
    }
}