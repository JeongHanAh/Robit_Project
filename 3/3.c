#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//sort가 아니고 그냥 3가지 종류로 나뉘는 것이므로 if문으로 판별 가능
int check(char* n) {
	if (strcmp(n, "cdefgabC") == 0) {
		return 1;
	}
	else if (strcmp(n, "Cbagfedc") == 0) {
		return 2;
	}
	else {
		return 3;
	}
}

void main() {
	//null 문자 주의
	char notes[9];

	printf("음 입력 \n");
	scanf("%s", notes);

	printf("\n결과 : ");

	switch (check(notes)) {
	case 1:
		printf("ascending\n");
		break;
	case 2:
		printf("descending\n");
		break;
	case 3:
		printf("mixed\n");
		break;
	}
}