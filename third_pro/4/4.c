#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	printf("Input Arithmetic Operation");
	printf("\nex) \t 3.4 * 8.5");
	printf("\n \t 2.9 - 5.4");
	printf("\n \t 3.9 * 8.0");
	printf("\n \t 3.9 ^ 8");

	printf("\n\ninput : ");
	float a, b;
	char cs;
	scanf("%f %c %f", &a, &cs, &b);
	if (cs == '+') {
		printf("%.2f + %.2f = %.2f", a, b, a + b);
	}
	else if (cs == '-') {
		printf("%.2f - %.2f = %.2f", a, b, a - b);
	}
	else if (cs == '*') {
		printf("%.2f * %.2f = %.2f", a, b, a * b);
	}
	else if (cs == '/') {
		if (b == 0) {
			printf("0으로 나눌 수 없습니다.");
		}
		else printf("%.2f / %.2f = %.2f", a, b, a / b);
	}
	else if (cs == '^') {
		float exp = 1;
		for (int i = 0; i < b; i++) {
			exp *= a;
		}
		printf("%.2f ^ %.2f = %.2f", a, b, exp);
	}
}