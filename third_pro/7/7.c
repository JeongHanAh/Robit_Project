#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int n, r;
	printf("n: ");
	scanf("%d", &n);
	printf("r: ");
	scanf("%d", &r);

	int fact1 = 1;
	int fact2 = 1; 
	int fact3 = 1; 
	int fact4 = 1;

	for (int i = 1; i <= n; i++) {
		fact1 *= i;
	}
	for (int i = 1; i <= n - r; i++) {
		fact2 *= i;
	}
	for (int i = 1; i <= r; i++) {
		fact3 *= i;
	}
	for (int i = 1; i <= n + r - 1; i++) {
		fact4 *= i;
	}
	int exp = 1;
	for (int i = 0; i < r; i++) {
		exp *= n;
	}
	printf("순열: %d\n", fact1 / fact2);
	printf("중복 순열: %d\n", exp);
	printf("조합: %d\n", fact1 / fact2 / fact3);
	printf("중복 조합: %d\n", fact4 / (fact1 / n) / fact3);

}