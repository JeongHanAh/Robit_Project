#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//반환값이 1이면 제곱ㄴㄴ수
int square(int n) {
	//제곱수가 n보다 작거나 같을 때까지
	for (int i = 2; i * i <= n; i++) {
		if (n % (i * i) == 0){
			return 0;
		}
	}
	return 1;
}

void main() {
	int min, max;
	int count = 0;
	int arr[1000];

	printf("min : ");
	scanf("%d", &min);

	printf("max : ");
	scanf("%d", &max);

	for (int i = min; i <= max; i++) {
		if (square(i)) { //1을 반환하면 True로 자동 if 성립 (0이면 거짓)
			arr[count] = i;
			count++;
		}
	}

	printf("제곱 ㄴㄴ수 : %d개\n", count);
	for (int i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}
}