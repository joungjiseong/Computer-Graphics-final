#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

typedef struct node {
	int nData;
	struct node *link;
}	Node, *NodePtr;

void main()
{
	char cmnd[10], data[10];
	NodePtr add(NodePtr pLast, int nData);
	NodePtr del(NodePtr pLast, int *pnData);
	NodePtr invert(NodePtr pNode);
	void print(NodePtr pNode);

	int nData;
	Node *pLast = NULL;
	cmnd[0] = 'a';
	while (cmnd[0]) {
		printf("\n[azdie] ? ");
		gets_s(cmnd);
		switch (*cmnd) {
		case 'a':
		case 'z':
			printf(" ? ");
			gets_s(data);
			pLast = add(pLast, atoi(data));	// 일단은 앞에다 삽입하고
			if (*cmnd == 'z')
				pLast = pLast->link;		// 하나 전진하면 끝에 넣는 효과
			break;
		case 'd':
			if (pLast) {
				pLast = del(pLast, &nData);
				printf("%d is deleted\n", nData);
			}
			else
				printf("empty list\n");
			break;
		case 'i':
			pLast = invert(pLast);
			break;
		case 'e':
			return;
		}
		print(pLast);
	}
}

NodePtr add(NodePtr pLast, int nData)
{
	// nData를 가지는 노드를 첫 노드로 삽입한다.
	NodePtr pNode = (NodePtr)malloc(sizeof(Node));
	if (pNode == NULL)
		return pLast;
	pNode->nData = nData;
	if (pLast == NULL)
		pLast = pNode->link = pNode;
	else {
		pNode->link = pLast->link;
		pLast->link = pNode;
	}
	return pLast;
}

NodePtr del(NodePtr pLast, int *pnData)
{
	// 첫번째 노드를 삭제하고 그 값은 pnData에 저장한다.
	if (pLast) {
		NodePtr pNode = pLast->link;	// 첫 노드
		*pnData = pNode->nData;			// 첫 노드의 데이타
		if (pLast->link == pLast)		// 한 노드만 있는 경우
			pLast = NULL;
		else
			pLast->link = pNode->link;
		free(pNode);
	}
	return pLast;
}

NodePtr invert(NodePtr pLast)
{
	// 순환 리스트를 거꾸로 뒤집는다.
	if (pLast) {
		NodePtr pNode = pLast = pLast->link;	// 첫노드를 마지막 노드로
		NodePtr pTrail = NULL;					// 순환을 끊기 위하여
		while (pNode) {
			NodePtr pTemp = pTrail;
			pTrail = pNode;
			pNode = pNode->link;
			pTrail->link = pTemp;
		}
	}
	return pLast;
}

void print(NodePtr pLast)
{
	if (pLast == NULL)
		return;
	NodePtr pNode = pLast;
	do {
		pNode = pNode->link;
		printf("%d ", pNode->nData);
	} while (pNode != pLast);
	printf("\n");
}
