#include <stdio.h>

#define MAX_TERM 100
#pragma warning (disable: 4996)

typedef int Polynomial[2 * (MAX_TERM + 1)];	// Polynomial: 다항식을 정의한다

void main()
{
	Polynomial polyA = { 6, 3, -1, 2, -2, 1, 0, -1, };				// 끝 표시, (계수, 지수)
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
			//			polyC[1] = -1;
			if (AddPolynomial(polyA, polyB, polyC))					// 더한다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 4:
			polyC[1] = -1;
			if (SubPolynomial(polyA, polyB, polyC))					// 뺀다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 5:
			SimpleMulPolynomial(polyA, polyB[0], polyB[1], polyC);	// 한 항을 곱한다.
			OutputPolynomial(polyC, "C(X) = ");						// C를 출력한다.
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
{	// 저장할 공간이 있는지 조사하여 한 항을 끝에 저장하고 T/F를 반환한다.
	int nNdx;
	for (nNdx = 1; aPoly[nNdx] >= 0; nNdx += 2);					// 끝을 찾고
	if (nNdx >= 2 * MAX_TERM)
		return false;
	aPoly[nNdx - 1] = nCoef;										// 계수
	aPoly[nNdx] = nExpon;											// 지수
	aPoly[nNdx + 2] = -1;											// 끝을 표시
	return true;
}

int AddPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// 두 다항식 A, B를 더하여 다항식 C에 저장하고 T/F를 반환한다.
	/****
	if (A[1] < 0 || B[1] < 0) {
		for (int i = 0; A[i + 1] >= 0; i += 2)
			if (Attach(C, A[0], A[1]) == false)
				return false;
		for (int i = 0; B[i + 1] >= 0; i += 2)
			if (Attach(C, B[i], B[i + 1]) == false)
				return false;
		return true;
	}
	int nNdxA = 0, nNdxB = 0;
	if (A[1] > B[1]) {
		if (Attach(C, A[0], A[1]) == false)
			return false;
		nNdxA = 2;
	}
	else if (A[1] == B[1]) {
		int nCoef = A[0] + B[0];
		if (nCoef)
			if (Attach(C, nCoef, A[1]) == false)
				return false;
		nNdxA = 2;
		nNdxB = 2;
	}
	else {
		if (Attach(C, B[0], B[1]) == false)
			return false;
		nNdxB = 2;
	}
	return AddPolynomial(A + nNdxA, B + nNdxB, C);
	****/
	int nNdxA = 0, nNdxB = 0;
	while (A[nNdxA + 1] >= 0 && B[nNdxB + 1] >= 0) {
		if (A[nNdxA + 1] > B[nNdxB + 1]) {							// A > B
			if (Attach(C, A[nNdxA], A[nNdxA + 1]) == false)
				return false;
			nNdxA += 2;
		}
		else if (A[nNdxA + 1] == B[nNdxB + 1]) {					//A = B
			int nCoef = A[nNdxA] + B[nNdxB];
			if (nCoef)
				if (Attach(C, nCoef, A[nNdxA + 1]) == false)
					return false;
			nNdxA += 2;
			nNdxB += 2;
		}
		else {														//A < B
			if (Attach(C, B[nNdxB], B[nNdxB + 1]) == false)
				return false;
			nNdxB += 2;
		}
	}
	for (; A[nNdxA + 1] >= 0; nNdxA += 2)
		if (Attach(C, A[nNdxA], A[nNdxA + 1]) == false)
			return false;
	for (; B[nNdxB + 1] >= 0; nNdxB += 2)
		if (Attach(C, B[nNdxB], B[nNdxB + 1]) == false)
			return false;
	return true;
}

int SubPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// 다항식 A에서 다항식 B를 빼서 다항식 C에 저장하고 T/F를 반환한다.
	/****/
	if (A[1] < 0 || B[1] < 0) {
		for (int i = 0; A[i + 1] >= 0; i += 2)
			if (Attach(C, A[i], A[i + 1]) == false)
				return false;
		for (int i = 0; B[i + 1] >= 0; i += 2)
			if (Attach(C, -B[i], B[i + 1]) == false)
				return false;
		return true;
	}
	if (A[1] > B[1]) {
		if (Attach(C, A[0], A[1]) == false)
			return false;
		return SubPolynomial(A + 2, B, C);
	}
	if (A[1] == B[1]) {
		int nCoef = A[0] - B[0];
		if (nCoef)
			if (Attach(C, nCoef, A[1]) == false)
				return false;
		return SubPolynomial(A + 2, B + 2, C);
	}
	if (Attach(C, -B[0], B[1]) == false)
		return false;
	return SubPolynomial(A, B + 2, C);
	/****/
	/****
	C[1] = -1;
	int nNdxA = 0, nNdxB = 0;
	while (A[nNdxA + 1] >= 0 && B[nNdxB + 1] >= 0) {
		if (A[nNdxA + 1] > B[nNdxB + 1]) {							// A > B
			if (Attach(C, A[nNdxA], A[nNdxA + 1]) == false)
				return false;
			nNdxA += 2;
		}
		else if (A[nNdxA + 1] == B[nNdxB + 1]) {					//A = B
			int nCoef = A[nNdxA] - B[nNdxB];
			if (nCoef)
				if (Attach(C, nCoef, A[nNdxA + 1]) == false)
					return false;
			nNdxA += 2;
			nNdxB += 2;
		}
		else {														//A < B
			if (Attach(C, -B[nNdxB], B[nNdxB + 1]) == false)
				return false;
			nNdxB += 2;
		}
	}
	for (; A[nNdxA + 1] >= 0; nNdxA += 2)
		if (Attach(C, A[nNdxA], A[nNdxA + 1]) == false)
			return false;
	for (; B[nNdxB + 1] >= 0; nNdxB += 2)
		if (Attach(C, -B[nNdxB], B[nNdxB + 1]) == false)
			return false;
	return true;
	****/
}

void SimpleMulPolynomial(Polynomial A, int nCoef, int nExpon, Polynomial B)
{	// 다항식 A와 한 항을 곱하여 다항식 B에 저장한다.
	/****
	for (int nNdx = 0; A[nNdx + 1] >= 0; nNdx += 2) {
		B[nNdx] = A[nNdx] * nCoef;
		B[nNdx + 1] = A[nNdx + 1] + nExpon;
		//Attach(B, A[nNdx], A[nNdx + 1]);
	}
	/****/
	/****/
	B[1] = -1;
	for (int nNdx = 0; A[nNdx + 1] >= 0; nNdx += 2)
		Attach(B, A[nNdx] * nCoef, A[nNdx + 1] + nExpon);
	/****/
}

int MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	
	if (A[1] < 0) {
		C[1] = -1;
		return true;
	}
	Polynomial C1, C2;
	SimpleMulPolynomial(B, A[0], A[1], C1);				// A1 * B → C1
	MultiplyPolynomial(A + 2, B, C2);					// An * B → C2
	AddPolynomial(C1, C2, C);							// C1 + C2 → C
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
		if (aPoly[i] == 0) {										// 계수가 0인지 체크
			fprintf(stderr, "%d 번째 항의 계수가 0 입니다.\n", i / 2 + 1);
			bRight = false;
		}
		if (nExpon < 0 || nExpon >= nPrvExpon) {					// 지수가 양수이면서 내림차순
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