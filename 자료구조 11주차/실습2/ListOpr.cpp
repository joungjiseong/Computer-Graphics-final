#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

typedef struct node {
	int nData;
	struct node *link;
}	Node, *NodePtr;

void main()
{
	NodePtr Add(NodePtr pFirst, int nData);
	NodePtr Insert(NodePtr pFirst, int nData, NodePtr pPrev);
	NodePtr Delete(NodePtr pFirst, int nData);
	NodePtr Find(NodePtr pFirst, int nData);
	void PrintList(NodePtr pFirst);
	NodePtr pFirst = NULL;
	NodePtr pPrev = NULL;
	while (1) {
		printf("[aidfe] ? ");
		char sCmnd[10];
		gets_s(sCmnd);
		if (*sCmnd == 'e')
			return;
		printf("Data ? ");
		char sData[10];
		gets_s(sData);
		int nData = atoi(sData);
		switch (*sCmnd) {
		case 'a':
			pFirst = Add(pFirst, nData);
			break;
		case 'f':
			pPrev = Find(pFirst, nData);
			printf("%s\n", (pPrev) ? "Good" : "Bad");
			break;
		case 'i':
			pFirst = Insert(pFirst, nData, pPrev);
			break;
		case 'd':
			pFirst = Delete(pFirst, nData);
		}
		PrintList(pFirst);
	}
}

NodePtr Add(NodePtr pFirst, int nData)
{
	// pFirst가 가르키는 Linked List의 제일 앞에 nData를 가지는 노드를 삽입한다.
	// pFirst가 가르키는 Linked List는 노드가 하나도 없을 수도 있다.
	return pFirst;
}

NodePtr Find(NodePtr pFirst, int nData)
{
	// 노드의 데이타 값이 nData 값을 가지는 첫번째 노드를 찾아서 그 노드를 return한다.
	// 만약에 그러한 노드가 없으면 NULL을 return한다.
	return pFirst;
}

NodePtr Insert(NodePtr pFirst, int nData, NodePtr pPrev)
{
	// pFirst가 가르키는 Linked List에서 pPrev 노드 뒤에 nData를 가지는 노드를 삽입한다.
	// 만약 pPrev가 NULL이면 제일 앞에 삽입된다.
	// Insert 명령은 Find 명령을 수행하여 pPrev에 적당한 노드로 설정한 후에 실행된다고 가정한다.
	return pFirst;
}

NodePtr Delete(NodePtr pFirst, int nData)
{
	// 노드의 데이타 값이 nData 값을 가지는 첫번째 노드를 찾아서 그 노드를 삭제한다.
	// 노드를 삭제하기 위하여 이전 노드를 알아야 하는데 Find 함수의 알고리즘에서
	// 별도의 변수 pTrail를 만들어 바로 뒤에 따라 오게하고 
	// 현재의 노드가 찾는 노드이면 pTrail은 이전 노드가 된다.
	return pFirst;
}

void PrintList(NodePtr pNode)
{
	while (pNode) {
		printf("%d ", pNode->nData);
		pNode = pNode->link;
	}
	printf("\n\n");
}
