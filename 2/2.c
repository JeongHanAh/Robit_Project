#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point {
	int x;
	int y;
}pos;

void main() {
	int a;
	scanf("%d", &a); //입력받을 좌표 수

	pos* p = (pos*)malloc(sizeof(pos)*a); // a만큼 구조체 배열 메모리 할당
	double max = 0;
	double hap = 0;

	double* distance = (double*)malloc(sizeof(pos*) * a); //거리 저장용

	for (int i = 0; i < a; i++) {
		scanf("%d %d", &p[i].x, &p[i].y);
	}

	for (int i = 0; i < a; i++) {
		distance[i] = sqrt((double)(p[i].x * p[i].x + p[i].y * p[i].y)); //거리 구하고 저장
	}

	max = distance[0];
	int idx = 0; //가장 거리가 먼 좌표 인덱스 값 저장용
	
	for (int i = 0; i < a; i++) {
		if (max < distance[i]) {
			max = distance[i];
			idx = i;
		}
	} //가장 먼 좌표 찾음

	for (int i = 0; i < a; i++) {
		if (i != idx) {
			double dx = (double)(p[idx].x - p[i].x);
			double dy = (double)(p[idx].y - p[i].y);
			hap += sqrt(dx * dx + dy * dy);
		}
	}

	printf("가장 거리가 먼 좌표는 (%d, %d)이며, 다른 좌표의 거리 총합은 약 %.1f입니다.", p[idx].x, p[idx].y, hap);
	
	free(p);
	free(distance);
}
