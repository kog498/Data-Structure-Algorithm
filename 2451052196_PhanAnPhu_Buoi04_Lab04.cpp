#include<iostream>
#include<random>
#include<ctime>
using namespace std;

struct Node {
	int data;
	Node* pLeft;
	Node* pRight;
};

void init(Node*& root) {
	root = NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->data = x;
	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
}

bool isEmpty(Node* root) {
	return root == NULL;
}

int insert(Node*& root, int x) {
	if (isEmpty(root)) {
		root = createNode(x);
	}
	else {
		Node* p = root;
		Node* q = NULL;
		while (p != NULL) {
			if (p->data == x) {
				return false;
			}
			else if (p->data > x) {
				q = p;
				p = p->pLeft;
			}
			else {
				q = p;
				p = p->pRight;
			}
		}
		p = createNode(x);
		if (q->data > x) {
			q->pLeft = p;
		}
		else {
			q->pRight = p;
		}
	}
	return true;
}

void input(Node*& root) {
	int x;
	do {
		cout << " > Nhap x: "; cin >> x;
		if (x != -1)
			insert(root, x);
	} while (x != -1);
}

void genTree(Node*& root) {
	for (int i = 1; i <= rand() % 10 + 10 + 1; i++) { // rand() % (max - min) + min + 1: Without negative
		insert(root, rand() % 1716 - 358 + 1); // rand() % (max + min) - min + 1: Has negative
	}
}

void printNLR(Node* root) {
	if (!isEmpty(root)) {
		cout << root->data << "\t" << root << "\tpLeft: " << root->pLeft << "\tpRight: " << root->pRight << endl;
		printNLR(root->pLeft);
		printNLR(root->pRight);
	}
}

void printLNR(Node* root) {
	if (!isEmpty(root)) {
		printLNR(root->pLeft);
		cout << root->data << "\t" << root << "\tpLeft: " << root->pLeft << "\tpRight: " << root->pRight << endl;
		printLNR(root->pRight);
	}
}

void printLRN(Node* root) {
	if (!isEmpty(root)) {
		printLRN(root->pLeft);
		printLRN(root->pRight);
		cout << root->data << "\t" << root << "\tpLeft: " << root->pLeft << "\tpRight: " << root->pRight << endl;
	}
}

Node* search(Node* root, int x) {
	Node* p = root;
	while (p != NULL && p->data != x) {
		if (p->data > x)
			p = p->pLeft;
		else
			p = p->pRight;
	}
	return p;
}

void searchStandFor(Node*& p, Node*& q) {
	if (q->pLeft == NULL) {
		p->data = q->data;
		p = q;
		q = q->pRight;
	}
	else
		searchStandFor(p, q->pLeft);
}

int remove(Node*& root, int x) {
	if (isEmpty(root))
		return false;
	if (root->data == x) {
		Node* p = root;
		if (root->pLeft == NULL)
			root = root->pRight;
		else if (root->pRight == NULL)
			root = root->pLeft;
		else
			searchStandFor(p, root->pRight);
		delete p;
		return true;
	}
	if (root->data > x)
		return remove(root->pLeft, x);
	if (root->data < x)
		return remove(root->pRight, x);
}

void removeAll(Node*& root) {
	while (!isEmpty(root)) {
		remove(root, root->data);
	}
}

bool def(int a, int b) {
	return true;
}

bool isSmaller(int node, int x) {
	return node < x;
}

bool isGreater(int node, int x) {
	return node > x;
}

int count(Node* root) {
	if (isEmpty(root)) {
		return 0;
	}
	return 1 + count(root->pLeft) + count(root->pRight);
}

int countLeaf(Node* root) {
	if (isEmpty(root))
		return 0;
	if (root->pLeft == NULL && root->pRight == NULL)
		return 1 + count(root->pLeft) + count(root->pRight);
	return count(root->pLeft) + count(root->pRight);
}

int countWithCmp(Node* root, int x, bool cmpFunc(int node, int x)) {
	if (isEmpty(root)) {
		return 0;
	}
	if (cmpFunc(root->data, x)) {
		return 1 + countWithCmp(root->pLeft, x, cmpFunc) + countWithCmp(root->pRight, x, cmpFunc);
	}
	return countWithCmp(root->pLeft, x, cmpFunc) + countWithCmp(root->pRight, x, cmpFunc);
}

int countRange(Node* root, int x, int y) {
	if (isEmpty(root))
		return 0;
	if (isGreater(root->data, x) && isSmaller(root->data, y))
		return 1 + countRange(root->pLeft, x, y) + countRange(root->pRight, x, y);
	return countRange(root->pLeft, x, y) + countRange(root->pRight, x, y);
}

bool isEven(int x) {
	return x % 2 == 0;
}

bool isOdd(int x) {
	return x % 2 != 0;
}

int countIf(Node* root, bool func(int)) {
	if (isEmpty(root))
		return 0;
	if (func(root->data))
		return 1 + countIf(root->pLeft, func) + countIf(root->pRight, func);
	return countIf(root->pLeft, func) + countIf(root->pRight, func);
}

/*
Returned values:
- Positive: Smaller-Than-X Nodes > Greater-Than-X Nodes
- Negative: Smaller-Than-X Nodes < Greater-Than-X Nodes
- Zero: Smaller-Than-X Nodes = Greater-Than-X Nodes
*/
int cmpCountWithCmp(Node* root, int x) {
	int smaller = countWithCmp(root, x, isSmaller);
	int greater = countWithCmp(root, x, isGreater);
	return smaller - greater;
}

/*
Returned values:
- Positive: Even Nodes > Odd Nodes
- Negative: Even Nodes < Odd Nodes
- Zero: Even Nodes = Odd Nodes
*/
int cmpCountIf(Node* root) {
	int even = countIf(root, isEven);
	int odd = countIf(root, isOdd);
	return even - odd;
}

int sum(Node* root) {
	if (isEmpty(root))
		return 0;
	return root->data + sum(root->pLeft) + sum(root->pRight);
}

int sumIf(Node* root, bool func(int)) {
	if (isEmpty(root))
		return 0;
	if (func(root->data))
		return root->data + sumIf(root->pLeft, func) + sumIf(root->pRight, func);
	return sumIf(root->pLeft, func) + sumIf(root->pRight, func);
}

/*
Returned values:
- Positive: Even Sum > Odd Sum
- Negative: Even Sum < Odd Sum
- Zero: Even Sum = Odd Sum
*/
int cmpSumIf(Node* root) {
	int even = sumIf(root, isEven);
	int odd = sumIf(root, isOdd);
	return even - odd;
}

Node* findMax(Node* root) {
	if (isEmpty(root))
		return NULL;
	Node* p = root;
	while (p->pRight != NULL) {
		p = p->pRight;
	}
	return p;
}

Node* findMin(Node* root) {
	if (isEmpty(root))
		return NULL;
	Node* p = root;
	while (p->pLeft != NULL) {
		p = p->pLeft;
	}
	return p;
}

// Viet toi day thoi con ben duoi bo

// emoji (* - *) 
void insEmj1() {
	cout << "(* - *) ";
}

// emoji (^ - ^)
void insEmj2() {
	cout << "(^ - ^) ";
}

// emoji (- _ -)
void insEmj3() {
	cout << "(- _ -) ";
}

// emoji (^ ~ ^)
void insEmj4() {
	cout << "(^ ~ ^) ";
}

// emoji (? - ?)
void insEmj5() {
	cout << "(? - ?) ";
}

void showHeader(Node* root, string title) {
	cout << title << "\n\n";
	cout << "$Hien tai:\n";
	printLNR(root);
	cout << endl;
}

enum Message {
	RESULT
};

string msg[] = {
	"$Ket qua:\n"
};

void emptyTree() {
	system("cls");
	insEmj5();
	cout << "Vui long tao cay truoc khi thuc hien dieu nay!\n";
}

void invalidChoice() {
	insEmj5();
	cout << "Lua chon khong hop le, vui long nhap lai!\n";
}

void repeatValue() {
	insEmj3();
	cout << "Gia tri bi trung mat roi!\n";
}

int main() {
	srand(time(0));
	Node* root;
	init(root);

	short choice;
	int x;
	do {
		cout << "=====================================\n";
		cout << "CHUONG TRINH CAY NHI PHAN TIM KIEM\n";
		cout << " 1. Nhap node cho cay\n";
		cout << " 2. Chen them node vao cay\n";
		cout << " 3. Tao cay tu dong\n";
		cout << " 4. Duyet cay nhi phan\n";
		cout << " 5. Tim kiem va thay the/xoa\n";
		cout << " 6. Xoa toan bo node\n";
		cout << " 7. Thong ke\n";
		cout << " 8. Tinh tong\n";
		cout << " 9. Tim gia tri lon nhat va nho nhat\n";
		cout << " 0. Thoat chuong trinh\n";
		cout << "> Nhap lua chon: "; cin >> choice;
		system("cls");
		insEmj1();
		switch (choice) {
		case 1:
			showHeader(root, "NHAP NODE VAO CAY");
			cout << "$Luu y:\n";
			cout << " > Nhap -1 de ket thuc.\n";
			cout << " > Neu cay da co node roi thi viec nhap\n";
			cout << "   tuong dong voi viec chen them node\n\n";
			cout << "$Bat dau nhap:\n";
			input(root);
			cout << endl;
			cout << msg[RESULT];
			printLNR(root);
			break;
		case 2:
			showHeader(root, "CHEN THEM NODE VAO CAY");
			cout << "$Nhap gia tri can them: "; cin >> x;
			if (insert(root, x)) {
				insEmj2();
				cout << "Da them node thanh cong!\n\n";
				cout << msg[RESULT];
				printLNR(root);
			}
			else {
				repeatValue();
			}
			break;
		case 3:
			if (isEmpty(root)) {
				cout << "TAO CAY TU DONG\n";
				genTree(root);
				cout << endl;
				cout << msg[RESULT];
				printLNR(root);
			}
			else {
				system("cls");
				insEmj5();
				cout << "Ban da tao cay roi, vui long chon nhap\n";
				cout << "hoac chen them node cho cay!\n";
			}
			break;
		case 4:
		{
			int n;
			if (!isEmpty(root)) {
				cout << "DUYET CAY NHI PHAN\n";
				cout << " 1. Theo LNR\n";
				cout << " 2. Theo NLR\n";
				cout << " 3. Theo LRN\n";
				do {
					cout << "> Nhap lua chon: "; cin >> n;
					if (n < 1 || n > 3) {
						invalidChoice();
					}
				} while (n < 1 || n > 3);
				cout << msg[RESULT];

				switch (n) {
				case 1:
					printLNR(root);
					break;
				case 2:
					printNLR(root);
					break;
				case 3:
					printLRN(root);
					break;
				}
			}
			else {
				emptyTree();
			}
			break;
		}
		case 5:
		{
			if (!isEmpty(root)) {
				int n;
				showHeader(root, "TIM KIEM VA THAY THE/XOA");
				cout << "$Nhap node can tim: "; cin >> n;
				Node* res = search(root, n);
				if (res != NULL) {
					insEmj2();
					cout << "Da tim thay node nay!\n";
					cout << "$Ban co muon thay the hoac xoa?\n";
					cout << " 1. Thay the\n";
					cout << " 2. Xoa\n";
					cout << " 0. Khong\n";
					do {
						cout << "> Nhap lua chon: "; cin >> n;
						switch (n) {
						case 1:
							cout << "$Vui long nhap gia tri moi: "; cin >> n;
							if (insert(root, n)) {
								remove(root, res->data);
								insEmj2();
								cout << "Da thay the thanh cong!\n\n";
								cout << msg[RESULT];
								printLNR(root);
							}
							else {
								repeatValue();
							}
							break;
						case 2:
							remove(root, res->data);
							insEmj2();
							cout << "Da xoa thanh cong!\n\n";
							cout << msg[RESULT];
							printLNR(root);
							break;
						case 0:
							break;
						default:
							invalidChoice();
						}
					} while (n < 0 || n > 2);
				}
				else {
					insEmj5();
					cout << "Khong tim thay!\n";
				}
			}
			else {
				emptyTree();
			}
			break;
		}
		case 6:
		{
			if (!isEmpty(root)) {
				int n;
				showHeader(root, "XOA TOAN BO NODE");
				cout << "$Ban co chac se xoa toan bo node trong cay?\n";
				cout << " 1. Xac nhan\n";
				cout << " 2. Huy bo\n";
				do {
					cout << "> Nhap lua chon: "; cin >> n;
					if (n != 1 && n != 2)
						invalidChoice();
				} while (n != 1 && n != 2);

				if (n == 1) {
					removeAll(root);
					insEmj2();
					cout << "Da xoa toan bo node trong cay!\n";
				}
				else {
					insEmj1();
					cout << "Da huy bo!\n";
				}
			}
			else {
				emptyTree();
			}
			break;
		}
		case 7:
		{
			if (!isEmpty(root)) {
				int n;
				showHeader(root, "THONG KE");
				cout << " 1. Dem so node trong cay\n";
				cout << " 2. Dem so node la trong cay\n";
				cout << " 3. Dem so node <x\n";
				cout << " 4. Dem so node >x\n";
				cout << " 5. Dem so node >x va <y\n";
				cout << " 6. Dem so node chan va le\n";
				cout << " 7. So sanh so luong node <x va >x\n";
				cout << " 8. So sanh so luong node chan va le\n";
				do {
					cout << "> Nhap lua chon: "; cin >> n;
					if (n < 1 || n > 8)
						invalidChoice();
				} while (n < 1 || n > 8);

				switch (n) {
				case 1:
					insEmj1();
					cout << "So node trong cay: " << count(root) << endl;
					break;
				case 2:
					insEmj1();
					cout << "So node la trong cay: " << countLeaf(root) << endl;
					break;
				case 3:
					cout << "$Nhap x: "; cin >> n;
					insEmj1();
					cout << "So node <" << n << ": " << countWithCmp(root, n, isSmaller) << endl;
					break;
				case 4:
					cout << "$Nhap x: "; cin >> n;
					insEmj1();
					cout << "So node <" << n << ": " << countWithCmp(root, n, isGreater) << endl;
					break;
				case 5:
				{
					int y;
					cout << "$Nhap x: "; cin >> n;
					cout << "$Nhap y: "; cin >> y;
					insEmj1();
					cout << "So node <" << n << " va >" << y << ": " << countRange(root, n, y) << endl;
					break;
				}
				case 6:
					insEmj1();
					cout << endl;
					cout << "> So node chan: " << countIf(root, isEven) << endl;
					cout << "> So node le: " << countIf(root, isOdd) << endl;
					break;
				case 7:
				{
					cout << "$Nhap x: "; cin >> n;
					insEmj1();
					int res = cmpCountWithCmp(root, n);
					if (res > 0) {
						cout << "Node <" << n << " nhieu hon node >" << n << endl;
					}
					else if (res < 0) {
						cout << "Node >" << n << " nhieu hon node <" << n << endl;
					}
					else {
						cout << "Bang nhau\n";
					}
					break;
				}
				case 8:
				{
					insEmj1();
					int res = cmpCountIf(root);
					if (res > 0) {
						cout << "Node chan nhieu hon node le\n";
					}
					else if (res < 0) {
						cout << "Node le nhieu hon node chan\n";
					}
					else {
						cout << "Bang nhau\n";
					}
					break;
				}
				}
			}
			else {
				emptyTree();
			}
			break;
		}
		case 8:
		{
			if (!isEmpty(root)) {
				int n;
				showHeader(root, "TINH TONG");
				cout << "$Ban muon tinh tong theo:\n";
				cout << " 1. Tat ca cac node\n";
				cout << " 2. Node chan & le\n";
				do {
					cout << "> Nhap lua chon: "; cin >> n;
					if (n != 1 && n != 2)
						invalidChoice();
				} while (n != 1 && n != 2);

				if (n == 1) {
					insEmj1();
					cout << "Tong tat ca cac node: " << sum(root) << endl;
				}
				else {
					insEmj1();
					cout << endl;
					cout << "> Tong node chan: " << sumIf(root, isEven) << endl;
					cout << "> Tong node le: " << sumIf(root, isOdd) << endl;
					n = cmpSumIf(root);
					if (n > 0) {
						cout << "=> Tong chan > tong le\n";
					}
					else if (n < 0) {
						cout << "=> Tong le > tong chan\n";
					}
					else {
						cout << "=> Tong chan va le bang nhau\n";
					}
				}
			}
			else {
				emptyTree();
			}
			break;
		}
		case 9:
			if (!isEmpty(root)) {
				showHeader(root, "TIM GIA TRI LON NHAT VA NHO NHAT");
				cout << msg[RESULT];
				cout << "> Gia tri lon nhat: " << findMax(root)->data << endl;
				cout << "> Gia tri nho nhat: " << findMin(root)->data << endl;
			}
			else {
				emptyTree();
			}
			break;
		case 0:
			system("cls");
			insEmj4();
			cout << "Cam on vi da su dung chuong trinh! Tam biet!\n";
			break;
		default:
			invalidChoice();
		}
	} while (choice != 0);


	removeAll(root);
	return 0;
}
