#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
	char input[1000];
	printf("입력 : ");
	gets_s(input, sizeof(input));
	input[strcspn(input, "\n")] = 0;

	char** stack = (char**)malloc(sizeof(char*) * 50);
	int top = -1; //스택 정의

	int len = strlen(input);
	int depth = 0; //들여쓰기 체크

	for (int i = 0; i < len; i++) {
		if (input[i] == '<') { //태그 처리 시작
			char tag[50];
			int j = 0;
			while (input[i] != '>') {
				tag[j++] = input[i++];
			}
			tag[j++] = '>'; tag[j] = '\0'; //태그 완성

			if (tag[1] == '/') {
				if (top == -1) {
					printf("Error: 태그 짝 안 맞음");
					return;
				}

				char* last_tag = stack[top];
				if (strncmp(last_tag + 1, tag + 2, strlen(tag) - 3) == 0) {
					depth--;
					for (int k = 0; k < depth; k++) printf("  "); //들여쓰기 출력
					printf("%s\n", tag);
					free(stack[top--]);//태그 메모리 해제
				}
				else {
					printf("Error: 태그 구조 잘못됨");
					return;
				}
			}
			//<div> 같은 경우
			else {
				for (int k = 0; k < depth; k++) printf("  ");
				printf("%s\n", tag);

				stack[++top] = (char*)malloc(sizeof(char) * 50);
				strcpy(stack[top], tag);
				depth++;
			}
		}
		//그냥 글자
		else {
			char text[100];
			int j = 0;
			while (i < len && input[i] != '<') {
				text[j++] = input[i++];
			}
			text[j] = '\0';
			i--;

			if (j > 0) {
				for (int k = 0; k < depth; k++) printf("  ");
				printf("%s\n", text);
			}
		}
	}

	if (top != -1) printf("Error: 닫히지 않은 태그 있음");
	
	free(stack);
}