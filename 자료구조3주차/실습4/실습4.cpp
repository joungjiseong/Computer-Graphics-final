#include <stdio.h>

#pragma warning(disable: 4996)

void main()
{
	while (1) {
		int k, n;
		printf("k ? ");
		scanf("%d", &k);
		if (k < 0)
			break;
		printf("n ? ");
		scanf("%d", &n);
		if (k > n)
			break;
		int PrintK2NBwrd1(int k, int n);
		int PrintK2NBwrd2(int k, int n);
		int PrintK2NBwrd3(int k, int n);
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintK2NBwrd1(k, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintK2NBwrd2(k, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintK2NBwrd3(k, n));
	}
}

// k���� n���� �Ųٷ� ����ϰ� �׵��� ���� ��ȯ�Ѵ�
int PrintK2NBwrd1(int k, int n)		// n-1���� ��ȯ�� ������ 1
{
	if (k > n)
		return 0;
	printf("%d ", n);
	return n + PrintK2NBwrd1(k, n - 1);
}

int PrintK2NBwrd2(int k, int n)		// 1���� ������ n-1���� ��ȯ
{
	if (k > n)
		return 0;
	int t = PrintK2NBwrd2(k + 1, n);
	printf("%d ", k);
	return k + t;
}

int PrintK2NBwrd3(int k, int n)		// n/2��, 1��, n/2���� ��ȯ
{
	if (k > n)
		return 0;
	int m = (k + n) / 2;
	int t = PrintK2NBwrd3(m + 1, n);
	printf("%d ", m);
	return PrintK2NBwrd3(k, m - 1) + t + m;
}