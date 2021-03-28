#include <iostream>
#include <queue>
struct edge{
    int v;
    struct edge* next;
};
struct edge* adjatable[110];
int n;
int cnt[110];
void insertedge(int vnum,int tmp){
    struct edge** p;
    p=&adjatable[vnum];
    while(*p!=NULL) p=&((*p)->next);
    *p=new struct edge;
    (*p)->v=tmp;
    (*p)->next=NULL;
    cnt[tmp]++;
}
void toposort(){
    std::queue<int> Q;
    int start;
    int i=1;
    for(;i<=n;i++){
        if(cnt[i]==0) Q.push(i);
    }
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        std::cout<<u<<" ";
        for(struct edge* p=adjatable[u];p!=NULL;p=p->next){
            cnt[p->v]--;
            if(cnt[p->v]==0) Q.push(p->v);
        }
    }
}
int main(){
    std::cin>>n;
    for(int vnum=1;vnum<=n;vnum++){
        int tmp;
        std::cin>>tmp;
        while(tmp!=0){
            insertedge(vnum,tmp);
            
            std::cin>>tmp;
        }
    }
    toposort();
    return 0;
}