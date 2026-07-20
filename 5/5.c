#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void main() {
	int n;
	printf("N은? ");
	scanf("%d", &n);
	int** arr = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(sizeof(int) * n); //2차원 동적할당
	}
	
	int num = 1;

	//규칙은 00, 01, 10, 20, 11, 02 ... [i][i - j] 형태이므로 이를 바탕으로 로직을 짬.

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			arr[j][i - j] = num++; //상반 삼각형 완성
		}
	}

	for (int i = n; i < 2 * n - 1; i++) {
		for (int j = i - n + 1; j < n; j++) { 
			arr[j][i - j] = num++; //하반 삼각형 완성
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}
}