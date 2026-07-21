#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//문자 리스트가 있다면, 그 리스트를 기반으로 표같이 문자의 나온 횟수를 저장할 수 있을 것이라 생각
//아스키코드가 그 역할을 할 수 있으므로, 아스키코드를 기반으로 가장 많이 나온 문자를 찾을 수 있었음.

void main() {
	char str[100];
	int count[256] = { 0 }; //문자 등장 횟수 저장용 배열(아스키코드 기반)
	
	gets_s(str, sizeof(str));

	char* p = str; // 문자열 시작을 포인터 p에 저장

	while (*p != '\0') {
		p++;
	} p--; //널 문자 때문에 한 칸 뒤로 이동

	while (p >= str) {
		printf("%c", *p);
		p--;
	}

	printf("\n");

	//최다 등장 문자 찾기
	p = str; //초기화
	while (*p != '\0') {
		if (*p != ' ') //공백 제외
			count[(int)*p]++;
		p++;
	}

	int max = 0;
	char max_char = '\0';

	for (int i = 0; i < 256; i++) {
		if (count[i] > max) {
			max = count[i];
			max_char = (char)i; //해당 인덱스는 아스키코드와 동일하므로 그대로 char형으로 바꿔준다.
		}
	}

	printf("최다 등장 문자 : %c\n", max_char);

}