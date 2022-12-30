#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
typedef struct bucket* bref;
typedef struct node* nref;
struct bucket
{
	int id;
	nref head, tail;
	bref next = NULL;
};


struct node
{
	int key;
	nref next = NULL;
};

struct blist {
	bref head = NULL;
	bref tail = NULL;
};

struct nlist {
	nref head, tail;
};
void addTail(nref& head, nref& tail, nref n) {
	tail->next = n;
	tail = n;
}
void addBucket(blist& l, bref& b)
{
	//apply guarding technique
	bref btail = new bucket;
	btail->id = -1;
	if (!l.head)
	{
		//if list is empty
		l.head = b;

		l.tail = btail;
		//link head and tail to create list
		l.head->next = l.tail;
		return;
	}
	bref run = l.head;
	bref prun = l.head; //prev bucket of run

	//loop while to find the insert location
	while (run->id < b->id && run != l.tail) {
		prun = run;
		run = run->next;
	}

	//check if the location is l.head
	if (run == l.head) {
		b->next = l.head;
		l.head = b;
	}
	else {
		b->next = prun->next;
		prun->next = b;
	}
}
// check whether a bucket containing id exist or not
bref isExist(blist l, int id) {
	bref run = l.head;

	//if list is empty
	if (!l.head)
		return NULL;

	//esle
	//find the location to insert bucket
	while (run->id != id) {
		if (run->next == l.tail)
			return NULL;
		run = run->next;
	}
	return run;
}
void addNum(blist& l, int num, int exp, int k) {
	//id of num
	int id = (num / exp) % (int)pow(10, k);
	//node of num
	nref n = new node;
	n->key = num;

	//check the existance of bucket containing id
	bref exist = isExist(l, id);

	if (!exist) {
		//bucket has not existed

		//construct bucket
		bref b = new bucket;
		b->head = n;
		b->tail = n;
		b->id = id;

		//insert bucket
		addBucket(l, b);
	}
	else {
		//bucket existed
		addTail(exist->head, exist->tail, n);
	}

}

vector<int> show(blist l) {
	//output vector
	vector<int> rs;

	bref h = l.head;
	bref t = l.tail;

	while (h != t) {
		nref run = h->head;
		while (run != NULL) {
			rs.push_back(run->key);
			run = run->next;
		}
		//cout << h->id << " ";
		h = h->next;
	}
	return rs;

}
//get max element of a vector
int getMax(vector<int> arr, int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}
void RadixSort(vector<int>& v, int exp, int k) {
	blist l;
	for (int i = 0; i < v.size(); i++)
		addNum(l, v[i], exp, k);
	v.clear();
	v = show(l);
}

int main() {
	fstream f;
	
	//read file
	f.open("C:\\testDSA.txt", ios::in);
	if (!f) {	//if file can not be read
		cout << "Error!\n";
		return 0;
	}



	int k, n;
	int num;
	f >> k >> n;

	vector<int> vec;
	for (int i = 0; i < n; i++)
	{
		f >> num;
		vec.push_back(num);
	}
	int s = pow(10, k);				//10^k is a step
	int max = getMax(vec, n);		//get max to limit the exp


	//for each exp: from 1	 100	10000	1000000 ...
	for (int exp = 1; max / exp > 0; exp *= s) {
		RadixSort(vec, exp, k);
	}


	//sorted 
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";







	return 0;
}