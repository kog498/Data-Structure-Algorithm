#include<iostream>

using namespace std;

struct Node {
	int value;
	Node* next;
	Node* prev;
};

struct List {
	Node* head;
	Node* tail;
};

void init(List& k) {
	k.head = NULL;
	k.tail = NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->value = x;
	p->next = NULL;
	p->prev = NULL;

	return p;
}

Node* search(List k, int x) {
	Node* p = k.head;
	while (p != NULL && p->value != x) {
		p = p->next;
	}
	return p;
}

bool isEmpty(List k) {
	return k.head == NULL || k.tail == NULL;
}

void insertAtFirst(List& k, int x) {
	Node* p = createNode(x);
	if (isEmpty(k)) {
		k.head = p;
		k.tail = p;
	}
	else {
		p->next = k.head;
		k.head->prev = p;
		k.head = p;
	}
}

void insertAtLast(List& k, int x) {
	Node* p = createNode(x);
	if (isEmpty(k)) {
		k.head = k.tail = p;
	}
	else {
		p->prev = k.tail;
		k.tail->next = p;
		k.tail = p;
	}
}

int insertAfter(List& k, int key, int x) {
	Node* p = search(k, key);
	//Tìm thấy
	if (p != NULL) {
		Node* q = createNode(x);
		q->next = p->next;
		q->prev = p;
		p->next = q;
		if (q->next == NULL)
			k.tail = q;
		else
			q->next->prev = q;
		return true;
	}
	return false;
}

int delAtFirst(List& k) {
	if (!isEmpty(k)) {
		Node* p = k.head;
		k.head = k.head->next;
		if (k.head == NULL)
			k.tail = NULL;
		else
			k.head->prev = NULL;
		delete p;
		return true;
	}
	return false;
}

int delAtLast(List& k) {
	if (!isEmpty(k)) {
		Node* p = k.tail;
		k.tail = k.tail->prev;
		if (k.tail == NULL)
			k.head = NULL;
		else
			k.tail->next = NULL;
		delete p;
		return true;
	}
	return false;
}

int delAt(List& k, int x) {
	Node* p = search(k, x);
	if (p != NULL) {
		if (p == k.head)
			delAtFirst(k);
		else if (p == k.tail)
			delAtLast(k);
		else {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
		}
		return true;
	}
	return false;
}

int delAfter(List& k, int x) {
	Node* p = search(k, x);
	if (p != NULL) {
		Node* q = p->next;
		if (q != NULL) {
			p->next = q->next;
			if (p->next == NULL)
				k.tail = p;
			else
				p->next->prev = p;
			delete q;
			return true;
		}
	}
	return false;
}

void delAll(List& k) {
	while (!isEmpty(k)) {
		delAtFirst(k);
	}
}

bool def(int x) {
	return true;
}

bool isEven(int x) {
	return x % 2 == 0;
}

void output(List k, bool func(int) = def) {
	Node* p = k.head;
	while (p != NULL) {
		if (func(p->value))
			cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

void reverseOutput(List k, bool func(int) = def) {
	Node* p = k.tail;
	while (p != NULL) {
		if (func(p->value))
			cout << p->value << " ";
		p = p->prev;
	}
	cout << endl;
}