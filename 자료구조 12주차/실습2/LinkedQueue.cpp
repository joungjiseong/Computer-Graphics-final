#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

typedef int Item;
typedef struct node {
	Item nData;
	struct node *link;
}	Node, *NodePtr;

typedef struct {
	NodePtr pFront;
	NodePtr pRear;
}	Queue, *QueuePtr;

void main()
{
	int  IsEmptyQueue(QueuePtr pQueue);
	//int  IsFullQueue(QueuePtr pQueue);
	int  AddQueue(QueuePtr pQueue, Item nItem);
	int  DeleteQueue(QueuePtr pQueue, Item& nItem);
	void PrintQueue(QueuePtr pQueue);
	int  Error(char *sMsg);

	/** Create Queue **/
	Queue aQueue;
	aQueue.pFront = NULL;
	while (1) {
		int value;
		printf("-2:Exit -1:Delete, *:Add ? ");
		scanf("%d", &value);
		if (value < -1)
			break;
		else if (value == -1) {
			if (DeleteQueue(&aQueue, value) == false)
				Error("empty");
			else
				printf("%d is deleted\n", value);
		}
		else {
			if (AddQueue(&aQueue, value) == false)
				Error("full");
			else
				printf("%d is inserted\n", value);
		}
		PrintQueue(&aQueue);
	}
}

int IsEmptyQueue(QueuePtr pQueue)
{	// queue가 비었으면 true 아니면 false를 반환한다.
	return true;
}

int AddQueue(QueuePtr pQueue, Item nItem)
{	// queue에 nItem을 추가하고 성공하면 true 아니면 false를 반환한다.
	return true;
}

int DeleteQueue(QueuePtr pQueue, Item& nItem)
{	//queue에서 삭제하여 nItem에 저장하고 성공하면 true 아니면 false를 반환한다.
	return true;
}

void PrintQueue(QueuePtr pQueue)
{
	NodePtr pNode = pQueue->pFront;
	while (pNode) {
		printf("----");
		pNode = pNode->link;
	}
	printf("--\n");
	pNode = pQueue->pFront;
	while (pNode) {
		printf("%4d", pNode->nData);
		pNode = pNode->link;
	}
	printf("\n");
	pNode = pQueue->pFront;
	while (pNode) {
		printf("----");
		pNode = pNode->link;
	}
	printf("--\n\n");
}

int Error(char *sMsg)
{
	printf("***** Queue is %s. *****\n", sMsg);
	return -1;
}
