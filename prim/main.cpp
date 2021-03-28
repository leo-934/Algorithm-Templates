#include <iostream>
#include <queue>
int n;
int adjamatrix[200][200];
class mycmp{
public:
    bool operator()(std::pair<int,int> a,std::pair<int,int> b){
        if(a.second>=b.second) return true;
        else return false;  
    }
};
bool vis[200];
struct edge{
    int u;
    int v;
    int w;
    bool operator <(const struct edge& tmp) const{
        if(w>tmp.w) return true;
        else return false;
    }
    edge(int _u,int _v,int _w):u(_u),v(_v),w(_w){}
    edge(){}
};
int dis[200];
#include <cstdlib>
#include <cstring>
int prim(int vnum){
    int sum=0;
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    std::priority_queue<edge> Q;
    Q.push(edge(vnum,vnum,0));
    while(!Q.empty()){
        edge tmp;
        int found=0;
        while(!Q.empty()){
            tmp=Q.top();
            Q.pop();
            if(!vis[tmp.v]){
                found=1;
                break;
            }
        }
        if(found==0) return sum;
        vis[tmp.v]=true;
        sum+=tmp.w;
        for(int i=1;i<=n;i++){
            if(!vis[i]&&adjamatrix[tmp.v][i]>0){
                if(adjamatrix[tmp.v][i]<dis[i]){
                    dis[i]=adjamatrix[tmp.v][i];
                    Q.push(edge(tmp.v,i,dis[i]));
                }
            }
        }
    }
    return sum;
}
int main(){
    while(std::cin>>n){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                std::cin>>adjamatrix[i][j];
        std::cout<<prim(1)<<std::endl;
    }
    return 0;
}