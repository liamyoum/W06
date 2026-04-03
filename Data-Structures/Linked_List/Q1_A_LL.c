//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item; // ListNode has item(int type)
	struct _listnode *next; // ListNode를 가리키는 포인터 next
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size; // Linked List has size(int type)
	ListNode *head; // ListNode를 가리키는 포인터 head
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item); // take 2 arguements(the address of Linked List and item)

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
	/* 유저에게 삽입하고 싶은 정수값 하나 입력 받고, 올바른 위치에 삽입
	연결 리스트는 이미 정렬된 리스트 혹은 빈 리스트로 가정
	조건: 정수값이 이미 연결 리스트에 있으면 return -1
	올바르게 삽입 되었을 경우 삽입된 위치의 인덱스 값 return */
int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
	
	/*
	logic:
	1. ListNode를 가리키는 포인터 cur과 인덱스를 나타내는 변수 idx 선언
	2. ll 자체가 null 이면 return -1
	3. ll->head->item == item 이면 return -1
	4. ll->head == NULL 이거나 ll->head->item이 삽입하려는 숫자보다 작으면 인덱스 0에 노드 삽입(insertNode 사용)
	5. cur->next != NULL 이면 cur로 연결 리스트 head부터 순행 순회(while문)
	6. 순회하면서 item == cur->next->item 이면 return -1
	7. 순회하면서 item < cur->next->item 이면 현재 인덱스 + 1 에 노드 삽입
	8. 순회하면서 item > cur->next->item 이면 cur = cur->next, idx++
	9. While문이 끝나면 현재 cur은 마지막 노드를 가리키는 포인터이고, 그 노드의 값에 대한 중복 검사는 순회하면서 진행 했으니 마지막 노드 인덱스 + 1에 삽입
	*/

	ListNode *cur;
	int idx = 0;

	// 리스트 자체가 없는 경우
	if (ll == NULL) {
		return -1;
	}
	// head가 가리키는 노드의 값이 item이랑 중복인 경우
	if (ll->head->item == item) {
		return -1;
	}
	// 리스트가 빈 리스트인 경우 혹은 빈 리스트는 아닌데 맨 앞에 넣어야하는 경우
	if (ll->head == NULL || ll->head->item > item) {
		insertNode(ll, 0, item);
		return 0;
	}

	cur = ll->head;

	while (cur->next != NULL) {
		// cur이 가리키는 노드의 다음 노드와 숫자가 같으면 return -1
		if (item == cur->next->item ) {
			return -1;
		}
		// cur이 가리키는 노드의 다음 노드보다 작으면
		if (item < cur->next->item) {
			insertNode(ll, idx + 1, item);
			return idx + 1;
		}
		// cur이 가리키는 노드의 다음 노드보다 숫자가 크면 이동
		cur = cur->next;
		idx++;
	}
	// while 문이 끝까지 가면 현재 cur은 마지막 노드를 가리키는 포인터, 이미 중복 검사는 위에서 했으므로 제일 큰 숫자임. 삽입만 하면 됨.
	insertNode(ll, idx + 1, item);
	return idx + 1;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur; // ListNode를 가리키는 포인터 cur
	if (ll == NULL) 
		return;
	cur = ll->head; // 연결리스트가 NULL이 아니면, 포인터 cur은 연결리스트의 head(포인터)를 가리킴. cur -> head -> the first node

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item); // 처음에는 head가 가리키는 첫 노드의 int item 값을 print
		cur = cur->next; // cur 포인터는 다음 노드를 가리킴
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur); // 노드 하나씩 다 메모리 할당 해제
		cur = tmp;
	}
	ll->head = NULL; // head 포인터도 NULL로 만들고
	ll->size = 0; // size도 0으로 할당
}


ListNode *findNode(LinkedList *ll, int index){ // 찾은 ListNode를 가리키는 포인터를 반환하는 함수 findNode

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){ 

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1) // 여기 그냥 index >= ll->size + 1 하든가 아니면 index > ll->size로 하는게 더 깔끔하지 않나?
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
