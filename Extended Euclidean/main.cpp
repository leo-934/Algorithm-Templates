#include <iostream>
int exgcd(int a,int b,int & x,int & y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    int r=exgcd(b,a%b,x,y);
    int tmp=x;
    x=y;
    y=b*tmp-a/b*b*y;
    return r;
}
int main(){
    int a,b;
    int x,y;
    std::cin>>a>>b;
    int r=exgcd(a,b,x,y);
    std::cout<<r<<std::endl;
    std::cout<<x<<std::endl;
    std::cout<<y<<std::endl;
    return 0;
}