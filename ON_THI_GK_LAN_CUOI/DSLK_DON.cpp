#include<iostream>
using namespace std;

struct Node {
	int value;
	Node* next;
};

// Khởi tạo danh sách rỗng
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

Node* search(Node* head, int x) {
	Node* p = head;
	while (p != NULL && p->value != x) {
		p = p->next;
	}
	return p;
}

//Thêm đầu
void themDau(Node*& head, int x) {
	Node* p = createNode(x);
	p->next = head;
	head = p;
}

//Thêm cuối
void themCuoi(Node*& head, int x) {
	if (isEmpty(head))
		head = createNode(x);
	else {
		Node* last = head;
		//Tìm phần tử cuối danh sách
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = createNode(x);
	}
}

//Thêm giữa (Thêm sau 1 phần tử)
int themSau(Node*& head, int key, int x) {
	Node* p = search(head, key);
	//Nếu tìm thấy phần tử mang giá trị key
	if (p != NULL) {
		Node* q = createNode(x);
		q->next = p->next;
		p->next = q;
		return 1;
	}
	return 0;
}

//Xóa đầu
int xoaDau(Node*& head) {
	if (!isEmpty(head)) {
		Node* p = head;
		head = head->next;
		delete p;
		return 1;
	}
	return 0;
}

//Xóa cuối
int xoaCuoi(Node*& head) {
	if (!isEmpty(head)) {
		Node* p = head;
		Node* q = NULL;
		while (p->next != NULL) {
			q = p;
			p = p->next;
		}
		//Nếu danh sách chỉ có 1 phần tử
		if (p == head)
			head = NULL;
		else
			q->next = NULL;
		delete p;
		return 1;
	}
	return 0;
}

int xoaSau(Node*& head, int key) {
	Node* p = search(head, key);
	if (p != NULL) {
		Node* q = p->next;
		if (q != NULL) {
			p->next = q->next;
			delete q;
			return 1;
		}
	}
	return 0;
}

void xoaTatCa(Node*& head) {
	while (!isEmpty(head)) {
		xoaDau(head);
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

void sapXep(Node*& head) {
	for (Node* i = head; i->next != NULL; i = i->next) { // for(int i = 0; i < n - 1; i++)
		for (Node* j = i->next; j != NULL; j = j->next) { // for(int j = i + 1; j < n; j++)
			if (i->value > j->value)
				swap(i->value, j->value);
		}
	}
}

int main() {
	Node* head;
	init(head);

	// 6 4 5 9 10
	themDau(head, 5);
	themDau(head, 4);
	themDau(head, 6);
	themCuoi(head, 9);
	themCuoi(head, 10);

	output(head);

	// 6 4 99 5 9 10
	themSau(head, 4, 99);

	output(head);

	// 6 4 99 5 10
	xoaSau(head, 10);
	output(head);

	sapXep(head);
	output(head);

	//xoaDau(head);
	//xoaDau(head);

	//output(head);

	xoaTatCa(head);
	return 0;
}