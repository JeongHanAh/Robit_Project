#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct student { //구조체 배열 만들기
	int grade;
	float gpa; //gradepointaverage
	char name[10];
}stu; //stu로 씀

void main() {
	stu list[5]; // 5명 입력받을 메모리 할당
	for (int i = 0; i < 5; i++) {
		scanf("%d %f %s", &list[i].grade, &list[i].gpa, &list[i].name);
	} // student 속성 입력받기

	for (int i = 0; i < 5 - 1; i++) { //선택 정렬, 조건은 if-elseif로 한꺼번에 비교
		int least = i;
		for (int j = i + 1; j < 5; j++) {
			if (list[j].grade < list[least].grade) {
				least = j;
			} //학년 비교		
			else if (list[j].grade == list[least].grade && list[j].gpa < list[least].gpa) {
				least = j;
			} //학년이 같으면 성적 비교
			else if (list[j].grade == list[least].grade && list[j].gpa == list[least].gpa) {
				// strcmp는 아스키코드 기준. 앞 문자열이 더 빠르면 음수 반환
				if (strcmp(list[j].name, list[least].name) < 0) {
					least = j;
				}
			} //학년, 성적 같으면 이름순
		}

		if (i != least) {
			stu temp = list[i]; // swap용 구조체 생성
			list[i] = list[least];
			list[least] = temp;
		}
	}

	printf("\n");
	for (int i = 0; i < 5; i++) {
		printf("%d %.1f %s\n", list[i].grade, list[i].gpa, list[i].name);
	}
}
