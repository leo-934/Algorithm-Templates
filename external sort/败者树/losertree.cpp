#include <iostream>
int n,m;
int losertree[1000];
void adjust(int position){
	int s=losertree[position];
           	int father=position/2;
	while(father>0){
		if(s>losertree[father]){
			int tmp=losertree[father];
			losertree[father]=s;
			s=tmp;
			
		}
		father=father/2;
	}
	losertree[0]=s;
}
void inittree(){
	for(int i=n;i<2*n;i++)
		adjust(i);
}
void printtree(){
	for(int i=0;i<n;i++){
		std::cout<<losertree[i]<<" ";
	}
	std::cout<<std::endl;
}
int main(){
	std::cin>>n>>m;
	for(int i=0;i<n;i++){
		losertree[i]=0;
		std::cin>>losertree[n+i];
	}
	inittree();
	printtree();
	for(int i=0;i<m;i++){
		int a,b;
		std::cin>>a>>b;
		losertree[a+n]=b;
		adjust(a+n);
		printtree();
	}
	return 0;
}