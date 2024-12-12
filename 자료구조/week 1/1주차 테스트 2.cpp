#include <stdio.h>

#define N	26

void main()
{
	for(int i = 0; i < N; i++){
		for (int j = 0; j < N; j++) {
			putchar('A' + ((j + i) % N));
		}
		putchar('\n');
	}
}