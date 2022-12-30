#include <iostream>
#include <queue>

using namespace std;

#define NaN -1

typedef struct leader* lref;
typedef struct trailer* tref;

struct leader {
	int key;	// Chứa dữ liệu
	int count;	// Số lượng trailer trỏ đến nó
	lref next;	// Leader tiếp theo
	tref trail;	// Quản lý danh sách trailer
};
struct bucket {
	lref head;
	lref tail;

	bucket() {
		head = new leader{ NaN, 0, NULL, NULL };
		tail = head;
	}
};
struct trailer {
	lref id;	// Leader nó trỏ đến
	tref next;	// Trailer tiếp theo
};

lref addLeader(bucket& list, int u, int& count) {
	lref iter = list.head;

	for (; iter != list.tail; iter = iter->next)
		// Nếu đã có u, trả về leader của u.
		if (iter->key == u)
			return iter;

	// Nếu chưa có u, add vào cuối.
	list.tail = new leader{ NaN,0,NULL, NULL };
	count++;
	iter->next = list.tail;
	iter->key = u;

	return iter;
}

void addPair(bucket& list, int u, int v, int& count) {
	lref pu, pv;
	pu = addLeader(list, u, count);
	pv = addLeader(list, v, count);

	tref path = new trailer{ pv, NULL };

	path->next = pu->trail;
	pu->trail = path;
	pv->count++;
}

void printTopoOrder(bucket& list, int& count) {
	lref iter = list.head;
	queue<lref> q;
	vector<int> order;
	for (; iter != list.tail; iter = iter->next)
		if (iter->count == 0)
			q.push(iter), count--;

	while (!q.empty()) {	
		lref p = q.front();
		q.pop();
		order.push_back(p->key);
		for (tref t = p->trail; t; t = t->next)
			if (--t->id->count == 0)
				q.push(t->id), count--;
	}

	if (count != 0)
		cout << "Error\n";

	for (int i = 0; i < order.size(); i++)
		cout << order[i] << " ";
}

int main() {
	/*
	1 2
	2 4
	4 6
	2 10
	4 8
	6 3
	1 3
	3 5
	5 8
	7 5
	7 9
	9 4
	9 10
	*/
	bucket list;
	int count = 0;
	while (1) {
		int u, v;
		cout << "Enter pair u - v: ";
		cin >> u >> v;
		if (!u && !v)
			break;
		addPair(list, u, v, count);
	}

	printTopoOrder(list, count);

	return 0;
}