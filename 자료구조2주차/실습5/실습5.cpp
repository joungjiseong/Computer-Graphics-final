#include <stdio.h>

#pragma warning(disable: 4996)

void main()
{
	int nNmbr1, nNmbr2;
	while (1) {
		printf("Number 1 ? ");
		scanf("%d", &nNmbr1);		// 수 하나 입력
		if (nNmbr1 <= 0)			// 음수이면 끝낸다
			break;
		printf("Number 2 ? ");
		scanf("%d", &nNmbr2);		// 다른 수 하나 더 입력
		int Euclid(int nBig, int nSmall);
		printf("GCD: %d\n\n", Euclid(nNmbr1, nNmbr2));	// 최대공약수 출력
	}
}

int Euclid(int nBig, int nSmall)
{
	if (nBig % nSmall == 0)
		return nSmall;
	return Euclid(nSmall, nBig % nSmall);
}
