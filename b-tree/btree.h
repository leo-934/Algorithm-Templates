#pragma once

class btree;
class btreenode;

class btreenode {
	int * keys;
	int t;
	btreenode ** sons;
	int keynum;
	bool isleaf;
public:	                  
	btreenode(int _t, bool _isleaf); //constructor

	void traverse();

	btreenode* search(int k);

	void insertNonFull(int k);//the node must be nonfull when this function is called

	void splitChild(int i);

	int getPred(int index);

	int getSucc(int index);

	void borrowFromPrev(int index);

	void borrowFromNext(int index);

	void merge(int index);

	void removeFromLeaf(int index);

	void removeFromNonLeaf(int index);

	void fill(int index);

	int findkey(int k);

	void remove(int k);

	friend class btree;

	~btreenode()
	{
		delete[] keys;
		delete[] sons;
	}
	
};
class btree {
	btreenode * root;
	int t;
public:
	btree(int _t);

	void traverse();
	
	btreenode* search(int k);

	void insert(int k);

	void remove(int k);
};