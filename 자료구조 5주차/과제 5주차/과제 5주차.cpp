#include <stdio.h>

#define MAX_TERM 100
#pragma warning (disable: 4996)

typedef int Polynomial[2 * (MAX_TERM + 1)];					// Polynomial: ���׽��� �����Ѵ�

void main()
{
	Polynomial polyA = { 6, 3, -1, 2, -2, 1, 0, -1, };		// �� ǥ��, (���, ����)
	Polynomial polyB = { 5, 4, -1, 2, 2, 1, 8, 0, 0, -1, };
	Polynomial polyC;
	int InputPolynomial(Polynomial A, const char* szMsg);
	void OutputPolynomial(Polynomial A, const char* szMsg);
	int CheckPolynomial(Polynomial A);
	int Attach(Polynomial aPoly, int nCoef, int nExpon);
	int AddPolynomial(Polynomial A, Polynomial B, Polynomial C);
	int SubPolynomial(Polynomial A, Polynomial B, Polynomial C);
	void SimpleMulPolynomial(Polynomial A, int nCoef, int nExpon, Polynomial B);
	int MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C);
	CheckPolynomial(polyA);
	CheckPolynomial(polyB);
	int bContinue = true;
	while (bContinue) {
		int nFtn;
		printf("1: A, 2: B, 3: Add, 4: Sub, 5: Simple, 6: Mul, 7: pr ? ");
		scanf("%d", &nFtn);
		switch (nFtn) {
		case 1:
			if (InputPolynomial(polyA, "A") == 0)					// ���׽� A�� �Է��Ѵ�.
				printf("Input Error\n");
			break;
		case 2:
			if (InputPolynomial(polyB, "B") == 0)					// ���׽� B�� �Է��Ѵ�.
				printf("Input Error\n");
			break;
		case 3:
			polyC[1] = -1;
			if (AddPolynomial(polyA, polyB, polyC))					// ���Ѵ�.
				OutputPolynomial(polyC, "C(X) = ");					// C�� ����Ѵ�.
			break;
		case 4:
			polyC[1] = -1;
			if (SubPolynomial(polyA, polyB, polyC))					// ����.
				OutputPolynomial(polyC, "C(X) = ");					// C�� ����Ѵ�.
			break;
		case 5:
			polyC[1] = -1;
			SimpleMulPolynomial(polyA, polyB[0], polyB[1], polyC);	// �� ���� ���Ѵ�.
			OutputPolynomial(polyC, "C(X) = ");						// C�� ����Ѵ�.
			polyC[1] = -1;
			SimpleMulPolynomial(polyB, polyA[0], polyA[1], polyC);	// �� ���� ���Ѵ�.
			OutputPolynomial(polyC, "C(X) = ");						// C�� ����Ѵ�.
			break;
		case 6:
			if (MultiplyPolynomial(polyA, polyB, polyC))			// ���Ѵ�.
				OutputPolynomial(polyC, "C(X) = ");					// C�� ����Ѵ�.
			break;
		case 7:
			OutputPolynomial(polyA, "A(X) = ");						// A�� ����Ѵ�.
			OutputPolynomial(polyB, "B(X) = ");						// B�� ����Ѵ�.
			break;
		default:
			bContinue = false;
		}
		putchar('\n');
	}
	printf("Bye, ....\n\n");
}

int Attach(Polynomial aPoly, int nCoef, int nExpon)
{	
	if (aPoly[1] < 0)
		return (aPoly[0] = nCoef, aPoly[1] = nExpon, aPoly[3] = -1);
	return Attach(aPoly + 2, nCoef, nExpon);
}

int AddPolynomial(Polynomial A, Polynomial B, Polynomial C)
{
	if (A[1] < 0 && B[1] < 0)
		return true;
	if (A[1] > B[1]) {
		Attach(C, A[0], A[1]);
		AddPolynomial(A + 2, B, C);
	}
	else if (A[1] == B[1]) {
		if(A[0] + B[0])
			Attach(C, A[0] + B[0], A[1]);
		AddPolynomial(A + 2, B + 2, C);
	}
	else {
		Attach(C, B[0], B[1]);
		AddPolynomial(A, B + 2, C);
	}
	return true;
}

int SubPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	
	if (A[1] < 0 && B[1] < 0)
		return true;
	if (A[1] > B[1]) {
		Attach(C, A[0], A[1]);
		SubPolynomial(A + 2, B, C);
	}
	else if (A[1] == B[1]) {
		if (A[0] - B[0])
			Attach(C, A[0] - B[0], A[1]);
		SubPolynomial(A + 2, B + 2, C);
	}
	else {
		Attach(C, -B[0], B[1]);
		SubPolynomial(A, B + 2, C);
	}
	return true;
}

int CopyRemainder(Polynomial A, Polynomial R, int nSign)	// nSign = 1 or -1
{	
	if (R[1] < 0)
		return true;
	return Attach(A, R[0] * nSign, R[1]) && CopyRemainder(A, R + 2, nSign);
}

void SimpleMulPolynomial(Polynomial A, int nCoef, int nExpon, Polynomial B)
{	
	if (A[1] < 0)
		return;
	B[0] = A[0] * nCoef, B[1] = A[1] + nExpon;
	return SimpleMulPolynomial(A + 2, nCoef, nExpon, B + 2);
}

int MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C)
{
	if (A[1] < 0)
		return true;
	Polynomial C1, C2;
	SimpleMulPolynomial(B, A[0], A[1], C1);
	MultiplyPolynomial(A + 2, B, C2);
	AddPolynomial(C1, C2, C);
	return true;
}

int CheckPolynomial(Polynomial aPoly)
{	// ���׽��� �ùٸ��� üũ
	int bRight = true;
	int nExpon, nPrvExpon = aPoly[1] + 1;
	for (int i = 0; i <= 2 * MAX_TERM; i += 2) {
		nExpon = aPoly[i + 1];
		if (nExpon == -1)
			return bRight;
		if (aPoly[i] == 0) {									// ����� 0���� üũ
			fprintf(stderr, "%d ��° ���� ����� 0 �Դϴ�.\n", i / 2 + 1);
			bRight = false;
		}
		if (nExpon < 0 || nExpon >= nPrvExpon) {				// ������ ����̸鼭 ��������
			fprintf(stderr, "%d ��° ���� ������ �߸� �Ǿ����ϴ�.\n", i / 2 + 1);
			bRight = false;
		}
		nPrvExpon = nExpon;
	}
	return false;
}

int InputPolynomial(Polynomial aPoly, const char* szMsg)
{	// ���׽��� �Է�
	int nCtr;
	fprintf(stderr, "%s ���׽��� �Է��մϴ�.\n", szMsg);
	do {
		fprintf(stderr, "���� ������ ? ");
		scanf("%d", &nCtr);
	} while (nCtr < 0);
	if (nCtr > MAX_TERM) {
		fprintf(stderr, "���� �ʹ� �����ϴ�.\n");
		return false;
	}
	nCtr *= 2;
	int nNdx;
	for (nNdx = 0; nNdx < nCtr; nNdx += 2) {
		fprintf(stderr, "%d ��° ���� ����� ? ", nNdx / 2 + 1);
		scanf("%d", &aPoly[nNdx]);
		fprintf(stderr, "%d ��° ���� ������ ? ", nNdx / 2 + 1);
		scanf("%d", &aPoly[nNdx + 1]);
	}
	aPoly[nNdx + 1] = -1;	/* ���� ǥ���Ѵ� */
	return CheckPolynomial(aPoly);
}

void OutputPolynomial(Polynomial aPoly, const char* szMsg)
{	// ���׽��� ���
	printf(szMsg);
	if (aPoly[1] == -1)
		putchar('0');
	else {
		for (int i = 0; aPoly[i + 1] >= 0; i += 2) {
			int nCoeff = aPoly[i];					// ���
			int nExpon = aPoly[i + 1];				// ����
			char cSign = '+';
			if (nCoeff < 0) {						// +/- �غ�
				cSign = '-';
				nCoeff = -nCoeff;
			}
			if (i || cSign == '-')					// ù ���� ����� ��츸 ����
				if (i == 0 && cSign == '-')			// ù ���� ����
					printf("-");
				else
					printf(" %c ", cSign);			// ��ȣ ���
			if (nCoeff != 1 || nExpon == 0)
				printf("%d", nCoeff);				// ��� ���
			if (nExpon > 0) {
				putchar('X');
				if (nExpon > 1)
					printf("^%d", nExpon);			// ���� ���
			}
		}
	}
	putchar('\n');
}