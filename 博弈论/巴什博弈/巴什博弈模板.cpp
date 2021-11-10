bool Bash(int m,int n){             //m为单次最大数，n为总数
    if(n%(m+1))
        return true;                //先手获胜
    else
        return false;               //后手获胜
}