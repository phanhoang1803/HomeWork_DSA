#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

#define NaN -1

typedef struct leader* lref;
typedef struct trailer* tref;

struct leader {
	int key;	
	int count;	// numbers of previous leaders
	lref next;	
	tref trail;	// list of trailers
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
	lref id;
	tref next;	
};

lref addLeader(bucket& list, int u, int& count) {
	lref iter = list.head;

	for (; iter != list.tail; iter = iter->next)
		//if there is a leader containing u
		if (iter->key == u)
			return iter;

	// if leader contaning u has not existed
	// addTail that leader
	list.tail = new leader{ NaN,0,NULL, NULL };
	count++;
	iter->next = list.tail;
	iter->key = u;

	return iter;
}

void addPair(bucket& list, int u, int v, int& count) {
	lref pu, pv;
	//add a pair to list
	pu = addLeader(list, u, count);
	pv = addLeader(list, v, count);

	//create a relationship between them
	tref path = new trailer{ pv, NULL };

	path->next = pu->trail;
	pu->trail = path;
	pv->count++;
}

//print topo list by graph theory
void printTopoOrder(bucket& list, int& count) {
	lref iter = list.head;
	queue<lref> q;
	vector<int> order;
	//push leaders whose indegree == 0
	for (; iter != list.tail; iter = iter->next)
		if (iter->count == 0)
			q.push(iter), count--;

	//while loop of queue
	while (!q.empty()) {
		//get each leader and print it
		lref p = q.front();
		q.pop();
		order.push_back(p->key);

		//unlock all its trailer
		for (tref t = p->trail; t; t = t->next)
			if (--t->id->count == 0)
				// if there is a leader whose indegree==0 appears
				// push it to queue
				q.push(t->id), count--;
	}

	//if topo order is not existed ( circle)
	if (count != 0)
	{
		cout << "Khong ton tai thu tu topo\n";
		return;
	}

	for (int i = 0; i < order.size(); i++)
		cout << order[i] << " ";
}

int main() {
	//open file
	fstream f;
	f.open("C:\\testDSA.txt", ios:: in);

	//if file can not be read
	if (!f)
		cout << "Error";
	else
	{
		// a pair of topo list
		int u, v;

		bucket list;

		//size of list
		int count = 0;

		//struct of each reading turn : (x,y)
		//temp variable used to read " ( , ) " and pass them.
		char temp;

		//while loop to add a pair
		while (1) {
			
			f >> temp;
			//if end of file
			if (f.eof())
				break;
			f >> u;
			f >> temp;
			f >> v;
			f >> temp;
			
			addPair(list, u, v, count);
		}
		//print list
		printTopoOrder(list, count);
	}


	return 0;
}