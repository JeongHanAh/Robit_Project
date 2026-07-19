#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int set[20];
int size = 0;

//특정 원소가 있을 시 그 인덱스 반환
int find(int x) {
	for (int i = 0; i < size; i++) {
		if (set[i] == x) return i;
	}
	return -1;
}

void add(int x) {
	if (find(x) == -1) { // 없을 때만 추가
		set[size++] = x;
	}
}

void remove_val(int x) {
	int idx = find(x);
	if (idx != -1) {
		for (int i = idx; i < size - 1; i++) {
			set[i] = set[i + 1];
		}
		size--;
	}
}

int check(int x) {
	if (find(x) != -1) return 1;
	else return 0;
}

void toggle(int x) {
	if (find(x) != -1) {
		remove_val(x);
	}
	else {
		add(x);
	}
}

void all() {
	size = 20;
	for (int i = 0; i < 20; i++) {
		set[i] = i + 1;
	}
}

void empty() {
	size = 0;
}

//주어진 조건의 함수 전부 구현

void print_set() {
	printf("집합: { ");
	for (int i = 0; i < size; i++) {
		printf("%d, ", set[i]);
	}
	printf(" }\n\n");
}

void main() {
	char cmd[20];
	int x;

	printf("연산을 선택하세요. ( 1 <= x <= 20 )\n");
	printf("add X\n");
	printf("remove X\n");
	printf("check X\n");
	printf("toggle X\n");
	printf("all 0\n");
	printf("empty 0\n\n");

	while (1) {
		printf("input : ");
		// 더 이상 입력이 없으면 종료
		if (scanf("%s %d", cmd, &x) == EOF) {
			break;
		}

		if (strcmp(cmd, "add") == 0) {
			add(x);
			print_set();
		}
		else if (strcmp(cmd, "remove") == 0) {
			remove_val(x);
			print_set();
		}
		else if (strcmp(cmd, "check") == 0) {
			int res = check(x);
			// 예제 이미지 출력 방식(1 집합 : { 3, })에 맞추어 출력
			printf("%d ", res);
			print_set();
		}
		else if (strcmp(cmd, "toggle") == 0) {
			toggle(x);
			print_set();
		}
		else if (strcmp(cmd, "all") == 0) {
			all();
			print_set();
		}
		else if (strcmp(cmd, "empty") == 0) {
			empty();
			print_set();
		}
	}
}