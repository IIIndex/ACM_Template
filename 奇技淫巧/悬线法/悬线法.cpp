namespace Max_Matrix{
    // map
    vector<vector<int>> mp, u, l, r;
    // 记住初始化n和m (mp第一/二维)
    int n, m;

    bool valid(int x, int y){
        // 检查当前节点是否在区域内
        if(x < 0 || x >= n || y < 0 || y >= m) return false;
        // 检查当前节点是否合法
        return mp[x][y];
    }

    int max_matrix(){
        int ans = 0;
        u.clear(); l.clear(); r.clear();
        u = l = r = vector(n, vector<int>(m));
        for(int j = 0; j < m; j++) for(int i = 0; i < n; i++){
            if(!valid(i, j)) continue;
            u[i][j] = valid(i - 1, j) ? u[i - 1][j] + 1 : 1;
        }

        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
            if(!valid(i, j)) continue;
            l[i][j] = valid(i, j - 1) ? l[i][j - 1] + 1 : 1;
        }

        for(int i = 0; i < n; i++) for(int j = m - 1; j >= 0; j--){
            if(!valid(i, j)) continue;
            r[i][j] = valid(i, j + 1) ? r[i][j + 1] + 1 : 1;
        }

        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
            if(!valid(i, j)) continue;
            if(valid(i - 1, j)) {
                cmin(l[i][j], l[i - 1][j]);
                cmin(r[i][j], r[i - 1][j]);
            }
            // 此处是求子矩形, 若求子正方形则取min(width, height)后平方即可
            cmax(ans, u[i][j] * (r[i][j] + l[i][j] - 1));
        }
        return ans;
    }

    void init(int _n, int _m){
        mp.clear();
        n = _n, m = _m;
        mp = vector(n, vector<int>(m));
    }
}