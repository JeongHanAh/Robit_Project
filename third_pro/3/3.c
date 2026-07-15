#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int a;

	printf("년도를 입력하세요 : ");
	scanf("%d", &a);

	if (a % 4 == 0 && a % 100 != 0 || a % 400 == 0) {
		printf("윤년");
	}
	else printf("윤년이 아님");
}