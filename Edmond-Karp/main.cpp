#include <iostream>
#include <queue>
#include <cstdlib>
#include <cstring>
int n;
int m;
int edge[205][205];
int pre[205];
int vis[205];
bool bfs(){
    std::queue<int> Q;
    Q.push(1);
    vis[1]=1;
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=1;i<=n;i++){
            if(edge[u][i]&&!vis[i]){
                vis[i]=1;
                pre[i]=u;
                if(i==n) return true;
                Q.push(i);
            }
        }
    }
    return false;
}
int ek(){
    int sum=0;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<205;i++) pre[i]=-1;
    while(bfs()){
        int flow=0x3f3f3f3f;
        int u,pr;
        u=n;
        pr=pre[u];
        while(pr!=-1){
            if(flow>edge[pr][u]) flow=edge[pr][u];
            u=pr;
            pr=pre[u];
        }
        sum+=flow;
        u=n;
        pr=pre[u];
        while(pr!=-1){
            edge[pr][u]-=flow;
            edge[u][pr]+=flow;
            u=pr;
            pr=pre[u];
        }

        memset(vis,0,sizeof(vis));
        for(int i=0;i<205;i++) pre[i]=-1;
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
    std::cout<<ek()<<std::endl;
    }
    return 0;
}