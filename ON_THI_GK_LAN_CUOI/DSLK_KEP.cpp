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

bool isEmpty(List k) {
	return k.head == NULL || k.tail == NULL;
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

void themDau(List& k, int x) {
	Node* p = createNode(x);
	if (isEmpty(k)) {
		k.head = k.tail = p;
	}
	else {
		p->next = k.head;
		k.head->prev = p;
		k.head = p;
	}
}

void themCuoi(List& k, int x) {
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

int themSau(List& k, int key, int x) {
	Node* p = search(k, key);
	if (p != NULL) {
		Node* q = createNode(x);
		q->next = p->next;
		q->prev = p;
		p->next = q;
		if (q->next == NULL)
			k.tail = q;
		else
			q->next->prev = q;
		return 1;
	}
	return 0;
}

int xoaDau(List& k) {
	if (!isEmpty(k)) {
		Node* p = k.head;
		k.head = k.head->next;
		if (k.head == NULL)
			k.tail = NULL;
		else
			k.head->prev = NULL;
		delete p;
		return 1;
	}
	return 0;
}

int xoaCuoi(List& k) {
	if (!isEmpty(k)) {
		Node* p = k.tail;
		k.tail = k.tail->prev;
		if (k.tail == NULL)
			k.head = NULL;
		else
			k.tail->next = NULL;
		delete p;
		return 1;
	}
	return 0;
}

int xoaSau(List& k, int key) {
	Node* p = search(k, key);
	if (p != NULL) {
		Node* q = p->next;
		if (q != NULL) {
			p->next = q->next;
			if (p->next == NULL)
				k.tail = p;
			else
				p->next->prev = p;
			delete q;
			return 1;
		}
	}
	return 0;
}

void xoaTatCa(List& k) {
	while (!isEmpty(k)) {
		xoaDau(k);
	}
}

void output(List k) {
	Node* p = k.head;
	while (p != NULL) {
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

void output_reverse(List k) {
	Node* p = k.tail;
	while (p != NULL) {
		cout << p->value << " ";
		p = p->prev;
	}
	cout << endl;
}

void sapXep(List& k) {
	for (Node* i = k.head; i->next != NULL; i = i->next) { // for(int i = 0; i < n - 1; i++)
		for (Node* j = i->next; j != NULL; j = j->next) { // for(int j = i + 1; j < n; j++)
			if (i->value > j->value)
				swap(i->value, j->value);
		}
	}
}

int main() {
	List k;
	init(k);

	// 3 4 5 6 7
	themDau(k, 5);
	themDau(k, 4);
	themDau(k, 3);
	themCuoi(k, 6);
	themCuoi(k, 7);

	// 3 4 5 6 7
	output(k);

	themSau(k, 5, 10);

	// 3 4 5 10 6 7
	output(k);

	xoaSau(k, 7);

	// 3 4 10 6 7
	output(k);

	sapXep(k);
	output(k);

	xoaTatCa(k);
	return 0;
}