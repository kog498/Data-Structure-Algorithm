#include<iostream>
#include<fstream>
using namespace std;

#define MAX 10

//Ma Trận Kề
int arr[MAX][MAX];
int n;
char vertex[MAX]; // Tập đỉnh

void init() {
	n = 0;
}

void inputGraphFromKey() {
	cout << "Nhap so dinh cua do thi: ";
	do {
		cin >> n;
		if (n < 1 || n > MAX)
			cout << "Nhap lai: "; cin >> n;
	} while (n < 1 || n > MAX);
	cout << "Nhap ten tung dinh cua do thi:\n";
	for (int i = 0; i < n; i++)
		cin >> vertex[i];
	cout << "Nhap gia tri cho ma tran ke:\n";
	for (int i = 0; i < n; i++) {
		cout << "Nhap cac gia tri ke cho dinh " << vertex[i] << ":\n";
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	}
}

void inputGraphFromFile() {
	ifstream fin("BT5_1.txt");
	if (fin.is_open()) {
		fin >> n;
		for (int i = 0; i < n; i++)
			fin >> vertex[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				fin >> arr[i][j];
		cout << "Doc file thanh cong!\n";
		fin.close();
	}
	else {
		cout << "Da co loi xay ra khi mo file!\n";
	}
}

void outputGraph() {
	cout << "\t";
	for (int i = 0; i < n; i++) {
		cout << vertex[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << vertex[i] << "\t";
		for (int j = 0; j < n; j++)
			cout << arr[i][j] << "\t";
		cout << endl;
	}
}

//Queue
struct Node {
	int info;
	Node* link;
};

Node* front, * rear;

void initQ() {
	front = NULL;
	rear = NULL;
}

void pushQ(int x) {
	Node* p = new Node;
	p->info = x;
	p->link = NULL;
	if (rear == NULL)
		front = p;
	else
		rear->link = p;
	rear = p;
}

int popQ(int& x) {
	if (front != NULL) {
		Node* p = front;
		x = p->info;
		front = front->link;
		if (front == NULL)
			rear = NULL;
		delete p;
		return 1;
	}
	return 0;
}

//Duyet BFS (Queue)
int C[100], bfs[100];
int nbfs = 0;

void initC() {
	for (int i = 0; i < n; i++) // n la so dinh cua do thi
		C[i] = 1;
}

void BFS(int v) {
	int w, p;
	initC();
	initQ;
	pushQ(v);
	C[v] = 0;
	while (front != NULL) {
		popQ(p);
		bfs[nbfs++] = p;
		for (w = 0; w < n; w++)
			if (C[w] && arr[p][w] == 1) {
				pushQ(w);
				C[w] = 0;
			}
	}
}

void outputBFS() {
	for (int i = 0; i < nbfs; i++)
		cout << vertex[bfs[i]] << " ";
	cout << endl;
}

void searchBFS(int s, int x) {
	initC();
	initQ();
	nbfs = 0;
	pushQ(s);
	C[s] = 0;
	while (front != NULL) {
		int p;
		popQ(p);
		if (p == x) {
			bfs[nbfs++] = p;
			cout << x << " co trong do thi\n";
			cout << "Duong di tu dinh " << vertex[s] << " den dinh " << vertex[x]
				<< " bang BFS la: ";
			outputBFS();
			return;
		}
		bfs[nbfs++] = p;
		for (int i = 0; i < n; i++)
			if (C[i] != 0 && arr[p][i] != 0) {
				pushQ(i);
				C[i] = 0;
			}
	}
	cout << x << " khong co trong do thi\n";
}

//Stack
Node* sp;

void initS() {
	sp = NULL;
}

void pushS(int x) {
	Node* p = new Node;
	p->info = x;
	p->link = sp;
	sp = p;
}

int popS(int& x) {
	if (sp != NULL) {
		x = sp->info;
		Node* p = sp;
		sp = sp->link;
		delete p;
		return 1;
	}
	return 0;
}

//Duyet DFS (STACK)
int C2[100], dfs[100];
int ndfs = 0;

void initC2() {
	for (int i = 0; i < n; i++)
		C[i] = 1;
}

void DFS(int s) {
	initC2();
	initS();
	pushS(s);
	dfs[ndfs++] = s;
	C[s] = 0;
	int v = -1, u = s;
	while (sp != NULL) {
		if (v == n)
			popS(u);
		for (v = 0; v < n; v++)
			if (arr[u][v] != 0 && C[v] == 1) {
				pushS(u);
				pushS(v);
				dfs[ndfs] = v;
				ndfs++;
				C[v] = 0;
				u = v;
				break;
			}
	}
}

void outputDFS() {
	for (int i = 0; i < ndfs; i++) {
		cout << vertex[dfs[i]] << " ";
	}
	cout << endl;
}

void searchDFS(int s, int x) {
	initC2();
	initS();
	pushS(s);
	C[s] = 0;
	int u = s, v = -1;
	while (sp != NULL) {
		if (v == n)
			popS(u);
		for (v = 0; v < n; v++)
			if (arr[u][v] != 0 && C[v] == 1) {
				pushS(u);
				pushS(v);
				C[v] = 0;
				if (v == x) {
					cout << x << " co trong do thi\n";
					return;
				}
				u = v;
				break;
			}
	}
	cout << x << " khong co trong do thi\n";
}

int main() {
	int chon;
	do {
		cout << "----------- BAI TAP 4, CHUONG 5, DO THI -----------\n";
		cout << "1. Khoi tao MA TRAN KE rong\n";
		cout << "2. Nhap MA TRAN KE tu file text\n";
		cout << "3. Nhap MA TRAN KE\n";
		cout << "4. Xuat MA TRAN KE\n";
		cout << "5. Duyet do thi theo chieu rong BFS - MTK\n";
		cout << "6. Duyet do thi theo chieu sau DFS - MTK\n";
		cout << "7. Tim dinh co gia tri x theo DFS\n";
		cout << "8. Tim dinh co gia tri x theo BFS\n";
		cout << "0. Thoat\n";
		cout << endl;
		cout << "Vui long chon so de thuc hien: "; cin >> chon;
		system("cls");
		switch (chon) {
		case 1:
			cout << "----- Khoi tao MA TRAN KE rong -----\n";
			init();
			cout << "Da khoi tao ma tran rong thanh cong!\n";
			break;
		case 2:
			cout << "----- Nhap MA TRAN KE tu file text -----\n";
			inputGraphFromFile();
			break;
		case 3:
			cout << "----- Nhap MA TRAN KE -----\n";
			inputGraphFromKey();
			break;
		case 4:
			cout << "----- Xuat MA TRAN KE -----\n";
			outputGraph();
			break;
		case 5:
		{
			int x;
			cout << "----- Duyet do thi theo chieu rong BFS - MTK -----\n";
			cout << "Nhap dinh bat dau: "; cin >> x;
			BFS(x);
			outputBFS();
			break;
		}
		case 6:
		{
			int x;
			cout << "----- Duyet do thi theo chieu sau DFS - MTK -----\n";
			cout << "Nhap dinh bat dau: "; cin >> x;
			DFS(x);
			outputDFS();
			break;
		}
		case 7:
		{
			int v, x;
			cout << "----- Tim dinh co gia tri x theo DFS -----\n";
			cout << "Nhap dinh bat dau tim: "; cin >> v;
			cout << "Nhap dinh can tim: "; cin >> x;
			searchDFS(v, x);
			break;
		}
		case 8:
		{
			int v, x;
			cout << "----- Tim dinh co gia tri x theo BFS -----\n";
			cout << "Nhap dinh bat dau tim: "; cin >> v;
			cout << "Nhap dinh can tim: "; cin >> x;
			searchBFS(v, x);
			break;
		}
		case 0:
			cout << "Cam on vi da su dung chuong trinh! Hen gap lai!\n";
			break;
		default:
			cout << "Lua chon khong hop le! Nhap lai!\n";
		}
	} while (chon != 0);
	return 0;
}