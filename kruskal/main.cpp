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
        if(w<tmp.w) return true;
        else return false;
    }
    edge(int _u,int _v,int _w):u(_u),v(_v),w(_w){}
    edge(){}
};
#include <cstdlib>
#include <cstring>
#include <algorithm>
int fa[200];
int count[200];
int find(int x){
    return fa[x]==-1?x:fa[x]=find(fa[x]);
}
void join(int x,int y){
    int rootx=find(x);
    int rooty=find(y);
    if(count[rootx]>count[rooty]) {
        fa[rooty]=rootx;
        count[rootx]=(count[rooty]+1>count[rootx]?count[rooty]+1:count[rootx]);
    }
    else{
        fa[rootx]=rooty;
        count[rooty]=(count[rootx]+1>count[rooty]?count[rootx]+1:count[rooty]);
    }

}
bool ask(int x,int y){
    return find(x)==find(y);
}
int kruskal(){
    int sum=0;
    memset(fa,-1,sizeof(fa));
    memset(count,0,sizeof(count));
    std::vector<edge> myedges;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            if(adjamatrix[i][j]>0)
                myedges.push_back(edge(i,j,adjamatrix[i][j]));
        }
    sort(myedges.begin(),myedges.end());
    int cnt=0;
    for(std::vector<edge>::iterator it=myedges.begin();
        it!=myedges.end();it++){
            if(!ask(it->u,it->v)){
                sum+=it->w;
                join(it->u,it->v);
                cnt++;
            }
            if(cnt==n-1) return sum;
        }
        return sum;
}
int main(){
    while(std::cin>>n){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                std::cin>>adjamatrix[i][j];
        std::cout<<kruskal()<<std::endl;
    }
    return 0;
}