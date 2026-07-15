#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	float array[5] = { 0 };
	for (int i = 1; i <= 5; i++) {
		printf("%d 번째 실수를 입력하시오. ", i);
		scanf("%f", &array[i - 1]);
	}

	float hap = 0;
	float max = array[0];
	float min = array[0];

	for (int i = 0; i < 5; i++) {
		hap += array[i];
		if (array[i] > max) {
			max = array[i];
		}
		if (array[i] < min) {
			max = array[i];
		}
	}
	printf("---- 결과 ----\n");
	printf("평균은 %f입니다.\n", hap / 5);
	printf("최댓값은 %f입니다\n.", max);
	printf("최솟값은 %f입니다.", min);

	return 0;
}