void dvd(int n){
    for(int l = 1; l <= n; l++){
        int k = n / l;
        // k = floor(n / l), k * r <= n
        // r <= n / k ==> r <= floor(n / k)
        int r = n / k;
        // n / l = n / (l + 1) = ... = n / r = k
        // do something
        
        l = r;
    }
}