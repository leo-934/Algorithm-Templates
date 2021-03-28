#include <iostream>
#include <queue>
#include <cstdlib>
#include <cstring>
int n;
int m;
int edge[205][205];
int vis[205];
int dfs(int vnum,int flow){
    vis[vnum]=1;
    vis[vnum]=1;
    if(vnum==n) return flow;
    for(int i=1;i<=n;i++){
        if(!vis[i]&&edge[vnum][i]>0){
            int k=dfs(i,flow>edge[vnum][i]?edge[vnum][i]:flow);
            if(k>0){
                edge[vnum][i]-=k;
                edge[i][vnum ]+=k;
                return k;
            }
        }
    }
    return 0;
}
int ff(){
    int sum=0;
    int flow;
    memset(vis,0,sizeof(vis));
    while(flow=dfs(1,0x3f3f3f3f)){
        memset(vis,0,sizeof(vis));
        sum+=flow;

    }
    return sum;
}
int main(){
    while(std::cin>>m>>n){
        memset(edge,0,sizeof(edge));
    for(int i=1;i<=m;i++){
        int u,v,w;
        std::cin>>u>>v>>w;
        edge[u][v]+=w;
    }
    std::cout<<ff()<<std::endl;
    }
    return 0;
}