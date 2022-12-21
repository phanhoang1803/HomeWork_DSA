#include "RedBlackTree.h"

#define RED 1
#define BLACK 0

/*					PRIVATE						*/	

//	INFORMATION HELPER
rbref RedBlackTree::getNode(int key) {
	rbref res = new RBNode;

	res->color                           = RED; // Red
	res->key                             = key;
	res->left = res->right = res->parent = nil;

	return res;
}
rbref RedBlackTree::getRoot() {
	return root;
}
rbref RedBlackTree::getNIL() {
	return nil;
}
bool RedBlackTree::isLeaf(rbref node) {
	return node->left == nil && node->right == nil;
}

void RedBlackTree::displayHelper(rbref root, string indent, bool last) {
	if (root != nil) {
		cout << indent;
		if (last) {
			cout << "R----";
			indent += "   ";
		}
		else {
			cout << "L----";
			indent += "|  ";
		}

		string sColor = root->color == RED ? "RED" : "BLACK";
		cout << root->key << "(" << sColor << ")" << endl;
		displayHelper(root->left, indent, false);
		displayHelper(root->right, indent, true);
	}
}
int RedBlackTree::heightHelper(rbref root) {
	if (root == nil || isLeaf(root))
		return 0;

	int leftHeight = heightHelper(root->left);
	int rightHeight = heightHelper(root->right);

	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
int RedBlackTree::blackHeightHelper(rbref root) {
	int count = 0;

	rbref current = root;
	while (current != nil) {
		if (current->color == BLACK)
			count++;
		current = current->left != nil ? current->left : current->right;
	}

	return count;
}

//	ROTATE
void RedBlackTree::leftRotate(rbref x) {
	/*
				p							p
				|							|
				x							y
			   / \			 -->		   / \
			  +	  y						  x   +
				 / \                     / \
				z	+                   +   z
	*/
	rbref y = x->right;
	rbref z = y->left;
	rbref p = x->parent;

	// Couple z - x
	x->right = z;
	if (z != nil)
		z->parent = x;

	// Couple x - y
	x->parent = y;
	y->left = x;

	// Couple y - p
	y->parent = p;
	if (x == root)
		root = y;
	else
		if (p->left == x)
			p->left = y;
		else
			p->right = y;
}
void RedBlackTree::rightRotate(rbref x) {
	/*
				p						p
				|						|
				x						y
			   / \					   / \
			  y	  +			-->		  +	  x
			 / \						 / \
			+	z						z   +
	*/
	rbref y = x->left;
	rbref z = y->right;
	rbref p = x->parent;

	// Couple z - x
	x->left = z;
	if (z != nil)
		z->parent = x;

	// Couple x - y
	x->parent = y;
	y->right = x;

	// Couple y - p
	y->parent = p;
	if (x == root)
		root = y;
	else
		if (p->left == x)
			p->left = y;
		else
			p->right = y;
}

//	INSERT HELPER
void RedBlackTree::insertBinarySearchTree(rbref x) {
	rbref y = nil, z = root;
	while (z != nil) {
		y = z;
		if (x->key < z->key)
			z = z->left;
		else
			z = z->right;
	}
	x->parent = y;
	if (y == nil)
		root = x;
	else
		if (x->key < y->key)
			y->left = x;
		else
			y->right = x;
}
void RedBlackTree::insert_LeftAdjust(rbref& x) {
	// x: node is added recently
	// p: parent
	// u: uncle
	// g: grandparent
	rbref p, u, g;

	p = x->parent;
	g = p->parent;
	u = g->right;

	if (u->color == RED) { // COLOR: p = red, u = red
		p->color = BLACK;
		u->color = BLACK;
		g->color = RED;
		x = g;
	}
	else {
		if (x == p->right) {
			x = x->parent;
			leftRotate(x);
			/*x = p;
			p = x->parent;
			g = p->parent;*/
		}
		x->parent->color = BLACK;	// Nhánh trái 2 đỏ, cha và chú đen. Thì đưa 1 đỏ vào giữa cha và chú -> cân bằng xong.
		x->parent->parent->color = RED;
		rightRotate(x->parent->parent);
	}
}
void RedBlackTree::insert_RightAdjust(rbref& x) {
	// x: node is added recently
	// p: parent
	// u: uncle
	// g: grandparent
	rbref p, u, g;

	p = x->parent;
	g = p->parent;
	u = g->left;

	if (u->color == RED) {
		p->color = BLACK;
		u->color = BLACK;
		g->color = RED;
		x = g;
	}
	else {
		if (x == p->left) {
			x = x->parent;
			rightRotate(x);
		}
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		leftRotate(x->parent->parent);
	}
}
void RedBlackTree::insert_FixUp(rbref x) {
	while (x->parent->color == RED)
		if (x->parent == x->parent->parent->left)
			insert_LeftAdjust(x);
		else
			insert_RightAdjust(x);

	root->color = BLACK;
}


//	DELETE HELPER
rbref RedBlackTree::predecessor(rbref x) {
	if (x->left == nil || x->right == nil)
		return x;


	// Right most of the left subtree
	rbref y = x->left;
	while (y->right != nil) {
		y = y->right;
	}

	return y;
}
rbref RedBlackTree::successor(rbref x) {
	if (x->left == nil || x->right == nil)
		return x;


	// Right most of the left subtree
	rbref y = x->right;
	while (y->left != nil) {
		y = y->left;
	}

	return y;
}
void RedBlackTree::delete_LeftAdjust(rbref& x) {
	rbref w = x->parent->right;
	if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		leftRotate(x->parent);
		w = x->parent->right;
	}

	if (w->right->color == BLACK && w->left->color == BLACK) {
		w->color = RED;
		x = x->parent;
	}
	else {
		if (w->right->color == BLACK) {
			w->left->color = BLACK;
			w->color = RED;
			rightRotate(w);
			w = x->parent->right;
		}
		w->color = x->parent->color;
		x->parent->color = BLACK;
		w->right->color = BLACK;
		leftRotate(x->parent);
		x = root;
	}
}
void RedBlackTree::delete_RightAdjust(rbref& x) {
	rbref w = x->parent->left;
	if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		leftRotate(x->parent);
		w = x->parent->left;
	}

	if (w->right->color == BLACK && w->left->color == BLACK) {
		w->color = RED;
		x = x->parent;
	}
	else {
		if (w->left->color == BLACK) {
			w->right->color = BLACK;
			w->color = RED;
			leftRotate(w);
			w = x->parent->left;
		}
		w->color = x->parent->color;
		x->parent->color = BLACK;
		w->left->color = BLACK;
		rightRotate(x->parent);
		x = root;
	}
}
void RedBlackTree::delete_FixUp(rbref x) {
	// TH1: x là nút đỏ => Chỉ cần tô màu đỏ thành đen.
	// TH2, 3, 4: x là nút đen => cần cân bằng lại cây.
	// Dấu hiệu đen đi đi ngược về gốc.
	while (x->color == BLACK && x != root)
		if (x == x->parent->left)
			delete_LeftAdjust(x);
		else
			delete_RightAdjust(x);

	x->color = BLACK;
}

/*-----------------------------------------------------------*/

/*					PUBLIC						*/

//	STRUCTOR
RedBlackTree::RedBlackTree() {
	nil = new RBNode;

	nil->color = BLACK; // Black
	nil->left = nil->right = nil->parent = nil;

	root = nil;
}

//	INFORMATION
void RedBlackTree::display() {
	displayHelper(root, "", true);
}

//	PROCESSING
void RedBlackTree::insertRBTree(int key) {
	// x: node is added recently
	rbref x = getNode(key);
	insertBinarySearchTree(x);
	insert_FixUp(x);
}
void RedBlackTree::createTree(int a[], int n){
	for (int i = 0; i < n; i++)
		insertRBTree(a[i]);
}
rbref RedBlackTree::lookUp(int key) {
	rbref current = root;

	while (current != nil) {
		if (current->key == key)
			return current;
		if (key < current->key)
			current = current->left;
		else
			current = current->right;
	}

	return nil;
}
int RedBlackTree::height() { // 
	return heightHelper(root);
}
int RedBlackTree::blackHeight() { // Number of black node from root to any leaf
	return blackHeightHelper(root);
}
bool RedBlackTree::remove(int key) {
	rbref keyNode = lookUp(key);
	
	if (keyNode == nil)
		return false;

	rbref y = successor(keyNode); // y is the leaf or y just has 1 subtree
	rbref x = y->left != nil ? y->left : y->right;

	// Separate y from the tree
	x->parent = y->parent;
	if (y->parent == nil)
		root = x;
	else
		if (y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;

	// Fix delete
	keyNode->key = y->key;
	if (y->color == BLACK)
		delete_FixUp(x);

	// Delete
	delete y;

	return true;
}