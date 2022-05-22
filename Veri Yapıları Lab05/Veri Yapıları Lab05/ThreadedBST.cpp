//ÖZGE KATIRCI
//MELÝSA DEMÝRHAN 
#include "ThreadedBST.h"
using namespace std;
///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode* curr = this->min();
	while (curr != NULL) {
		BSTNode* n = this->next(curr);
		delete curr;
		curr = n;
	}// end-while
} //end-eraseTreeNodes
///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {
	BSTNode* p = root;
	BSTNode* k = NULL;
	while (p != NULL)
	{
		if (key == (p->key))
		{
			cout << "Node is already in the tree." << endl;
			return;
		}
		k = p;
		if (key < p->key)
		{
			if (p->leftLinkType == CHILD) {
				p = p->left;
			}
			else {
				break;
			}
		}
		else
		{
			if (p->rightLinkType == CHILD) {
				p = p->right;
			}
			else {
				break;
			}
		}
	}
	BSTNode* tmp = new BSTNode(key);

	if (k == NULL)
	{
		root = tmp;
		tmp->left = NULL;
		tmp->right = NULL;
	}
	else if (key < (k->key))
	{
		tmp->left = k->left;
		tmp->right = k;
		k->leftLinkType = CHILD;
		k->left = tmp;
	}
	else
	{
		tmp->left = k;
		tmp->right = k->right;
		k->rightLinkType = CHILD;
		k->right = tmp;
	}
}
///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
	BSTNode* k = NULL, * p = root;
	int temp = 0;

	while (p) {
		if (key == p->key) {
			temp = 1;
			break;
		}
		k = p;
		if (key < p->key) {
			if (p->leftLinkType == CHILD)
				p = p->left;
			else
				break;
		}
		else {
			if (p->rightLinkType == CHILD){
				p = p->right;
			}	
			else{
				break;
			}	
		}
	}

	if (temp == 0){
		cout << "Key is not found in the tree."<<endl;
	}
	else if (p->leftLinkType == CHILD && p->rightLinkType == CHILD){
		BSTNode* ks = p;
		BSTNode* s = p->right;

		while (s->left != NULL) {
			ks = s;
			s = s->left;
		}

		p->key = s->key;

		if (s->leftLinkType == THREAD && s->rightLinkType == THREAD){
			if (k == NULL){
				root = NULL;
			}
			else if (s == ks->left) {
				ks->leftLinkType = THREAD;
				ks->left = s->left;
			}
			else {
				ks->rightLinkType = THREAD;
				ks->right = s->right;
			}
			free(s);
		}
		else{
			BSTNode* temp;

			if (s->leftLinkType == CHILD){
				temp = s->left;
			}
			else{
				temp = s->right;
			}

			if (ks == NULL){
				root = temp;
			}
			else if (s == ks->left){
				ks->left = temp;
			}
			else{
				ks->right = temp;
			}
				
			BSTNode* ss = next(s);
			BSTNode* pp = previous(s);

			if (s->leftLinkType == CHILD){
				pp->right = ss;
			}
			else {
				if (s->rightLinkType == CHILD)
					ss->left = pp;
			}
			free(s);
		}
	}
	else if (p->leftLinkType == CHILD){
		BSTNode* temp;
		if (p->leftLinkType == CHILD)	{
			temp = p->left;
		}
		else {
			temp = p->right;
		}
		if (k == NULL) {
			root = temp;
		}
		else if (p == k->left){
			k->left = temp;
		}
		else{
			k->right = temp;
		}
			
		BSTNode* s = next(p);
		BSTNode* pp = previous(p);
		if (p->leftLinkType == CHILD){
			pp->right = s;
		}	
		else {
			if (p->rightLinkType == CHILD){
				s->left = pp;
			}
		}

		free(p);
	}
	else if (p->rightLinkType == CHILD){
		BSTNode* temp;
		if (p->leftLinkType == CHILD){
			temp = p->left;
		}
		else {
			temp = p->right;
		}
		if (k == NULL) {
			root = temp;
		}
		else if (p == k->left) {
			k->left = temp;
		}
		else {
			k->right = temp;
		}
			
		BSTNode* s = next(p);
		BSTNode* pp = previous(p);
		if (p->leftLinkType == CHILD){
			pp->right = s;
		}
		else {
			if (p->rightLinkType == CHILD){
				s->left = pp;
			}
				
		}
		free(p);
	}
	else{
		if (k == NULL)
			root = NULL;
		else if (p == k->left) {
			k->leftLinkType = THREAD;
			k->left = p->left;
		}
		else {
			k->rightLinkType = THREAD;
			k->right = p->right;
		}
		free(p);
	}

} // end-remove
///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::find(int key) {
	BSTNode* p = root;
	while (p != NULL)
	{
		if (key == p->key)
		{
			return p;
		}
		else if (key > p->key)
		{
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	BSTNode* p = root;
	if (p == NULL)
	{
		return NULL;
	}
	while (p->left != NULL)
	{
		p = p->left;
	}
	return p;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {
	BSTNode* p = root;
	if (p == NULL)
	{
		return NULL;
	}
	while (p->right != NULL)
	{
		p = p->right;
	}
	return p;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {
	// Fill this in
	if (node == NULL){
		return NULL;
	}
	if (node->leftLinkType == THREAD){
		return node->left;
	}
	else {
		node = node->left;
		while (node->rightLinkType == CHILD) {
			node = node->right;
		}
		return node;
	}
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	// Fill this in
	if(node==NULL){
		return NULL;
	}
	else{
		if (node->rightLinkType == THREAD){
			return node->right;
		}
		node = node->right;
		while (node->leftLinkType == CHILD) {
			node = node->left;
		}
	   return node;
	}
} // end-next