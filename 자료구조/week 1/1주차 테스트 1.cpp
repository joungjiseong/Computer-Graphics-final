#include <stdio.h>

#pragma warning( disable : 4996 )

void main()
{
	void MultiTbl();
	MultiTbl();
	// �Ʒ��� �Լ����� ����Ͽ� �������� ����϶�
}

void MultiTbl()
{
	void MultiTblDan(int nDan);
	for (int i = 2; i < 10; i++)
		MultiTblDan(i);
	// 2�ܺ��� 9�ܱ��� �������� ����Ѵ�.
}

void MultiTblDan(int nDan)
{
	void MultiTblRow(int nDan, int nRow);
	for (int i = 1; i < 10; i++)
		MultiTblRow(nDan, i);
	putchar('\n');
	// �������� �� ��(nDan)�� ����Ѵ�
}

void MultiTblRow(int nDan, int nRow)
{
	printf("%d X %d = %2d\n", nDan, nRow, nDan * nRow);
	// �������� �� ��(nDan�� nRow��)�� ����Ѵ�.
}