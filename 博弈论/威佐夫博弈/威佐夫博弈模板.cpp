bool Wythoff(int x,int y){
    if(x>y){
        swap(x,y);
    }
    int z=y-x;
    if((int)((sqrt(5)+1)/2*z)==x){
        return false;        //先手必败
    }
    else{
        return true;         //先手必胜
    }
}