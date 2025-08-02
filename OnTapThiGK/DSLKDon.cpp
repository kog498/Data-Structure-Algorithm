#include "LinkedList.h"

int main() {
	Node* head;
	init(head);
	insertAtFirst(head, 5);
	insertAtFirst(head, 4);
	insertAtLast(head, 6);
	insertAtLast(head, 7);
	output(head);
	//print(head);
	//delAtFirst(head);
	//print(head);
	//delAtLast(head);
	//print(head);
	//if (search(head, 9) != NULL) {
	//	cout << "Tim thay!\n";
	//}
	//else {
	//	cout << "Khong tim thay!\n";
	//}
	insertAfter(head, 4, 10);
	delAt(head, 6);
	output(head);

	delAll(head);
	return 0;
}