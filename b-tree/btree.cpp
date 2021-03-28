#include "btree.h"
#include <iostream>
btreenode::btreenode(int _t, bool _isleaf):t(_t),isleaf(_isleaf)
{
	keys = new int[2 * t - 1];
	sons= new btreenode*[2 * t];
	keynum = 0;
}

void btreenode::traverse()
{
	for (int i = 0; i < keynum; i++) {
		if(!isleaf) sons[i]->traverse();
		std::cout << " " << keys[i];
	}
	if(!isleaf) sons[keynum]->traverse();
}

btreenode * btreenode::search(int k)
{
	int i = 0;
	while (i<keynum&&k>keys[i]) i++;
	if (i < keynum&&k == keys[i]) return this;
	if (isleaf) return NULL;
	return sons[i]->search(k);
}

void btreenode::insertNonFull(int k)
{
	if (isleaf) {
		int i = keynum-1;
		while (i >= 0 && keys[i] > k) {
			keys[i + 1] = keys[i];
			i--;
		}
		keys[i + 1] = k;
		keynum++;
	}
	else {
		int i = keynum - 1;
		while (i >= 0 && keys[i] > k) i--;
		//insert to sons[i+1]
		if (sons[i + 1]->keynum == 2 * t - 1) {
			splitChild(i + 1);
			if (keys[i + 1] < k) i++;
		}
		sons[i + 1]->insertNonFull(k);
	}
}

void btreenode::splitChild(int i)
{
	btreenode* y = this->sons[i];
	btreenode* z = new btreenode(y->t, y->isleaf);

	z->keynum = y->t - 1;
	y->keynum = y->t - 1;

	for (int j = t; j <= 2 * t-2; j++) {
		z->keys[j - t] = y->keys[j];
	}
	if (y->isleaf == false) {
		for (int j = t; j <= 2 * t - 1; j++) {
			z->sons[j - t] = y->sons[j];
		}
	}
	
	for (int j = keynum + 1; j >= i + 2; j--) {
		sons[j] = sons[j - 1];
	}
	sons[i + 1] = z;
	for (int j = keynum; j >= i + 1; j--) {
		keys[j] = keys[j-1];
	}
	keys[i] = y->keys[t - 1];

	keynum++;
}

int btreenode::getPred(int index)
{
	btreenode* cur = sons[index];
	while (cur->isleaf == false)
		cur = cur->sons[cur->keynum];
	
	return cur->keys[cur->keynum - 1];
}

int btreenode::getSucc(int index)
{
	btreenode* cur = sons[index + 1];
	while (cur->isleaf == false)
		cur = cur->sons[0];
	return cur->keys[0];
}

void btreenode::borrowFromPrev(int index)//give a key from sons[index-1] to sons[index]
{
	btreenode* child = sons[index];
	btreenode* sibing = sons[index - 1];
	for (int i = child->keynum; i >= 1; i--) {
		child->keys[i] = child->keys[i - 1];
	}
	if (child->isleaf == false)
		for (int i = child->keynum + 1; i >= 1; i--)
			child->sons[i] = child->sons[i - 1];
	child->keys[0] = keys[index - 1];

	if (child->isleaf == false)
		child->sons[0]=sibing->sons[sibing->keynum];
	keys[index - 1] = sibing->keys[sibing->keynum - 1];
	child->keynum++;
	sibing->keynum--;
	return;
}

void btreenode::borrowFromNext(int index)
{
	btreenode* child = sons[index];
	btreenode* sibling = sons[index + 1];

	//give the key
	child->keys[child->keynum] = keys[index];
	keys[index] = sibling->keys[0];
	for (int i = 0; i <= sibling->keynum - 2; i++)
		sibling->keys[i] = sibling->keys[i + 1];

	//give the sons
	if (child->isleaf == false) {
		child->sons[child->keynum + 1] = sibling->sons[0];
		for (int i = 0; i <= sibling->keynum - 1; i++)
			sibling->sons[i] = sibling->sons[i + 1];
	}

	//change the keynum
	child->keynum++;
	sibling->keynum--;
	return;
}

void btreenode::merge(int index)//merge sons[index] with sons[index+1]
{
	btreenode* child = sons[index];
	btreenode* sibling = sons[index + 1];

	child->keys[t - 1] = keys[index];
	for (int i = 0; i <= t-2; i++)
		child->keys[i + t] = sibling->keys[i];
	
	if (child->isleaf == false) {
		for (int i = 0; i <= t-1; i++)
			child->sons[t + i] = sibling->sons[i];
	}
	for (int i = index; i <= keynum - 2; i++){
		keys[i] = keys[i + 1];
	}
	for (int i = index + 1; i <= keynum - 1; i++) {
		sons[i] = sons[i + 1];
	}
	child->keynum = 2 * t - 1;
	keynum--;
	delete sibling;
	return;
}

void btreenode::removeFromLeaf(int index)
{

	for (int i = index; i <= keynum - 2; i++)
		keys[i] = keys[i + 1];
	keynum--;
	return;
}

void btreenode::removeFromNonLeaf(int index)
{
	int k = keys[index];//the merge function will change the keys[], so we get it first.
	
	if (sons[index]->keynum >= t) {
		int pred = getPred(index);
		keys[index] = pred;
		sons[index]->remove(pred);
	}
	else if (sons[index + 1]->keynum >= t) {
		int succ = getSucc(index);
		keys[index] = succ;
		sons[index + 1]->remove(succ);
	}
	else {
		merge(index);
		sons[index]->remove(k);
	}
}

void btreenode::fill(int index)
{
	if (index != 0 && sons[index - 1]->keynum >= t)
		borrowFromPrev(index);
	else if (index != keynum && sons[index + 1]->keynum >= t)
		borrowFromNext(index);
	else {
		if (index != keynum) merge(index);
		else merge(index - 1);
	}
	return;
}

int btreenode::findkey(int k)
{
	int index = 0;
	while (index < keynum&&keys[index] < k) {
		index++;
	}
	return index;
}

void btreenode::remove(int k)
{
	int index = findkey(k);
	if (index < keynum&&keys[index]==k) {
		if (isleaf) {
			removeFromLeaf(index);
		}
		else
			removeFromNonLeaf(index);
	}
	else {
		if (isleaf) {
			std::cout << "The key " << k << " is noy exist in the tree.\n";
			return;
		}
		else {
			if (sons[index]->keynum < t) fill(index);

			if (index > keynum) sons[index - 1]->remove(k);
			else sons[index]->remove(k);

		}
	}
}

btree::btree(int _t):t(_t),root(NULL)
{
}

void btree::traverse()
{
	if (root) root->traverse();
}

btreenode * btree::search(int k)
{
	if (root) return root->search(k);
	else return NULL;
}

void btree::insert(int k)
{
	if (root == NULL) {
		root = new btreenode(t, true);
		root->keys[0] = k;
		root->keynum = 1;
	}
	else {
		if (root->keynum == 2 * t - 1) {
			btreenode* s = new btreenode(t, false);
			s->sons[0] = root;
			s->splitChild(0);
			root = s;
		}
		root->insertNonFull(k);
	}
}

void btree::remove(int k)
{
	if (root == NULL) {
		std::cout << "the tree is empty\n";
		return;
	}
	root->remove(k);

	if (root->keynum == 0) {
		btreenode* tmp = root;
		if (root->isleaf) root = NULL;
		else root = root->sons[0];
		delete tmp;
	}
	return;
}
