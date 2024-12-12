#include <stdio.h>

#pragma warning( disable : 4996 )

void main()
{
	void MultiTbl();
	MultiTbl();
	// 아래의 함수들을 사용하여 구구단을 출력하라
}

void MultiTbl()
{
	void MultiTblDan(int nDan);
	for (int i = 2; i < 10; i++)
		MultiTblDan(i);
	// 2단부터 9단까지 구구단을 출력한다.
}

void MultiTblDan(int nDan)
{
	void MultiTblRow(int nDan, int nRow);
	for (int i = 1; i < 10; i++)
		MultiTblRow(nDan, i);
	putchar('\n');
	// 구구단의 한 단(nDan)을 출력한다
}

void MultiTblRow(int nDan, int nRow)
{
	printf("%d X %d = %2d\n", nDan, nRow, nDan * nRow);
	// 구구단의 한 행(nDan의 nRow행)을 출력한다.
}