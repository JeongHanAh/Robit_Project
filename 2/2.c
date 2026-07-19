#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int arr[8];

	printf("입력\n\n");
	for (int i = 0; i < 8; i++) {
		printf("%d: ", i);
		scanf("%d", &arr[i]);
	}
	printf("\n\n");

	for (int i = 0; i < 8; i++) {
		printf("%3d", arr[i]);
	}
	printf("\n\n");

	for (int i = 8 - 1; i > 0; i--) {
		int a = 0;

		//0번 부터 i까지 가장 큰 값인 인덱스 찾기
		//알기 쉽게 생각하면 인덱스 두 칸짜리 네모를 끝까지 계속 슬라이드하는 느낌
		//가장 큰 값이 네모 오른쪽으로 이동
		for (int j = 1; j <= i; j++) {
			if (arr[j] > arr[a]) {
				a = j;
			}
		}

		if (a != i) {
			int temp = arr[i];
			arr[i] = arr[a];
			arr[a] = temp;

			//값 교환되면 출력
			for (int j = 0; j < 8; j++) {
				printf("%3d", arr[j]);
			}
			printf("\n\n");
		}
	}
	
	printf("출력\n\n");
	for (int i = 0; i < 8; i++) {
		printf("%d : %4d\n", i, arr[i]); // 간격을 맞추기 위해 %4d 사용
	}
}