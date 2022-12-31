#pragma once
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
