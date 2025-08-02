#include<iostream>
#include<string>
using namespace std;

struct HocVien {
	long maHV;
	string hoTen;
	short namSinh;
};

struct Node {
	HocVien value;
	Node* next;
};

void init(Node*& head) {
	head = NULL;
}

bool isEmpty(Node* head) {
	return head == NULL;
}

Node* createNode(HocVien hv) {
	Node* p = new Node;
	p->value = hv;
	p->next = NULL;

	return p;
}

void nhapHv(HocVien& hv) {
	cout << "Ma HV: "; 
	cin >> hv.maHV;
	cin.ignore();
	cout << "Ho va ten: "; 
	getline(cin, hv.hoTen);
	cout << "Nam sinh: "; 
	cin >> hv.namSinh;
}

void xuatHv(HocVien hv) {
	cout << "Ma HV: " << hv.maHV << endl;
	cout << "Ho va ten: " << hv.hoTen << endl;
	cout << "Nam sinh: " << hv.namSinh << endl;
}

void output(Node* head) {
	Node* p = head;
	while (p != NULL) {
		cout << endl;
		xuatHv(p->value);
		p = p->next;
	}
}

void insertAtFirst(Node*& head, HocVien hv) {
	Node* p = createNode(hv);
	p->next = head;
	head = p;
}

void insertAtLast(Node*& head, HocVien hv) {
	Node* p = createNode(hv);
	if (isEmpty(head)) {
		head = p;
	}
	else {
		Node* last = head;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = p;
	}
}

int insertAfter(Node*& head, long maHV, HocVien hv) {
	Node* p = head;
	while (p != NULL && p->value.maHV != maHV) {
		p = p->next;
	}
	if (p != NULL) {
		Node* q = createNode(hv);
		q->next = p->next;
		p->next = q;
		return true;
	}
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
		//Có nhiều phân tử
		if (p != head) {
			q->next = NULL;
		}
		//Có 1 phần tử
		else {
			head = NULL;
		}
		delete p;
		return true;
	}
	return false;
}

int delAt(Node*& head, long maHv) {
	if (!isEmpty(head)) {
		Node* p = head;
		Node* q = NULL;
		while (p != NULL && p->value.maHV != maHv) {
			q = p;
			p = p->next;
		}
		//Tìm thấy học viên mang mã học viên "maHv"
		if (p != NULL) {
			if (p != head) {
				q->next = p->next;
				delete p;
			}
			else {
				delAtFirst(head);
			}
		}
		return true;
	}
	//Danh sách rỗng hoặc không tìm thấy học viên nào có maHV
	return false;
}

void delAll(Node*& head) {
	while (!isEmpty(head)) {
		delAtFirst(head);
	}
}

Node* search(Node* head, long maHv) {
	Node* p = head;
	while (p != NULL && p->value.maHV != maHv) {
		p = p->next;
	}
	return p;
}

int main() {
	Node* head;
	init(head);
	
	cout << "Nhap hoc vien 1:\n";
	HocVien hv1;
	nhapHv(hv1);
	insertAtFirst(head, hv1);

	cout << "Nhap hoc vien 2:\n";
	HocVien hv2;
	nhapHv(hv2);
	insertAtFirst(head, hv2);

	cout << "Nhap hoc vien 3:\n";
	HocVien hv3;
	nhapHv(hv3);
	insertAtLast(head, hv3);

	cout << "Nhap hoc vien 4:\n";
	HocVien hv4;
	nhapHv(hv4);
	insertAtLast(head, hv4);

	cout << "=====DANH SACH HOC VIEN=====\n";
	output(head);

	long maHv;
	//cout << "=====XOA HOC VIEN=====\n";
	//cout << "Nhap ma so hoc vien: "; cin >> maHv;
	//if (delAt(head, maHv)) {
	//	cout << "Xoa thanh cong!\n";
	//	output(head);
	//}
	//else {
	//	cout << "Khong tim thay!\n";
	//}

	cout << "=====THEM VAO SAU MOT HOC VIEN=====\n";
	cout << "Nhap ma so hoc vien: "; cin >> maHv;
	cout << "Nhap thong tin hoc vien:\n";
	HocVien hv;
	nhapHv(hv);
	if (insertAfter(head, maHv, hv)) {
		cout << "Them thanh cong!\n";
		output(head);
	}
	else {
		cout << "Khong tim thay!\n";
	}

	delAll(head);
	return 0;
}