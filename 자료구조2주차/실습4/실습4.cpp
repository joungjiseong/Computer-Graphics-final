// hanoi.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

#pragma warning(disable: 4996)

void main()
{
	while (true) {
		int nCtr;
		printf("Disks ? ");
		scanf("%d", &nCtr);			// �ű�� ž�� ���� �Է� �޴´�.
		if (nCtr <= 0)
			break;
		void hanoi(int nDisk, int nFrom, int nTo);
		hanoi(nCtr, 1, 2);			// ž�� 1���� 2�� �ű�ÿ�.
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
