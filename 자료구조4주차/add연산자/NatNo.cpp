#include <stdio.h>

#pragma warning(disable: 4996)

typedef int NatNo;

NatNo Zero();
int   IsZero(NatNo x);
NatNo Succ(NatNo x);
NatNo Pred(NatNo x);
NatNo Add(NatNo x, NatNo y);

// Practise
int   Equal(NatNo x, NatNo y);
int   Greater(NatNo x, NatNo y);
NatNo Sub(NatNo x, NatNo y);		// Error example

// HW
NatNo Mul(NatNo x, NatNo y);
NatNo Div(NatNo x, NatNo y);		// Error case
NatNo Mod(NatNo x, NatNo y);		// Error case

void main()
{
	while (1) {
		int nFtn;
		NatNo x, y, z;
		printf("Is1, Su2, Ad3, Eq4, Gt5, Sb6, Mu7, Di8, Mo9: ? ");
		scanf("%d", &nFtn);
		if (nFtn < 1 || nFtn > 9)
			break;
		printf("x ? ");
		scanf("%d", &x);
		if (nFtn > 2) {
			printf("y ? ");
			scanf("%d", &y);
		}
		switch (nFtn) {
		case 1:
			z = IsZero(x); break;
		case 2:
			z = Succ(x); break;
		case 3:
			z = Add(x, y); break;
		case 4:
			z = Equal(x, y); break;
		case 5:
			z = Greater(x, y); break;
		case 6:
			z = Sub(x, y); break;
		case 7:
			z = Mul(x, y); break;
		case 8:
			z = Div(x, y); break;
		case 9:
			z = Mod(x, y);
		}
		printf("return %d\n\n", z);
	}
}

NatNo Error()
{
	printf("Error:: not applicable operator!!!\n");
	return Zero();
}

NatNo Zero()
{
	return 0;
}

int IsZero(NatNo x)
{
	if (x == Zero())
		return true;
	return false;
}

NatNo Succ(NatNo x)
{
	return x + 1;		// +�� ��¿ �� ����
}

NatNo Pred(NatNo x)
{
	if (IsZero(x))
		return Error();
	return x - 1;		// -�� ��¿ �� ����
}

/*
	���⼭���� ���ǵ� ������ �� ����� �� ����.
*/

NatNo Add(NatNo x, NatNo y)
{	//x + y
	//x ���� �޼ҵ�
	/*if (IsZero(x))
		return y;
	return Succ(Add(Pred(x), y));*/
	
	//y ���� �޼ҵ�
	if (IsZero(y))
		return x;
	return Succ(Add(x, Pred(y)));

}

int Equal(NatNo x, NatNo y)
{	// x == y
	/*	if (IsZero(x))
		return IsZero(y);
	if (IsZero(y))
		return false;
	return Equal(Pred(x),Pred(y));
	*/
	
	if (IsZero(y))
		return IsZero(x);
	if (IsZero(x))
		return false;
	return Equal(Pred(x), Pred(y));
}

int Greater(NatNo x, NatNo y)
{	// x > y
	/*
	if (IsZero(x))
		return false;
	if (IsZero(y))
		return true;
	return Greater(Pred(x), Pred(y));
	*/

	if (IsZero(y))
		return IsZero(x) ? false : true;
	if (IsZero(x))
		return false;
	return Greater(Pred(x), Pred(y));
}

NatNo Sub(NatNo x, NatNo y)
{	// x - y
	// Sub(x + 1, y + 1) ::= Sub(x, y)			;; �Ϲ� ����

	/*
	if (IsZero(x))
		return IsZero(y) ? Zero() : Error();
	if (IsZero(y))
		return x;
	return Sub(Pred(x), Pred(y));
	*/

	if (IsZero(y))
		return x;
	if (IsZero(x))
		return Error();
	return Sub(Pred(x), Pred(y));

}

NatNo Mul(NatNo x, NatNo y)
{	// x * y

	/*
	if (IsZero(x))
		return Zero();
	return Add(Mul(Pred(x), y), y);
	*/

	if (IsZero(y))
		return Zero();
	return Add(Mul(x, Pred(y)), x);
}

NatNo Div(NatNo x, NatNo y)
{	// x / y
	// Div(x + y, y) ::= Div(x, y) + 1
	if (IsZero(y))
		return Error();
	return Greater(y, x) ? Zero() : Succ(Div(Sub(x, y), y));
}

NatNo Mod(NatNo x, NatNo y)
{	// x % y
	// Mod(x + y, y) ::= Mod(x, y)				;; �Ϲ� ����
	//     x  y
	// (1) ?  ? --> ?						;; �ߴ� ����
	// (2) ~~~~
	// (3) ~~~~
	// [1]:(?,?)	Sub(?, ?) ::= ?
	// [2]:(?,?)	Sub(?, ?) ::= ?
	if (IsZero(y))
		return Error();
	return Greater(y, x) ? x : Mod(Sub(x, y), y);
}

/****

[����]
NatNo Add(NatNo x, NatNo y)
{
	// Add(x + 1, y) = Add(x, y) + 1
	//     x  y
	// (1) 0  y --> y		;; simple solution

	// Rule
	// Z�� Zero�̰�, N�� Nonzero�̰�, A�� All �� Zero/Nonzero���� �ǹ��Ѵ�.
	// [1]:(Z,A)	Add(Zero(), y) ::= y						;; 0 + y ::= y
	// [2]:(N,A)	Add(Succ(x), y) ::= Succ(Add(x, y))

	// Coding
	if (IsZero(x))						// y�� �ƹ��� ���������� ����
		return y;						// [1]
	// ���⼭���� x�� Zero�� �ƴ�
	return Succ(Add(Pred(x), y));		// [2]

}

���� ������ ���캸��
(1) �����ڿ� ���� ��Ģ�� �����
(2) ��� ��Ȳ�� ���Ͽ� ������ ��Ģ�� �׻� �����ϴ� ���� �����ϰ�
(3) ��� ��Ȳ������ �����ϰ� �ϳ��� �ִٴ� ���� �����ϰ�
(4) �� ��Ģ�� ���� �ڵ��� �Ǿ���.

���� ������ �߿��� ��� �ִ� ������ �Լ��� ���Ͽ�
���� (1), (2), (3), (4)�� ������ ���� �ڵ��϶�


NatNo Operator(NatNo x, NatNo y)
{
	//
	// �� �������� ��� ��쿡���� ����ǰ�
	// ���� �ϳ��� ��Ģ�� ����ȴٴ� ���� ���δ�
	//

	.......
	.......		// ���� ��Ģ�� ���� ������ �ڵ��� �Ѵ�.
	.......
}

�� ������ �Ǿ� �ִ� ��� �����ڿ� ���Ͽ�
���� ���� ���� ������� ä�� �ִ´�.

****/