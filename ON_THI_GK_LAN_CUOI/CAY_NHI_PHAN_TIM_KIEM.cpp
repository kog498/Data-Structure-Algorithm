#include<iostream>
using namespace std;

struct Node {
	int value;
	Node* pLeft;
	Node* pRight;
};

void init(Node*& root) {
	root = NULL;
}

bool isEmpty(Node* root) {
	return root == NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->value = x;
	p->pLeft = NULL;
	p->pRight = NULL;

	return p;
}

void add(Node*& root, int x) {
	if (root == NULL)
		root = createNode(x);
	else {
		if (root->value == x)
			return;
		else if (root->value > x)
			return add(root->pLeft, x);
		else
			return add(root->pRight, x);
	}
}

Node* search(Node* root, int x) {
	if (root == NULL)
		return NULL;
	if (root->value == x)
		return root;
	else if (root->value > x)
		return search(root->pLeft, x);
	else
		return search(root->pRight, x);
}

bool def(int x) {
	return true;
}

int count(Node* root, bool func(int) = def) {
	if (root == NULL)
		return 0;
	if (func(root->value))
		return 1 + count(root->pLeft, func) + count(root->pRight, func);
	return count(root->pLeft, func) + count(root->pRight, func);
}

void outputLNR(Node* root) {
	if (root != NULL) {
		outputLNR(root->pLeft);
		cout << root->value << " ";
		outputLNR(root->pRight);
	}
}

void searchStandFor(Node*& p, Node*& q) {
	if (q->pLeft == NULL) {
		p->value = q->value;
		p = q;
		q = q->pRight;
	}
	else
		searchStandFor(p, q->pLeft);
}

int remove(Node*& root, int x) {
	if (root == NULL)
		return 0;
	if (root->value == x) {
		Node* p = root;
		if (root->pLeft == NULL)
			root = root->pRight;
		else if (root->pRight == NULL)
			root = root->pLeft;
		else
			searchStandFor(p, root->pRight);
		delete p;
		return 1;
	}
	if (root->value > x)
		return remove(root->pLeft, x);
	if (root->value < x)
		return remove(root->pRight, x);
}

int main() {
	Node* root;
	init(root);
	add(root, 5);
	add(root, 4);
	add(root, 3);
	add(root, 6);
	outputLNR(root);

	if (search(root, 9))
		cout << "Tim thay!\n";
	else
		cout << "Ko\n";
	cout << count(root) << endl;

	return 0;
}