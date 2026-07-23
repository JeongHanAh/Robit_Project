#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void removespace(char arr[]) { //공백 제거용
	int i = 0, j = 0;
	
	while (arr[i] != '\0') {
		if (arr[i] != ' ') {
			arr[j] = arr[i];
			j++;
		}
		i++;
	}
	arr[j] = '\0'; //문자열 끝에 널문자 삽입
}

int ispalindrome(char arr[]) {
	int left = 0;
	int right = strlen(arr) - 1; //마지막 인덱스

	while (left < right) {
		if (arr[left] != arr[right]) {
			return 0;
		}
		left++;
		right--;
	}
	return 1;
}

void main() {
	char arr[100];
	gets_s(arr, sizeof(arr));
	if (ispalindrome(arr) == 1) {
		printf("회문");
	}
	else printf("회문 아님");
}
