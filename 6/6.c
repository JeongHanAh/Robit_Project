#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void main() {
	int n1, n2;
	printf("N1 N2는?(홀수로 입력) : ");
	scanf("%d %d", &n1, &n2);

	int** arr = (int**)malloc(sizeof(int*) * n1);
	for (int i = 0; i < n1; i++) {
		arr[i] = (int*)calloc(n2, sizeof(int));
	}

	int num = 1;
	int center_h = n1 / 2; //중앙 행
	int center_y = n2 / 2; //중앙 열

	arr[center_h][center_y] = num++;

	int scale = 1; //마름모 크기

	while (num <= n1 * n2) { //과제 3랑 비슷한 방식
		int h = center_h + 1;
		int y = center_y - (scale - 1);

		if (h >= 0 && h < n1 && y >= 0 && y < n2) {
			arr[h][y] = num++;
		} //시작점이 배열 안쪽이면 숫자 채움

		//4방향 대각선 이동

		for (int i = 0; i < scale - 1; i++) {
			h++; y++;
			if (h >= 0 && h < n1 && y >= 0 && y < n2) {
				arr[h][y] = num++;
			}
		}
		for (int i = 0; i < scale; i++) {
			h--; y++;
			if (h >= 0 && h < n1 && y >= 0 && y < n2) {
				arr[h][y] = num++;
			}
		}
		for (int i = 0; i < scale; i++) {
			h--; y--;
			if (h >= 0 && h < n1 && y >= 0 && y < n2) {
				arr[h][y] = num++;
			}
		}
		for (int i = 0; i < scale; i++) {
			h++; y--;
			if (h >= 0 && h < n1 && y >= 0 && y < n2) {
				arr[h][y] = num++;
			}
		}

		scale++;
	}

	printf("\n출력 :\n");
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			printf("%4d", arr[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < n1; i++) {
		free(arr[i]);
	}
	free(arr);
}