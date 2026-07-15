#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int a;
	printf("값을 입력하세요. ");
	scanf("%d", &a);

	if (a == 1) {
		printf("*");
	}
	else {
		for (int i = 1; i <= a; i++) {
			if (i == 1) {
				for (int j = 0; j < a - 1; j++) {
					printf(" ");
				}
				printf("*");
			}
			else if (i == a) {
				for (int j = 0; j < i*2 - 1; j++) {
					printf("*");
				}
			}
			else {
				for (int j = 0; j < a - i; j++) {
					printf(" ");
				}
				printf("*");
				for (int j = 0; j < (i - 1) * 2 - 1; j++) {
					printf(" ");
				}
				printf("*");
			}
			printf("\n");
		}
	}
}