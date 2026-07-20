#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int arr[100][100];

void main() {
	int n1, n2;
	printf("어떤 2차원 배열을 채울까요?(입력: 행 열, 최대 100)\n");
	scanf("%d %d", &n1, &n2);
	int n = 1;

	printf("\n배열A\n\n");
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			arr[i][j] = n++;
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}

	printf("\n배열B\n\n");
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n1; j++) {
			printf("%3d", arr[j][i]);
		}
		printf("\n");
	}
}