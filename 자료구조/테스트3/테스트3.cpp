#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#pragma warning( disable : 4996 )

void main()
{
	char Encrypt(char chr, int nKey);
	char sMsg[80];
	int nKey = 3, nMore = true;
	while (nMore) {
		printf("? ");
		gets_s(sMsg);
		switch (sMsg[0]) {
		case 0:
			nMore = false;
			break;
		case '@':
			printf("  kay ? ");
			gets_s(sMsg);
			nKey = atoi(sMsg);
			break;
		default:
			printf("  ");
			for (int i = 0; sMsg[i]; i++)
				putchar(Encrypt(sMsg[i], nKey));
			putchar('\n');
		}
		printf("\n");
	}
	printf("Bye, ....\n");
}

char Encrypt(char chr, int nKey)
{
	if (isalpha(chr)) {
		char cBgn = isupper(chr) ? 'A' : 'a';
		chr = cBgn + (chr - cBgn + nKey + 26) % 26;
	}
	return chr;
}
