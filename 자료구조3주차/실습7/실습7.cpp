#define MaxLen 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)

void main()
{
	while (1) {
		char str[MaxLen];
		printf("�ܾ� ���ڿ�: ");
		gets_s(str);
		if (*str == NULL)
			break;
		int nNdx = 0;
		int nNdxMax = strlen(str) - 1;		// ������ 0���� length - 1����
		while (1) {
			printf("%s�� ��ȭ��ų ����[0~%d] ? ", str, nNdxMax);
			char strNdx[MaxLen];
			gets_s(strNdx);
			nNdx = atoi(strNdx);			// sscanf(strNdx, "%d", &nNdx);
			if (nNdx < 0 || nNdx > nNdxMax)
				break;
			void Perm(char* str, int k, int n);
			Perm(str, nNdx, nNdxMax);
			putchar(10);
		}
		putchar(10);
	}
	printf("Bye, ...\n");
}

void swap(char& x, char& y)
{
	char t = x;
	x = y;
	y = t;
}

void Perm(char* str, int k, int n)
{
	if (k == n)
		printf("%s\n", str);
	else {
		for (int i = k; i <= n; i++) {
			int temp;
			swap(str[k], str[i]);
			Perm(str, k + 1, n);
			swap(str[k], str[i]);
		}
	}
}
