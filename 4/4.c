#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void main() {
	int a;
	printf("몇 개의 원소를 할당하겠습니까? : ");
	scanf("%d", &a);
	int* arr = (int*)malloc(sizeof(int) * a); //입력 받은 수만큼만 메모리 할당

	for (int i = 0; i < a; i++) {
		printf("정수형 데이터 입력:");
		scanf("%d", &arr[i]);
	}
	int max = arr[0];
	int min = arr[0];
	int hap = 0;
	
	for (int i = 0; i < a; i++) {
		if (arr[i] > max) { // 가장 큰 값 기억
			max = arr[i];
		}
		if (arr[i] < min) { //가장 작은 값 기억
			min = arr[i];
		}
		hap += arr[i];
	}
	float avg = (float)hap / a; //전체합 재활용
	printf("최대값: %d\n", max);
	printf("최소값: %d\n", min);
	printf("전체합: %d\n", hap);
	printf("평 균: %f\n", avg);

	free(arr);
}