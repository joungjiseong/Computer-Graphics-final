#include <stdio.h>

#define	N1	9
#define	N2	8
#define	N3	7
#define	N4	8
#define DIM	4
#pragma warning( disable: 4996 )

void main()
{
	int B[N1][N2][N3][N4];
	int nArrDesc[2 * DIM + 1] = { DIM, 0, 0, 0, 0, N1, N2, N3, N4 };
	int nDim = DIM;
	int* nNdx = nArrDesc + 1;
	int* nBound = nArrDesc + 1 + DIM;
	for (int i = 0; i < nBound[0]; i++)
		for (int j = 0; j < nBound[1]; j++)
			for (int k = 0; k < nBound[2]; k++)
				for (int l = 0; l < nBound[3]; l++)
					B[i][j][k][l] = i * 1000 + j * 100 + k * 10 + l;
	int IsOK = true;
	while (IsOK) {
		int nValue;
		printf("index> ");
		for (int i = 0; i < DIM && IsOK; i++) {
			scanf("%d", nNdx + i);
			if (i == 0 && nNdx[i] < 0)
				IsOK = false;
		}
		if (IsOK) {
			int Aij(int A[], int nArrDesc[], int& nValue);
			if (Aij((int*)B, nArrDesc, nValue))
				printf("A[%d][%d][%d][%d] = %d(%d)\n",
					nNdx[0], nNdx[1], nNdx[2], nNdx[3], B[nNdx[0]][nNdx[1]][nNdx[2]][nNdx[3]], nValue);
			else
				printf("���� ����, ....\n");
			putchar('\n');
		}
	}
	printf("Bye, ....\n\n");
}

int Aij(int A[], int nArrDesc[], int& nValue)
{	// ������ �����̸� nValue�� ���ο� ���� �迭�� ���� �����ϰ� T/F�� ��ȯ�Ѵ�.
	// �˴ٽ��� ������ ���� ���� �޶����� ������, ��� for loop�� ����Ͽ� ���� ����϶�.
	// �Ʒ��� ���� ������ ������ �Ųٷ� ����� �Ѵ�.
	// nNdx[3] * nSize +		;; nSize = 1;
	// nNdx[2] * nSize +		;; nSize = nBound[3]
	// nNdx[1] * nSize +		;; nSize = nBound[2] * nBound[3]
	// nNdx[0] * nSize			;; nSize = nBound[1] * nBound[2] * nBound[3]
	int n = 0, nSize = 1;
	int nDim = nArrDesc[0], * arNdx = nArrDesc + 1, * arBound = nArrDesc + 1 + nDim;
	for (int i = nDim - 1; i >= 0; i--) {
		if (arNdx[i] < 0 || arNdx[i] >= arBound[i])
			return false;
		n += arNdx[i] * nSize;
		nSize *= arBound[i];
	}
	nValue = A[n];
	return true;
}
