#include <stdio.h>

#pragma warning(disable: 4996)

void main()
{
	while (1) {
		int n, r;
		printf("n ? ");
		scanf("%d", &n);
		if (n <= 0)
			break;
		printf("r ? ");
		scanf("%d", &r);
		if (n < r || r < 0)
			break;
		int Combi(int, int);
		printf("Combi(%d, %d) = %d\n\n", n, r, Combi(n, r));
	}
}

int Combi(int n, int r)
{
	if (n == r || r==0)
		return 1;
	return Combi(n - 1, r) + Combi(n - 1, r - 1);
}

