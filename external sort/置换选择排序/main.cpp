#include <iostream>
#include <queue>
std::queue<int> data;
int m,n;
int heapsize;
void siftdown(int* myheap,int position){
	int father=position;
	int son=father*2+1;
	int tmp=myheap[father];
	while(son<heapsize){
		if(son+1<heapsize&&myheap[son+1]<myheap[son]) son++;
		if(tmp>myheap[son]){
			myheap[father]=myheap[son];
			father=son;
			son=son*2+1;
		}
		else break;
	}
	myheap[father]=tmp;
}
using std::vector;
vector<int> mysort(int * myheap){
	vector<int> res;
	int min;
	while(!data.empty()&&heapsize!=0){
		min=myheap[0];
		res.push_back(min);
		int tmp;
		tmp=data.front();
		data.pop();
		if(min<=tmp) myheap[0]=tmp;
		else{
			myheap[0]=myheap[heapsize-1];
			myheap[heapsize-1]=tmp;
			heapsize--;
		}
		siftdown(myheap,0);
	}
	return res;
}
int main(){
	std::cin>>m>>n;
	int myheap[n];
	heapsize=n;
	for(int i=0;i<m;i++){
		int tmp;
		std::cin>>tmp;
		data.push(tmp);
	}
	for(int i=0;i<n;i++){
		int tmp;
		std::cin>>tmp;
		myheap[i]=tmp;
	}
	std::vector<int> res=mysort(myheap);
	for(std::vector<int>::iterator it=res.begin();it!=res.end();it++){
		std::cout<<*it<<" ";
	}
	return 0;
}