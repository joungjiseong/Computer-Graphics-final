// hanoi.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

#pragma warning(disable: 4996)

void main()
{
	while (true) {
		int nCtr;
		printf("Disks ? ");
		scanf("%d", &nCtr);			// 옮기는 탑의 층을 입력 받는다.
		if (nCtr <= 0)
			break;
		void hanoi(int nDisk, int nFrom, int nTo);
		hanoi(nCtr, 1, 2);			// 탑을 1에서 2로 옮기시요.
		putchar('\n');
	}
}

void hanoi(int nDisk, int nFrom, int nTo)
{
	int n = 6 - nFrom - nTo;
	if (nDisk == 1) {
		printf("%d --> %d\n", nFrom, nTo);
		return;
	}
	hanoi(nDisk - 1, nFrom, n);
	hanoi(1, nFrom, nTo);
	hanoi(nDisk - 1, n, nTo);
}
