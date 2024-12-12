#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS	100
#pragma warning (disable: 4996)

typedef struct {
	int nData;
	int nOtherData;
}	Element;

void main()
{
	void InsertHeap(Element heap[], Element anItem, int& n);
	Element DeleteHeap(Element heap[], int& nCtr);

	Element heap[MAX_ELEMENTS + 1];
	int nCtr = 0;
	Element item;
	srand((unsigned)time(NULL));
	while (1) {
		int nMax;
		printf("³ëµå °³¼ö ? ");
		scanf("%d", &nMax);
		if (nMax <= 0 || nMax > MAX_ELEMENTS)
			break;
		printf("  [Heap ·£´ý »ðÀÔ]\n");
		for (int i = 1; i <= nMax; i++) {
			item.nData = rand() % 1000;
			printf("    [%02d] %d\n", i, item.nData);
			InsertHeap(heap, item, nCtr);
		}
		printf("\n  [Heap »èÁ¦]\n");
		for (int i = 1; i <= nMax; i++) {
			item = DeleteHeap(heap, nCtr);
			printf("    [%02d] %d\n", i, item.nData);
		}
		putchar('\n');
	}
}

void InsertHeap(Element heap[], Element anItem, int& nCtr)
{
	int nNdx = ++nCtr;
	while (nNdx > 1 && anItem.nData > heap[nNdx / 2].nData) {
		heap[nNdx] = heap[nNdx / 2];
		nNdx /= 2;
	}
	heap[nNdx] = anItem;
}

Element DeleteHeap(Element heap[], int& nCtr)
{
	Element	anItem = heap[1];
	Element	lastItem = heap[nCtr--];
	int parent = 1, child = 2;
	while (child<=nCtr) {
		if (child < nCtr && heap[child].nData < heap[child + 1].nData)
			child++;
		if (lastItem.nData >= heap[child].nData)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = lastItem;
	return anItem;
}
