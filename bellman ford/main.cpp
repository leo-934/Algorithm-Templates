#include <iostream>
#include <cstdlib>
#include <cstring>
int dis[600];
struct edge{
    int v,to,w;
    edge(int _v,int _to,int _w):v(_v),to(_to),w(_w){}
    edge(){};
};
struct edge myedges[5300];
int cnt=1;
int vnum;
void readedge(){
    int v,to,w;
    std::cin>>v>>to>>w;
    myedges[cnt]=edge(v,to,-w);
    cnt++;
}
void readbiegde(){
    int v,to,w;
    std::cin>>v>>to>>w;
    myedges[cnt]=edge(v,to,w);
    cnt++;
    myedges[cnt]=edge(to,v,w);
    cnt++;
}
int bellmanford(){
    for(int j=1;j<vnum;j++){
        for(int i=1;i<=cnt;i++){
            if(dis[myedges[i].to]>dis[myedges[i].v]+myedges[i].w)
                dis[myedges[i].to]=dis[myedges[i].v]+myedges[i].w;
        }
    }
    for(int i=1;i<=cnt;i++){
            if(dis[myedges[i].to]>dis[myedges[i].v]+myedges[i].w) return 0;
    }
    return 1;
}
int main(){
    int f;
    std::cin>>f;
    for(int i=0;i<f;i++){
        int n,m,w;
        std::cin>>n>>m>>w;
        cnt=1;
        vnum=n;
        memset(dis,0x3f,sizeof(dis));
        dis[1]=0;
        for(int j=0;j<m;j++){
            readbiegde();
        }
        for(int j=0;j<w;j++){
            readedge();
        }
        cnt--;
        int flag;
        flag=bellmanford();
        if(!flag) std::cout<<"YES"<<std::endl;
        else{
            std::cout<<"NO"<<std::endl;
        }
    }
    
    return 0;
}