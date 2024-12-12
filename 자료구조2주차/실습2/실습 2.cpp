#include <stdio.h>

#pragma warning(disable: 4996)

void main()
{
	while (1) {
		int n;
		printf("n ? ");
		scanf("%d", &n);
		if (n < 0)
			break;
		int Fib(int);
		printf("Fib[%d] = %d\n\n", n, Fib(n));
	}

}

/*** iterative algorithm
int Fib(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	int nFib0 = 0, nFib1 = 1, nFib;
	for (int i = 2; i <= n; i++) {
		nFib = nFib0 + nFib1;
		nFib0 = nFib1;
		nFib1 = nFib;
	}
	return nFib;
}
****/

/*** recursive algorithm ***/
int Fib(int n)
{
	if (n <= 1)
		return n;
	return Fib(n - 1) + Fib(n - 2);
}
