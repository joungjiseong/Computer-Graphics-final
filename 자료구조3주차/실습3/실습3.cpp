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

// k부터 n까지 출력하고 그들의 합을 반환한다
int PrintK2NFwrd1(int k, int n)		// n-1개의 순환과 나머지 1
{
	if (k > n)
		return 0;
	int t = PrintK2NFwrd1(k, n - 1);
	printf("%d ", n);
	return n + t;
}

int PrintK2NFwrd2(int k, int n)		// 1개와 나머지 n-1개의 순환
{
	if (k > n)
		return 0;
	printf("%d ", k);
	return k + PrintK2NFwrd2(k + 1, n);
}

int PrintK2NFwrd3(int k, int n)		//  n/2개, 1개, n/2개의 순환
{
	if (k > n)
		return 0;
	int m = (k + n) / 2;
	int t = PrintK2NFwrd3(k, m - 1);
	printf("%d ", m);
	return PrintK2NFwrd3(m + 1, n) + t + m;
}