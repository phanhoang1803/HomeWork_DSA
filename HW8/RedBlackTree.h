#pragma once
#include "Libraries.h"
#include "DefineRBTree.h"

class RedBlackTree
{
private:
	rbref root;
	rbref nil;

	//	INFORMATION HELPER
	rbref getNode(int key);
	rbref getRoot();
	rbref getNIL();
	bool isLeaf(rbref node);

	void displayHelper(rbref root, string indent, bool last);
	int heightHelper(rbref root);
	int blackHeightHelper(rbref root);

	//	ROTATE
	void leftRotate(rbref x);
	void rightRotate(rbref x);

	//	INSERT HELPER
	void insertBinarySearchTree(rbref x);
	void insert_LeftAdjust(rbref& x);
	void insert_RightAdjust(rbref& x);
	void insert_FixUp(rbref x);

	//	DELETE HELPER
	rbref predecessor(rbref x);
	rbref successor(rbref x);
	void delete_LeftAdjust(rbref& x);
	void delete_RightAdjust(rbref& x);
	void delete_FixUp(rbref x);
public:
	//	STRUCTOR
	RedBlackTree();

	//	INFORMATION
	void display();

	//	PROCESSING
	void insertRBTree(int key);
	void createTree(int a[], int n);
	rbref lookUp(int key);
	int height();
	int blackHeight();
	bool remove(int key);
};