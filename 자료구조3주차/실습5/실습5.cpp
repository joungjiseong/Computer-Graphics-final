#include <stdio.h>

#pragma warning(disable: 4996)
#define N	25

void main()
{
	int arr[N];
	for (int i = 0; i < N; i++)
		arr[i] = i + 101;
	while (1) {
		int n;
		printf("n ? ");
		scanf("%d", &n);
		if (n < 0 || n > N)
			break;
		int PrintArrayFwrd1(int a[], int n);
		int PrintArrayFwrd2(int a[], int n);
		int PrintArrayFwrd3(int a[], int n);
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintArrayFwrd1(arr, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintArrayFwrd2(arr, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintArrayFwrd3(arr, n));
	}
}

// �迭���� n���� ������ ����ϰ� �׵��� ���� ��ȯ�Ѵ�
int PrintArrayFwrd1(int a[], int n)		// n-1���� ��ȯ�� ������ 1
{
	if (n == 0)
		return 0;
	int t = PrintArrayFwrd1(a, n - 1);
	printf("%d ", a[n-1]);
	return a[n - 1] + t;
}

int PrintArrayFwrd2(int a[], int n)		// 1���� ������ n-1���� ��ȯ
{
	if (n == 0)
		return 0;
	printf("%d ", a[0]);
	return a[0] + PrintArrayFwrd2(a + 1, n - 1);
}

int PrintArrayFwrd3(int a[], int n)		// n/2��, 1��, n/2���� ��ȯ
{
	if (n == 0)
		return 0;
	int m = n / 2;
	int t1 = PrintArrayFwrd3(a, m);
	printf("%d ", a[m]);
	return PrintArrayFwrd3(a + m + 1, n - m - 1) + t1 + a[m];
}