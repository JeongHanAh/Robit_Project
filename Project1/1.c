#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void rightri(int n) {
	int a = n / 2 + 1; //줄 수의 반을 나눠 * 한 개만 찍는 게 있는 걸 감안해 +1
	for (int i = 0; i <= a; i++) {
		for (int j = 0; j < i; j++) {
			printf("*");
		}
		printf("\n");
	} //대칭
	for (int i = a - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			printf("*");
		}
		printf("\n");
	}
}

void leftri(int n) {
	int a = n / 2 + 1;
	for (int i = 0; i <= a; i++) {
		for (int j = 0; j < a - i; j++) {
			printf(" ");
		}
		for (int j = 0; j < i; j++) {
			printf("*");
		}
		printf("\n");

	}
	for (int i = a - 1; i > 0; i--) {
		for (int j = 0; j < a - i; j++) {
			printf(" ");
		}
		for (int j = 0; j < i; j++) {
			printf("*");
		}
		printf("\n");
	}
}

void hourglass(int n) {
	int a = n / 2 + 1;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < i; j++) {
			printf(" ");
		}
		for (int j = 0; j < (a - i) * 2 - 1; j++) {
			printf("*");
		}
		printf("\n");
	}
	for (int i = 1; i < a; i++) {
		for (int j = 0; j < a - i - 1; j++) {
			printf(" ");
		}
		for (int j = 0; j < (1+i) * 2 - 1; j++) {
			printf("*");
		}
		printf("\n");
	}
}

void tritri(int n) {
	int a = n / 2 + 1;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < i; j++) {
			printf(" ");
		}
		for (int j = 0; j < a - i; j++) {
			printf("*");
		}
		printf("\n");
	}
	for (int i = 1; i < a; i++) {
		for (int j = 0; j < a - 1; j++) {
			printf(" ");
		}
		for (int j = 0; j <= i; j++) {
			printf("*");
		}
		printf("\n");
	}
}


void main() {
	int a, b;
	printf("사이즈와 종류를 입력하시오.");
	scanf("%d %d", &a, &b); //입력을 총 줄 수로 하기 때문에 대칭인 것을 감안할 예정

	switch (b) {
	case 1:
		rightri(a);
		break;
	case 2:
		leftri(a);
		break;
	case 3:
		hourglass(a);
		break;
	case 4:
		tritri(a);
		break;
	}

}