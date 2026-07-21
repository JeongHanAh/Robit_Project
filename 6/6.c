#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/*
예제에 주어진대로 3행 4열 사각형 모양을 만든다고 가정했을 때
나머지 연산자로 구한다고 했을 때 굉장히 쉽게 구해지는 것을 알 수 있다.
*/

void main() {
	int arr[20]; 
	int count = 0;
	int shape[3][4];
	
	//첫 입력
	printf("input: ");
	if (scanf("%d", &arr[count]) == 1) {
		count++;
	}

	//무한루프, 숫자가 아닌 문자 등을 입력하였을 시 탈출
	while (1) {
		//포인터로 도형 채우기
		int* p = &shape[0][0]; 
		
		for (int i = 0; i < 12; i++) { //i를 count로 나눴을 때 나오는 나머지로 패턴 그리기
			*(p + i) = arr[i % count];
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				//포인터식 배열 접근법
				printf("%d", *(p + i * 4 + j));
			}
			printf("\n");
		}
		printf("\n");

		//계속 입력 받기
		printf("next input : ");

		//정수가 아니면 0을 반환
		if (scanf("%d", &arr[count]) != 1) {
			break;
		}

		count++;
	}

}