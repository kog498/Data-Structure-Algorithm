#include "DoubleLinkedList.h"

int main() {
	List k;
	init(k);
	insertAtFirst(k, 5);
	insertAtFirst(k, 4);
	insertAtLast(k, 8);
	insertAtLast(k, 9);
	output(k);
	//insertAfter(k, 9, 10);
	//output(k);
	//reverseOutput(k);
	delAfter(k, 8);
	output(k);
	reverseOutput(k);
	output(k, isEven);

	delAll(k);
	return 0;
}