//lab 5.1
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
#define MAX 20
int A[MAX][MAX];
int n;
char vertex[MAX];
int C[MAX];
int bfs[MAX];
int nbfs = 0;

/************/
//graph
void init()
{
	n = 0;
}
void inputGraphFromKey()
{
	cout << "Nhap so dinh cua do thi: ";
	do{
		cin >> n;
		if (n < 1 || n > MAX)
			cout << "Nhap lai: ";
	} while(n < 1 || n > MAX);
	cout << "Nhap ten tung dinh cua do thi: ";
	for (int i = 0; i < n; i++)
		cin >> vertex[i];
	cout << "Nhap gia tri cho ma tran ke:\n";
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap cac gia tri ke cho dinh " << vertex[i] << ": ";
		for (int j = 0; j < n; j++)
			cin >> A[i][j];
	}
}
void inputGraphFromFile()
{
	ifstream inFile;
	inFile.open("BT5_1.txt");
	if (inFile.is_open())
	{
		inFile >> n;
		for (int i = 0; i < n; i++)
			inFile >> vertex[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				inFile >> A[i][j];
		cout << "Doc file thanh cong\n";
		inFile.close();
	}
	else
		cout << "Mo file khong thanh cong\n";	
}
void outputGraph()
{
	cout << "\t";
	for (int i = 0; i < n; i++)
		cout << vertex[i] << "\t";
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << vertex[i] << "\t";
		for (int j = 0; j < n; j++)
			cout << A[i][j] << "\t";
		cout << endl;
	}
}
/************/
//QUEUE
struct Node
{
	int info;
	Node *link;
};
Node *front, *rear;
void init_Q()
{
	front = rear = NULL;
}
void Push(int x)
{
	Node *p = new Node;
	p->info = x;
	p->link = NULL;
	if (rear == NULL)
		front = p;
	else
		rear->link = p;
	rear = p;
}
void Pop(int &x)
{
	if (front != NULL)
	{
		Node *p = front;
		front = p->link;
		x = p->info;
		if (front == NULL)
			rear = NULL;
		delete p;
	}
}
/******/
//BFS
void initC()
{
	for (int i = 0; i < n; i++)
		C[i] = 1;
}
void BFS(int v)
{
	initC();
	init_Q();
	int w, p;
	Push(v);
	C[v] = 0;
	while (front != NULL)
	{
		Pop(p);
		bfs[nbfs++] = p;
		for (w = 0; w < n; w++)
			if (C[w] && A[p][w] == 1)
			{
				Push(w);
				C[w] = 0;
			}
	}
}
void output_BFS()
{
	for (int i = 0; i < nbfs; i++)
	{
		cout << vertex[bfs[i]];
		if (i < nbfs - 1)
			cout << ", ";		 
	}
	cout << endl;
}
/******/

int main()
{
	int chon;
	bool in = false;
	do{
		system("cls");
		cout << "Menu\n1. Khoi tao do thi\n2. Nhap ma tran ke tu ban phim\n3. Nhap ma tran ke tu file\n"
			<< "4. Xuat ma tran ke\n5. Duyet BFS\n6. Thoat\nBan chon: ";
		cin >> chon;
		switch(chon)
		{
		case 1:
			init();
			in = true;
			break;
		case 2:
			if (in)
				inputGraphFromKey();
			else
				cout << "Hay khoi tao do thi\n";
			break;
		case 3:
			if (in)
				inputGraphFromFile();
			else
				cout << "Hay khoi tao do thi\n";
			break;
		case 4:
			if (in)
				outputGraph();
			else
				cout << "Khoi tao\n";
			break;
		case 5:
			int v;
			cout << "Nhap dinh bat dau duyet bfs: ";
			cin >> v;
			BFS(v);
			cout << "Day ket qua duyet duoc tu bfs: ";
			output_BFS();
			break;
		default:
			cout << "Ban chon thoat\n";
		}
		_getch();
	} while(chon >= 1 && chon <= 4);
}