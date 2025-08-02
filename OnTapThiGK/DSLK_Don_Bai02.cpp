#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

struct NhanVien {
	string hoTen;
	double luong;
	string chucVu;
	string queQuan;
};

struct Node {
	NhanVien value;
	Node* next;
};

void init(Node*& head) {
	head = NULL;
}

Node* createNode(NhanVien nv) {
	Node* p = new Node;
	p->value = nv;
	p->next = NULL;

	return p;
}

bool isEmpty(Node* head) {
	return head == NULL;
}

void insertAtLast(Node*& head, NhanVien nv) {
	Node* p = createNode(nv);
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

int readFile(Node*& head) {
	ifstream fin("StaffList.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			NhanVien nv;
			getline(fin, nv.hoTen);
			fin >> nv.luong;
			fin.ignore();
			getline(fin, nv.chucVu);
			getline(fin, nv.queQuan);

			insertAtLast(head, nv);
		}

		fin.close();
		return true;
	}
	return false;
}

void xuat1NV(NhanVien nv) {
	cout << "Ho va ten: " << nv.hoTen << endl;
	cout << "Muc luong: " << fixed << setprecision(0) << nv.luong << endl;
	cout << "Chuc vu: " << nv.chucVu << endl;
	cout << "Que quan: " << nv.queQuan << endl;
}

void output(Node* head) {
	Node* p = head;
	while (p != NULL) {
		cout << endl;
		xuat1NV(p->value);
		p = p->next;
	}
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

void delAll(Node*& head) {
	while (!isEmpty(head)) {
		delAtFirst(head);
	}
}

Node* searchWithName(Node* head, string key) {
	Node* p = head;
	while (p != NULL && p->value.hoTen != key) {
		p = p->next;
	}
	return p;
}

Node* searchWithSalary(Node* head, double key) {
	Node* p = head;
	while (p != NULL && p->value.luong != key) {
		p = p->next;
	}
	return p;
}

void sortWithName(Node*& head) {
	for (Node* i = head; i->next != NULL; i = i->next) {
		for (Node* j = i->next; j != NULL; j = j->next) {
			if (j->value.hoTen < i->value.hoTen) {
				swap(j->value, i->value);
			}
		}
	}
}

void sortWithSalary(Node*& head) {
	for (Node* i = head; i->next != NULL; i = i->next) {
		for (Node* j = i->next; j != NULL; j = j->next) {
			if (j->value.luong < i->value.luong) {
				swap(j->value, i->value);
			}
		}
	}
}

bool isAvailable(string arr[], int n, string hometown) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == hometown)
			return true;
	}
	return false;
}

// Danh sách đặc: Dong Thap, Ho Chi Minh
int outFile(Node* head) {
	if (!isEmpty(head)) {
		string hometown[34];
		int n = 0;
		Node* p = head;
		while (p != NULL) {
			if (!isAvailable(hometown, n, p->value.queQuan)) {
				hometown[n] = p->value.queQuan;
				n++;
			}
			p = p->next;
		}
		for (int i = 0; i < n; i++) {
			ofstream fout(hometown[i] + ".txt");
			if (fout.is_open()) {
				p = head;
				while (p != NULL) {
					if (p->value.queQuan == hometown[i]) {
						fout << p->value.hoTen << endl
							<< p->value.luong << endl
							<< p->value.chucVu << endl
							<< p->value.queQuan << endl;
					}
					p = p->next;
				}
				cout << "Xuat file thanh cong!\n";
				fout.close();
			}
		}
		return true;
	}
	return false;
}

int main() {
	Node* head;
	init(head);

	if (readFile(head)) {
		cout << "Doc file thanh cong!\n";
		output(head);

		//Sử dụng hàm tìm kiếm
		//string key;
		//cout << "=====TIM KIEM THEO TEN=====\n";
		//cout << "Nhap ten can tim: "; getline(cin, key);
		//Node* p = searchWithName(head, key);
		//if (p != NULL) {
		//	cout << "\nKet qua tim thay:\n";
		//	xuat1NV(p->value);
		//}
		//else {
		//	cout << "\nKhong tim thay!\n";
		//}

		//Sắp xếp
		//cout << "\nSau khi sap xep\n";
		//sortWithName(head);
		//output(head);

		outFile(head);
	}
	else {
		cout << "Da co loi khi doc file!\n";
	}

	delAll(head);
	return 0;
}