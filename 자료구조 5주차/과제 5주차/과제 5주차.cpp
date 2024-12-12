#include <stdio.h>

#define MAX_TERM 100
#pragma warning (disable: 4996)

typedef int Polynomial[2 * (MAX_TERM + 1)];					// Polynomial: 다항식을 정의한다

void main()
{
	Polynomial polyA = { 6, 3, -1, 2, -2, 1, 0, -1, };		// 끝 표시, (계수, 지수)
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
			if (InputPolynomial(polyA, "A") == 0)					// 다항식 A를 입력한다.
				printf("Input Error\n");
			break;
		case 2:
			if (InputPolynomial(polyB, "B") == 0)					// 다항식 B를 입력한다.
				printf("Input Error\n");
			break;
		case 3:
			polyC[1] = -1;
			if (AddPolynomial(polyA, polyB, polyC))					// 더한다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 4:
			polyC[1] = -1;
			if (SubPolynomial(polyA, polyB, polyC))					// 뺀다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 5:
			polyC[1] = -1;
			SimpleMulPolynomial(polyA, polyB[0], polyB[1], polyC);	// 한 항을 곱한다.
			OutputPolynomial(polyC, "C(X) = ");						// C를 출력한다.
			polyC[1] = -1;
			SimpleMulPolynomial(polyB, polyA[0], polyA[1], polyC);	// 한 항을 곱한다.
			OutputPolynomial(polyC, "C(X) = ");						// C를 출력한다.
			break;
		case 6:
			if (MultiplyPolynomial(polyA, polyB, polyC))			// 곱한다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 7:
			OutputPolynomial(polyA, "A(X) = ");						// A를 출력한다.
			OutputPolynomial(polyB, "B(X) = ");						// B를 출력한다.
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
{	// 다항식이 올바른지 체크
	int bRight = true;
	int nExpon, nPrvExpon = aPoly[1] + 1;
	for (int i = 0; i <= 2 * MAX_TERM; i += 2) {
		nExpon = aPoly[i + 1];
		if (nExpon == -1)
			return bRight;
		if (aPoly[i] == 0) {									// 계수가 0인지 체크
			fprintf(stderr, "%d 번째 항의 계수가 0 입니다.\n", i / 2 + 1);
			bRight = false;
		}
		if (nExpon < 0 || nExpon >= nPrvExpon) {				// 지수가 양수이면서 내림차순
			fprintf(stderr, "%d 번째 항의 지수가 잘못 되었습니다.\n", i / 2 + 1);
			bRight = false;
		}
		nPrvExpon = nExpon;
	}
	return false;
}

int InputPolynomial(Polynomial aPoly, const char* szMsg)
{	// 다항식을 입력
	int nCtr;
	fprintf(stderr, "%s 다항식을 입력합니다.\n", szMsg);
	do {
		fprintf(stderr, "항의 갯수는 ? ");
		scanf("%d", &nCtr);
	} while (nCtr < 0);
	if (nCtr > MAX_TERM) {
		fprintf(stderr, "항이 너무 많습니다.\n");
		return false;
	}
	nCtr *= 2;
	int nNdx;
	for (nNdx = 0; nNdx < nCtr; nNdx += 2) {
		fprintf(stderr, "%d 번째 항의 계수는 ? ", nNdx / 2 + 1);
		scanf("%d", &aPoly[nNdx]);
		fprintf(stderr, "%d 번째 항의 지수는 ? ", nNdx / 2 + 1);
		scanf("%d", &aPoly[nNdx + 1]);
	}
	aPoly[nNdx + 1] = -1;	/* 끝을 표시한다 */
	return CheckPolynomial(aPoly);
}

void OutputPolynomial(Polynomial aPoly, const char* szMsg)
{	// 다항식을 출력
	printf(szMsg);
	if (aPoly[1] == -1)
		putchar('0');
	else {
		for (int i = 0; aPoly[i + 1] >= 0; i += 2) {
			int nCoeff = aPoly[i];					// 계수
			int nExpon = aPoly[i + 1];				// 지수
			char cSign = '+';
			if (nCoeff < 0) {						// +/- 준비
				cSign = '-';
				nCoeff = -nCoeff;
			}
			if (i || cSign == '-')					// 첫 항이 양수일 경우만 제외
				if (i == 0 && cSign == '-')			// 첫 항이 음수
					printf("-");
				else
					printf(" %c ", cSign);			// 부호 출력
			if (nCoeff != 1 || nExpon == 0)
				printf("%d", nCoeff);				// 계수 출력
			if (nExpon > 0) {
				putchar('X');
				if (nExpon > 1)
					printf("^%d", nExpon);			// 지수 출력
			}
		}
	}
	putchar('\n');
}