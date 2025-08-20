//lab 5, 6, 7: cai dat DFS, BFS
#include <iostream>
#include <fstream>
#define MAXSIZE 100
using namespace std;
char vertex[MAXSIZE];
int a[MAXSIZE][MAXSIZE];
int n;
int C[MAXSIZE];
int dfs[MAXSIZE];
int ndfs = 0;
int bfs[MAXSIZE];
int nbfs = 0;

//ma tran ke
void inputMatrix(int a[][MAXSIZE], int &n)
{
	do{
		cout << "Nhap so luong dinh cua do thi: ";
		cin >> n;
	} while(n <= 0 || n > MAXSIZE);
	cout << "Nhap ten cua " << n << " dinh: ";
	for (int i = 0; i < n; i++)
		cin >> vertex[i];
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap cac thong tin ke/ khong ke giua dinh " << i 
			<< " voi cac dinh con lai: ";
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	}
}
void inputMatrixFromFile(int a[][MAXSIZE], int &n)
{
	ifstream inF;
	inF.open("Lab7.txt");
	if (inF.is_open())
	{
		inF >> n;
		for (int i = 0; i < n; i++)
			inF >> vertex[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				inF >> a[i][j];
		inF.close();
		cout << "Doc ma tran ke thanh cong\n";
	}
	else
		cout << "Mo file khong thanh cong\n";
}
void output(int a[][MAXSIZE], int n)
{
	for(int i = 0; i < n; i++)
		cout << "\t" << vertex[i];
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << vertex[i];
		for (int j = 0; j < n; j++)
			cout << "\t" << a[i][j];
		cout << endl;
	}
}
int search(char b[], int n, char v) //v la dinh can xet, mang b la mang chua ten cac dinh cua do thi
{
	for(int i = 0; i < n; i++)
		if (b[i] == v)
			return i;
	return -1;
}
void searchMatrix(int a[][MAXSIZE], int n, char v)
{
	int kq = search(vertex, n, v);
	if (kq == -1)
	{
		cout << "Dinh khong ton tai trong do thi\n";
		return;
	}
	cout << "Cac dinh ke voi dinh " << v << " la: ";
	for (int j = 0; j < n; j++)
		if (a[kq][j] == 1)
			cout << vertex[j] << " ";
}

//Danh sach ke
struct Node
{
	int info; //thu tu cua dinh // int weight
	Node *link;
};
Node *first[MAXSIZE];
int size;
void init()
{
	for(int i = 0; i < size; i++)
		first[i] = NULL;
}
Node *createNode(int x)
{
	Node *p = new Node;
	if (!p) return NULL;
	p->info = x;
	p->link = NULL;
	return p;
}
void insert_First(Node *&f, int x)
{
	Node *p = createNode(x);
	if (!p) 
	{
		cout << "Khong the them node vao danh sach\n";
		return;
	}
	p->link = f;
	f = p;
}
void inputList()
{
	do{
		cout << "Nhap so luong dinh cua do thi: ";
		cin >> size;
	} while(size <= 0 || size > MAXSIZE);
	cout << "Nhap ten cua cac dinh trong do thi: ";
	for(int i = 0; i < size; i++)
		cin >> vertex[i];
	for (int i = 0; i < size; i++)
	{
		//dua dinh dang xet vao danh sach
		insert_First(first[i], i);
		//dua cac dinh ke voi dinh i vao ds
		int x;
		cout << "Nhap cac dinh ke voi dinh " << i << " ket thuc nhan -1: ";
		do{
			cin >> x;
			if (x == -1) break;
			insert_First(first[i], x);
		} while(x != -1);
	}
}
void outputList()
{
	for(int i = 0; i < size; i++)
	{
		cout << "Danh sach cac dinh ke voi dinh " << vertex[i] << ": ";
		Node *p = first[i];
		//D -> C -> B -> A
		while (p->link != NULL)
		{
			cout << vertex[p->info] << " ";
			p = p->link;
		}
		cout << endl;
	}
}

//stack (ho tro duyet cac dinh do thi bang DFS)
Node *st; //stack
void init_Stack()
{
	st = NULL;
}
bool isEmpty_Stack()
{
	if(st == NULL) return true;
	return false;
}
void push_Stack(int x)
{
	Node *p = new Node;
	if(p == NULL) return;
	p->info = x;
	p->link = st;
	st = p;
}
void pop_Stack(int &gt)
{
	if(!isEmpty_Stack())
	{
		Node *p = st;
		gt = p->info;
		st = st->link;
		delete p;
	}
}
void process_Stack()
{
	Node *p = st;
	if(p == NULL) 
	{
		cout << "Stack rong\n";
		return;
	}
	cout << "Stack hien tai (tu dinh stack):\n";
	while(p != NULL)
	{
		cout << p->info << "\n";
		p = p->link;
	}
	cout << endl;
}

//dfs
void initEdges()
{
	for(int i = 0; i < n; i++)
		C[i] = 1;
}
void DFS(int s)
{
	initEdges();
	init_Stack();
	push_Stack(s);
	dfs[ndfs++] = s;
	C[s] = 0;
	int u = s;
	int v = -1;
	while(!isEmpty_Stack())
	{
		if(v == n)
			pop_Stack(u);
		for(v = 0; v < n; v++)
			if(a[u][v] == 1 && C[v] == 1)
			{
				push_Stack(u);
				push_Stack(v);
				dfs[ndfs++] = v;
				C[v] = 0;
				u = v;
				break;
			}
	}
}
void output_1DArray(int a[], int size)
{
	for(int i = 0; i < size; i++)
		cout << vertex[a[i]] << " ";
	cout << endl;
}
//tim kiem 1 dinh x co trong do thi hay khong bang DFS bat dau duyet tu dinh s
//tim duoc duong di bang DFS cho viec tim kiem
//tinh tong trong so duong di bang DFS da di qua
void search_DFS(int s, int x) //tim x bat dau tu s
{
	initEdges();
	init_Stack();
	push_Stack(s);
	//dfs[ndfs++] = s;
	C[s] = 0;
	int u = s;
	int v = -1;
	while(!isEmpty_Stack())
	{
		if(v == n)
			pop_Stack(u);
		for(v = 0; v < n; v++)
			if(a[u][v] != 0 && C[v] == 1)
			{
				push_Stack(u);
				push_Stack(v);
				//dfs[ndfs++] = v;
				C[v] = 0;
				if(v == x)
				{
					cout << x << " co trong do thi\n";
					return;
				}
				u = v;
				break;
			}
	}
	cout << x << " khong co trong do thi\n";
}
//queue (ho tro duyet cac dinh do thi bang BFS)
Node *front, *rear;
void init_Queue()
{
	front = rear = NULL;
}
int isEmpty_Queue()
{
	if(front == NULL)
		return 1;
	return 0;
}
void push_Queue(int x)
{
	Node *p = new Node;
	if(p == NULL) return;
	p->info = x;
	p->link = NULL;
	if(rear == NULL)
		front = p;
	else
		rear->link = p;
	rear = p;
}
void pop_Queue(int &x)
{
	if(front != NULL)
	{
		Node *p = front;
		x = p->info;
		front = front->link;
		if(front == NULL)
			rear = NULL;
		delete p;
	}
}

//bfs
void BFS(int s)
{
	initEdges();
	init_Queue();
	push_Queue(s);
	C[s] = 0;
	while (!isEmpty_Queue())
	{
		int p;
		pop_Queue(p);
		bfs[nbfs++] = p;
		for(int i = 0; i < n; i++)
			if(C[i] == 1 && a[p][i] == 1)
			{
				push_Queue(i);
				C[i] = 0;
			}
	}
}

//search vertex from graph by BFS
void search_by_BFS(int s, int x) //s la dinh bat dau, x la dinh can tim
{
	initEdges();
	init_Queue();
	nbfs = 0;
	push_Queue(s);
	C[s] = 0;
	while(!isEmpty_Queue())
	{
		int p;
		pop_Queue(p);
		if(p == x)
		{
			bfs[nbfs++] = p;
			cout << x << " co trong do thi\n";
			//xuat duong di tu s den x
			cout << "Duong di tu dinh " << vertex[s] << " den dinh " << vertex[x] 
				<< " bang BFS la: ";
			output_1DArray(bfs, nbfs);
			return;
		}
		bfs[nbfs++] = p;
		for(int i = 0; i < n; i++)
			if(C[i] && a[p][i] != 0)
			{
				push_Queue(i);
				C[i] = 0;
			}
	}
	cout << x << " khong co trong do thi\n";
}
void main()
{
	inputMatrixFromFile(a, n);
	cout << "\nMa tran trong so:\n";
	output(a, n);	
	
	search_DFS(0, 8);
}

