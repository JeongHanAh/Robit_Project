#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print(int* row, int* col, int** pArr) {
	for (int i = 0; i < *row; i++) {
		for (int j = 0; j < *col; j++) {
			printf("%4d", pArr[i][j]);
		}
		printf("\n");
	}
} //출력 함수

void arr_ij(int* sizeRow, int* sizeCol, int** pArr) {
	//경계 설정, 경로를 지나가고 나서 경계가 한 칸씩 줄어든다.
	int top = 0;
	int bottom = *sizeRow - 1;
	int left = 0;
	int right = *sizeCol - 1;

	int num = 1;

	//경계면이 서로 부딪히면 끝남
	while (top <= bottom && left <= right) {
		for (int i = left; i <= right; i++) { // 왼 -> 오
			pArr[top][i] = num++;
		}
		top++;
		for (int i = top; i <= bottom; i++) { // 상 -> 하
			pArr[i][right] = num++;
		}
		right--;

		//루프가 다 돌지 않았기 때문에 이미 부딪힌 상태에서 더 진행하지 않으려면 조건을 단다.
		if (top <= bottom) { //부딪히지 않았다면
			for (int i = right; i >= left; i--) { // 오 -> 왼
				pArr[bottom][i] = num++;
			}
			bottom--;
		}
		
		if (left <= right) { //부딪히지 않았다면
			for (int i = bottom; i >= top; i--) { //왼 -> 오
				pArr[i][left] = num++;
			}
			left++; 
		}

	}
}

int main() {
	int** arr = NULL;
	int row, col, sizeRow, sizeCol;

	printf("열의 수를 입력하세요:");
	scanf("%d", &sizeCol);
	printf("행의 수를 입력하세요:");
	scanf("%d", &sizeRow);

	row = sizeRow;
	col = sizeCol;

	arr = (int**)malloc(sizeof(int*) * sizeRow);
	for (int i = 0; i < sizeRow; i++) {
		arr[i] = (int*)malloc(sizeof(int) * sizeCol);
	}

	arr_ij(&sizeRow, &sizeCol, arr);
	print(&row, &col, arr);

	for (int i = 0; i < row; i++) {
		free(arr[i]);
	}
	free(arr);

	return 0;
}