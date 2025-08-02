#include<iostream>
using namespace std;

struct Node {
	int value;
	Node* next;
};

void init(Node*& head) {
	head = NULL;
}

bool isEmpty(Node* head) {
	return head == NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->value = x;
	p->next = NULL;

	return p;
}

void insertAtFirst(Node*& head, int x) {
	Node* p = createNode(x);
	p->next = head;
	head = p;
}

void insertAtLast(Node*& head, int x) {
	Node* p = createNode(x);
	if (isEmpty(head)) {
		head = p;
	}
	else {
		// Tìm node cuối cùng, dấu hiệu: 5 4 [2 -> NULL]
		Node* last = head;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = p;
	}
}

int insertAfter(Node*& head, int key, int x) {
	Node* p = head;
	while (p != NULL && p->value != key) {
		p = p->next;
	}
	//Nếu tìm thấy node chứa giá trị x
	if (p != NULL) {
		Node* q = createNode(x);
		q->next = p->next;
		p->next = q;
		return true;
	}
	//Không tìm thấy
	return false;
}

int delAtFirst(Node*& head) {
	if (!isEmpty(head)) {
		Node* p = head;
		head = head->next;
		delete p;
		return true;
	}
	return false;
}

int delAtLast(Node*& head) {
	if (!isEmpty(head)) {
		Node* p = head;
		Node* q = NULL;
		while (p->next != NULL) {
			q = p;
			p = p->next;
		}
		//Nếu ds có nhiều phần tử
		if (p != head) {
			q->next = NULL;
		}
		//Ds chỉ có 1 phần tử
		else {
			head = NULL;
		}
		delete p;

		return true;
	}
	return false;
}

int delAt(Node*& head, int key) {
	if (!isEmpty(head)) {
		Node* p = head;
		Node* q = NULL;
		while (p != NULL && p->value != key) {
			q = p;
			p = p->next;
		}
		//Nếu tìm thấy node có giá trị key
		if (p != NULL) {
			//Nếu node chứa giá trị key ở sau head
			if (p != head) {
				q->next = p->next;
				delete p;
			}
			//Nếu node chứa giá trị key ở ngay head
			else {
				delAtFirst(head);
			}
			return true;
		}
	}
	//Nếu ds rỗng hoặc không tìm thấy node có giá trị key
	return false;
}

void delAll(Node*& head) {
	while (!isEmpty(head)) {
		delAtFirst(head);
	}
}

void output(Node* head) {
	Node* p = head;
	while (p != NULL) {
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

Node* search(Node* head, int x) {
	Node* p = head;
	while (p != NULL && p->value != x) {
		p = p->next;
	}
	return p;
}