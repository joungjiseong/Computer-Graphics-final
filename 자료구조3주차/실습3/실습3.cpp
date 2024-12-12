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
		int PrintK2NFwrd1(int k, int n);
		int PrintK2NFwrd2(int k, int n);
		int PrintK2NFwrd3(int k, int n);
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintK2NFwrd1(k, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintK2NFwrd2(k, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintK2NFwrd3(k, n));
	}
}

// k���� n���� ����ϰ� �׵��� ���� ��ȯ�Ѵ�
int PrintK2NFwrd1(int k, int n)		// n-1���� ��ȯ�� ������ 1
{
	if (k > n)
		return 0;
	int t = PrintK2NFwrd1(k, n - 1);
	printf("%d ", n);
	return n + t;
}

int PrintK2NFwrd2(int k, int n)		// 1���� ������ n-1���� ��ȯ
{
	if (k > n)
		return 0;
	printf("%d ", k);
	return k + PrintK2NFwrd2(k + 1, n);
}

int PrintK2NFwrd3(int k, int n)		//  n/2��, 1��, n/2���� ��ȯ
{
	if (k > n)
		return 0;
	int m = (k + n) / 2;
	int t = PrintK2NFwrd3(k, m - 1);
	printf("%d ", m);
	return PrintK2NFwrd3(m + 1, n) + t + m;
}