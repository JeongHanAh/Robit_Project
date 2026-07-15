#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int ans = 0;
	int fibo = 0;

	printf("몇 번째 피보나치 수를 출력할까요?\n");
	scanf("%d", &ans);
	if (ans == 1) {
		fibo = 0;
	}
	else if (ans == 2) {
		fibo == 1;
	}
	else if (ans > 2) {
		int a = 0;
		int b = 1;
		for (int i = 3; i <= ans; i++) {
			fibo = a + b;
			a = b;
			b = fibo;
		}
	}

	printf("%d 번째 피보나치 수는 %d 입니다.", ans, fibo);
}