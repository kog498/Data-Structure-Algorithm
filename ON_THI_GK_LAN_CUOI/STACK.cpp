#include<iostream>
using namespace std;

#define MAX 100

void init(int arr[], int& sp) {
	sp = -1;
}

bool isEmpty(int arr[], int sp) {
	return sp == -1;
}

bool isFull(int arr[], int sp) {
	return sp == MAX - 1;
}

int push(int arr[], int& sp, int x) {
	if (!isFull(arr, sp)) {
		arr[++sp] = x;
		return 1;
	}
	return 0;
}

int pop(int arr[], int& sp, int& res) {
	if (!isEmpty(arr, sp)) {
		res = arr[sp--];
		return 1;
	}
	return 0;
}

void output(int arr[], int sp) {
	for (int i = sp; i >= 0; i--) {
		cout << arr[i] << endl;
	}
}

int main() {
	int arr[MAX];
	int sp; // sp lưu phần tử đỉnh
	init(arr, sp);

	int x;
	cout << "Nhap so thap phan: "; cin >> x;
	int temp = x;
	while (temp != 0) {
		push(arr, sp, temp % 2);
		temp = temp / 2;
	}

	while (!isEmpty(arr, sp)) {
		int res;
		pop(arr, sp, res);
		cout << res;
	}
	cout << endl;

	//push(arr, sp, 5);
	//push(arr, sp, 7);
	//push(arr, sp, 6);
	//push(arr, sp, 9);
	//push(arr, sp, 10);

	//output(arr, sp);
	//cout << endl;

	//int res;
	//pop(arr, sp, res);
	//output(arr, sp);
	//cout << "Pop result: " << res << endl;

	return 0;
}