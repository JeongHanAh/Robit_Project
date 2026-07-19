#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void main() {
	char input[100];
	char subStr[100];

	printf("최대 99개 문자 입력 <inputStr> : ");
	scanf("%s", input);

	printf("찾는 문자열 <subStr> : ");
	scanf("%s", subStr);

	int len_in = strlen(input);
	int len_sub = strlen(subStr);

	printf("%s의 위치 : ", subStr);

	//문자열 탐색
	for (int i = 0; i <= len_in - len_sub; i++) {
		int match = 1;
		for (int j = 0; j < len_sub; j++) {
			if (input[i + j] != subStr[j]) {
				match = 0;
				break;
			}
		}

		if (match == 1) {
			printf("%d ", i + 1); //인덱스 번호에서 1 추가
		}
	}

	printf("\n");

}