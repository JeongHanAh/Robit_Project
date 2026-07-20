#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void main() {
	int n1, n2;
	int num = 1;

	printf("행 열 입력: ");
	scanf("%d %d", &n1, &n2);

	int right, top, bottom, left;

	int** arr = (int**)malloc(sizeof(int*) * n1);
	for (int i = 0; i < n1; i++) {
		arr[i] = (int*)malloc(sizeof(int) * n2);
	}

	right = n2 - 1;
	top = 0;
	left = 0;
	bottom = n1 - 1;

	while (num <= n1 * n2) {
		for (int i = left; i <= right && num <= n1 * n2; i++) {
			arr[top][i] = num++;
		}
		top++;
		for (int i = top; i <= bottom && num <= n1 * n2; i++) {
			arr[i][right] = num++;
		}
		right--;
		for (int i = right; i >= left && num <= n1 * n2; i--) {
			arr[bottom][i] = num++;
		}
		bottom--;
		for (int i = bottom; i >= top && num <= n1 * n2; i--) {
			arr[i][left] = num++;
		}
		left++;
	}

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < n1; i++) {
		free(arr[i]);
	}
	free(arr);
}