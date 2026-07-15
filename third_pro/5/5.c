#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int a;
	printf("값을 입력하세요.");
	scanf("%d", &a);

	for (int i = 0; i <= a; i++) {
		for (int j = 0; j < i; j++) printf("*");
		for (int j = (a - 1) * 2; j >= (i * 2) - 1; j--) printf(" ");
		for (int j = 0; j < i; j++) printf("*");
		printf("\n");
	}
	for (int i = a - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) printf("*");
		for (int j = (a - 1) * 2; j >= (i * 2) - 1; j--) printf(" ");
		for (int j = 0; j < i; j++) printf("*");
		printf("\n");
	}
}