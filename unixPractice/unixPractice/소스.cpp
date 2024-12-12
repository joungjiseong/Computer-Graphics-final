#include <stdio.h>

struct st {
	int a;
	char b;
};

void swap(int a[2]) {
	int num = a[0];
	a[0] = a[1];
	a[1] = num;
}

int main() {
	int a[2] = { 3, 20 };
	swap(a);
	printf("a = { %d %d } \n", a[0], a[1]);

	st x = { 1, 'c' };
	st* p;
	p = &x;
	printf("%d %c", x.a, x.b);
	printf("%d %c", p->a, p->b);

	return 0;

	char* ptr[3];
	*ptr[3] = { "red", "blue", "green" };
	char** p = ptr;

	printf(**p);
}