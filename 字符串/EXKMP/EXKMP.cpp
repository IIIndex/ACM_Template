// z[i]表示串s[0...n - 1]与串s[i...n - 1]的LCP（最长公共前缀）
// 其中，z[0]在本模板计算结果为0，但在某些题可能需要为n，根据情况具体使用
vector<int> z;

void exkmp(const string& str){
    z.resize(str.size());
    for(int i = 1, l = 0, r = 0; i < str.length(); i++){
        // str[0, r - l] == str[l, r] -> str[i, r] == str[i - l, r - l]
        // 因此若z[i - l] < len(s[i...r])的话，z[i]和z[i - l]等价
        if(z[i - l] < r - i + 1) z[i] = z[i - l];
        // 否则暴力向后匹配即可
        else{
            z[i] = max(r - i + 1, 0);
            while(i + z[i] < str.length() && str[z[i]] == str[i + z[i]]) z[i]++;
            l = i; r = i + z[i] - 1;
        }
    }
}