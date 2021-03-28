#include <iostream>
#include <cstdlib>
#include <cstring>
#define INF 0x3f
#include <queue>
int dis[10010];
struct edge{
    int v;
    int w;
    int to;
    int next;
};
//struct edge myedges[500100];
struct edgenode{
    int u;
    int v;
    int w;
    struct edgenode* next;
};
struct edgenode* adjatable[10010];
int n,m,s;
void addedge(){
    int u,v,w;
    std::cin>>u>>v>>w;
    edgenode* tmp=adjatable[u];
    edgenode* p=new edgenode;
    p->u=u;
    p->v=v;
    p->w=w;
    p->next=tmp;
    adjatable[u]=p;
}

int count[10010];
int vis[10010];
void spfa(int s){
    std::queue<int> Q;
    Q.push(s);
    count[s]++;
    vis[s]=1;
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        vis[u]=0;
        for(edgenode* p=adjatable[u];p!=NULL;p=p->next){
            if(dis[p->v]>dis[u]+p->w){
                dis[p->v]=dis[u]+p->w;
                if(!vis[p->v]){
                    Q.push(p->v);
                    count[p->v]++;
                    vis[p->v]=1;
                }
            }
        }
    }
}
int main(){
    std::cin>>n>>m>>s;
    for(int i=1;i<=n;i++) adjatable[i]=NULL;
    for(int i=1;i<=m;i++){
        addedge();
    }
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    spfa(s);
    for(int i=1;i<=n;i++){
        if(dis[i]==0x3f3f3f3f) std::cout<<2147483647<<" ";
        else std::cout<<dis[i]<<" ";
    }
    return 0;
}