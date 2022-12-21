#include "RedBlackTree.h"
#include "Libraries.h"

int main() {
	RedBlackTree rbt;
	//rbt.insert(1);
	//rbt.display(rbt.getRoot());
	//cout << "--------------------\n";
	//rbt.insert(2);
	//rbt.display(rbt.getRoot());
	//cout << "--------------------\n";
	//rbt.insert(3);
	//rbt.display(rbt.getRoot());
	//cout << "--------------------\n";
	//rbt.insert(4);
	//rbt.display(rbt.getRoot());
	//cout << "--------------------\n";
	//rbt.insert(5);
	//rbt.display(rbt.getRoot());
	//cout << "--------------------\n";

	/*rbt.insertRBTree(55);
	rbt.insertRBTree(40);
	rbt.insertRBTree(65);
	rbt.insertRBTree(60);
	rbt.insertRBTree(75);
	rbt.insertRBTree(57);
	rbt.insertRBTree(89);
	rbt.insertRBTree(90);
	rbt.insertRBTree(95);*/
	//rbt.insertRBTree(97);
	//rbt.insertRBTree(32);
	//rbt.insertRBTree(31);
	//rbt.insertRBTree(32);

	int a[] = { 55,40,65,60,75,57,89,90,95,97,32,31,35};
	int n = sizeof(a) / sizeof(int);
	rbt.createTree(a, n);
	rbt.display();
	cout << "--------------------\n";

	/*if (rbt.lookUp(36) != rbt.getNIL())
		cout << "Has 36\n";
	else
		cout << "Doesn't exist\n";
	cout << "Height: " << rbt.height(rbt.getRoot()) << endl;
	cout << "Black height: " << rbt.blackHeight(rbt.getRoot());*/



	return 0;
}