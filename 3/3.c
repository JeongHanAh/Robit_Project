#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct goods {
	char name[30];
	int price;
}goods;

void main() {
	int a;
	scanf("%d", &a);
	goods* g = (goods*)malloc(sizeof(goods) * a); //a만큼 메모리 할당
	
	for (int i = 0; i < a; i++) {
		scanf("%s %d", &g[i].name, &g[i].price);
	}

	char name_u[30]; 
	int hap = 0; //더한 값이 없으면 0으로 출력

	getchar(); //입력 버퍼 줄바꿈 방지
	gets_s(name_u, sizeof(name_u)); //물품 이름 입력받기

	for (int i = 0; i < a; i++) {
		if (strcmp(name_u, g[i].name) == 0) {
			hap += g[i].price;
		}
	}  //이름 매칭되면 가격 더하기

	printf("\n%d", hap);

	free(g);

}
