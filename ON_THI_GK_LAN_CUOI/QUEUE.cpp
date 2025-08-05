#include<iostream>
using namespace std;

#define MAX 100

void init(int arr[], int& front, int& rear) {
	front = -1;
	rear = -1;
}

bool isEmpty(int arr[], int front, int rear) {
	return front == -1 || rear == -1;
}

bool isFull(int arr[], int front, int rear) {
	return rear - front == MAX - 1;
}

int push(int arr[], int& front, int& rear, int x) {
	if (isFull(arr, front, rear)) {
		return 0;
	}
	if (front == -1)
		front = 0;
	if (rear == MAX - 1) {
		for (int i = front; i <= rear; i++) {
			arr[i - front] = arr[i];
		}
		rear = rear - front;
		front = 0;
	}
	arr[++rear] = x;
	return 1;
}

int pop(int arr[], int& front, int& rear, int& res) {
	if (isEmpty(arr, front, rear))
		return 0;
	res = arr[front++];
	if (front > rear) {
		front = -1;
		rear = -1;
	}
	return 1;
}

void output(int arr[], int front, int rear) {
	for (int i = front; i <= rear; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	int arr[MAX];
	int front, rear; // front phần tử mình sẽ lấy ra, rear là phần tử mình mới thêm vào
	init(arr, front, rear);
	push(arr, front, rear, 1);
	push(arr, front, rear, 2);
	push(arr, front, rear, 3);
	push(arr, front, rear, 4);
	push(arr, front, rear, 5);

	output(arr, front, rear);

	int res;
	pop(arr, front, rear, res);
	output(arr, front, rear);
	cout << res << endl;

	return 0;
}