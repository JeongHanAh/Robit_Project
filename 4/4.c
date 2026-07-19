#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int n, b;
	int arr[1000];

	printf("N : ");
	scanf("%d", &n);

	printf("B : ");
	scanf("%d", &b);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	// 중앙값 인덱스 찾기
	int pos = -1;
	for (int i = 0; i < n; i++) {
		if (arr[i] == b) {
			pos = i;
			break;
		}
	}

	int a = 0;

	// 중앙값이 무조건 포함되어야 하므로 i는 B보다 같거나 작음
	for (int i = 0; i <= pos; i++) {
		int sum = 0;
		
		for (int j = i; j < n; j++) {
			if (arr[j] > b) {
				sum++;
			}
			else if (arr[j] < b) {
				sum--;
			}

			if (j >= pos && sum == 0) {
				a++;
			}
		}
	}

	printf("\n중앙값이 %d인 부분수열의 개수 : %d\n", b, a);
}