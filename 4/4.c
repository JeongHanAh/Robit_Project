#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char country[30];
	char province[30];
	char city[30];
	char district[30];
} address;

typedef struct {
	int id;
	char name[30];
	address addr; 
	int grade;
} student;

void clearBuffer() {
	while (getchar() != '\n'); //버퍼 지우기용 (예외처리)
}

//숫자만 통과할 수 있는 함수
int getNum() {
	int num;
	while (scanf("%d", &num) != 1) {
		printf("Error: 숫자가 아님.");
		clearBuffer();
	}
	clearBuffer(); //엔터 제거
	return num;
}

void add(student* arr, int* count) {
	if (*count >= 100) { //최대 100명으로 설정
		printf("꽉 참.\n");
		return;
	}

	student s;
	printf("번호: ");
	s.id = getNum();

	printf("이름: ");
	scanf("%s", s.name);

	printf("나라: ");
	scanf("%s", s.addr.country);
	printf("도: ");
	scanf("%s", s.addr.province);
	printf("시: ");
	scanf("%s", s.addr.city);
	printf("구: ");
	scanf("%s", s.addr.district);

	printf("성적: ");
	s.grade = getNum();

	arr[*count] = s;
	(*count)++;
	printf("추가됨.\n");
}

void printAll(student* arr, int count) {
	if (count == 0) {
		printf("비어있음.\n");
		return;
	}
	for (int i = 0; i < count; i++) {
		printf("%d | %s | %s %s %s %s | %d\n",
			arr[i].id, arr[i].name,
			arr[i].addr.country, arr[i].addr.province, arr[i].addr.city, arr[i].addr.district,
			arr[i].grade);
	}
}

void search(student* arr, int count) {
	if (count == 0) {
		printf("비어있음.\n");
		return;
	}

	int choice;
	printf("1.번호 2.성적 3.나라 4.도 5.시 6.구 : ");
	choice = getNum();

	int searchInt;
	char searchStr[30];
	int found = 0;

	if (choice == 1 || choice == 2) {
		printf("숫자 입력: ");
		searchInt = getNum();
	}
	else {
		printf("문자 입력: ");
		scanf("%s", searchStr);
	}

	for (int i = 0; i < count; i++) {
		int match = 0;
		if (choice == 1 && arr[i].id == searchInt) match = 1;
		else if (choice == 2 && arr[i].grade == searchInt) match = 1;
		else if (choice == 3 && strcmp(arr[i].addr.country, searchStr) == 0) match = 1;
		else if (choice == 4 && strcmp(arr[i].addr.province, searchStr) == 0) match = 1;
		else if (choice == 5 && strcmp(arr[i].addr.city, searchStr) == 0) match = 1;
		else if (choice == 6 && strcmp(arr[i].addr.district, searchStr) == 0) match = 1;

		if (match == 1) {
			printf("이름: %s, 번호: %d\n", arr[i].name, arr[i].id);
			found = 1;
		}
	}
	if (found == 0) printf("없음.\n");
}

void sort(student* arr, int count) {
	if (count < 2) return; // 예외처리

	int choice;
	printf("1.번호순 2.이름순 3.성적순 4.나라순 : ");
	choice = getNum();

	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1 - i; j++) {
			int swap = 0;
			if (choice == 1 && arr[j].id > arr[j + 1].id) swap = 1;
			else if (choice == 2 && strcmp(arr[j].name, arr[j + 1].name) > 0) swap = 1;
			else if (choice == 3 && arr[j].grade < arr[j + 1].grade) swap = 1;
			else if (choice == 4 && strcmp(arr[j].addr.country, arr[j + 1].addr.country) > 0) swap = 1;

			if (swap == 1) {
				student temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void del(student* arr, int* count) {
	if (*count == 0) {
		printf("비어있음.\n");
		return;
	}

	printf("삭제할 번호 입력: ");
	int targetId = getNum();

	int matchIdx[100]; //중복 확인용 배열
	int matchCount = 0;

	for (int i = 0; i < *count; i++) {
		if (arr[i].id == targetId) {
			matchIdx[matchCount] = i;
			matchCount++;
		}
	}

	if (matchCount == 0) {
		printf("없음.\n");
		return;
	}

	int delIdx = matchIdx[0];

	if (matchCount > 1) { //중복일 때 선택해서 삭제
		for (int i = 0; i < matchCount; i++) {
			int idx = matchIdx[i];
			printf("[%d] 이름: %s, 성적: %d\n", i + 1, arr[idx].name, arr[idx].grade);
		}
		printf("몇 번 삭제? ");
		int sel = getNum();
		delIdx = matchIdx[sel - 1];
	}

	for (int i = delIdx; i < *count - 1; i++) { //배열 덮어쓰기
		arr[i] = arr[i + 1];
	}
	(*count)--;
	printf("삭제됨.\n");
}

void save(student* arr, int count) {
	FILE* file = fopen("attendance.txt", "w");
	if (file == NULL) return;

	fprintf(file, "%d\n", count);
	for (int i = 0; i < count; i++) {
		fprintf(file, "%d %s %s %s %s %s %d\n",
			arr[i].id, arr[i].name,
			arr[i].addr.country, arr[i].addr.province, arr[i].addr.city, arr[i].addr.district,
			arr[i].grade);
	}
	fclose(file);
	printf("저장됨.\n");
}

void load(student* arr, int* count) {
	FILE* file = fopen("attendance.txt", "r");
	if (file == NULL) return; //파일 없으면 패스

	fscanf(file, "%d", count);
	for (int i = 0; i < *count; i++) {
		fscanf(file, "%d %s %s %s %s %s %d",
			&arr[i].id, arr[i].name,
			arr[i].addr.country, arr[i].addr.province, arr[i].addr.city, arr[i].addr.district,
			&arr[i].grade);
	}
	fclose(file);
}

void main() {
	student arr[100];
	int count = 0;

	load(arr, &count); //시작할 때 불러오기

	int menu;
	printf("종료하려면 6 입력.\n");

	while (1) {
		printf("\n1.추가 2.삭제 3.찾기 4.정렬 5.출력 6.종료 : ");
		menu = getNum();

		if (menu == 1) {
			add(arr, &count);
		}
		else if (menu == 2) {
			del(arr, &count);
		}
		else if (menu == 3) {
			search(arr, count);
		}
		else if (menu == 4) {
			sort(arr, count);
		}
		else if (menu == 5) {
			printAll(arr, count);
		}
		else if (menu == 6) {
			save(arr, count);
			break;
		}
		else printf("잘못된 입력.\n");
	}
}