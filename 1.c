#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void main() {
	int arr[5][5] = { 0 };
	int n = 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < (3 - i) * 2 - 1; j++) {
			arr[i][i + j] = n++;
		}
	}

	for (int i = 3; i < 5; i++) {
		for (int j = 0; j < (i - 2)*2+1; j++) {
			arr[i][4 - i + j] = n++;
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}

}