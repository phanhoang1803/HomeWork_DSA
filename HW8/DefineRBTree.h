#pragma once

// Tiêu chuẩn cây đỏ đen:
/*
	* Là cây nhị phân tìm kiếm
		* left < mid < right
	* Mỗi nút là nút đỏ hoặc đen
	* Nút gốc và NIL luôn là nút đen
	* Cha đỏ thì con đen
	* Mỗi đường đi từ một nút bất kỳ đến các nút lá đều có cùng số lượng các nút đen (Black Height)
*/

typedef struct RBNode* rbref;
struct RBNode {
	int key;
	bool color;		//Black = 0
	RBNode* parent;
	RBNode* left;
	RBNode* right;
};

