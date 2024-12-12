#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

typedef int Item;
typedef struct node {
	Item nData;
	struct node *link;
}	Node, *NodePtr, *StackPtr;

void main()
{
	int  IsEmptyStack(StackPtr pStack);
	// int  IsFullStack(StackPtr pStack);
	int  Push(StackPtr& pStack, Item nItem);
	int  Pop(StackPtr& pStack, Item& nItem);
	void PrintStack(StackPtr pStack);
	int  Error(char *sMsg);

	/** Create Stack **/
	StackPtr pStack = NULL;
	while (1) {
		Item value;
		printf("-2:Exit -1:Pop, *:Push ? ");
		scanf("%d", &value);
		if (value < -1)
			break;
		else if (value == -1) {
			if (Pop(pStack, value) == false)
				Error("empty");
			else
				printf("%d is deleted\n", value);
		}
		else {
			if (Push(pStack, value) == false)
				Error("full");
			else
				printf("%d is inserted\n", value);
		}
		PrintStack(pStack);
	}
}

int IsEmptyStack(StackPtr pStack)
{
	// stack이 비었으면 true 아니면 false를 반환한다.
	return true;
}

int Push(StackPtr& pStack, Item nItem)
{
	// stack에 nItem을 push하고 성공하면 true 아니면 false를 반환한다.
	return true;
}

int Pop(StackPtr& pStack, Item& nItem)
{
	// stack에서 pop하여 nItem에 저장하고 성공하면 true 아니면 false를 반환한다.
	return true;
}

void PrintStack(StackPtr pNode)
{
	printf("|    |\n");
	while (pNode) {
		printf("|%3d |\n", pNode->nData);
		pNode = pNode->link;
	}
	printf("+----+\n\n");
}

int Error(char *sMsg)
{
	printf("***** Stack is %s. *****\n", sMsg);
	return false;
}
