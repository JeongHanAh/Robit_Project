#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


//중첩구조체 구현
typedef struct date{
	int year, month, day;
} date;

typedef struct time{
	int hour, min, sec;
} time;
typedef struct timestamp {
	date d;
	time t;
} timestamp;

int days_in_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //달 별 일 수 저장

//윤년 판별기
int leapyear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		return 1;
	} return 0;
}

//그냥 초로 다 쪼개고 다시 합치는 방식
long long totalsec(timestamp dt) {
	long long totalday = 0;

	for (int y = 1; y < dt.d.year; y++) {
		totalday += 365 + leapyear(y);
	} //작년까지의 총 일수 더하기
	for (int m = 1; m < dt.d.month; m++) {
		totalday += days_in_month[m];
		if (m == 2 && leapyear(dt.d.year)) {
			totalday += 1; //2월에 윤년이면 하루 추가
		}
	}

	//이번 달 어제까지 일 수 더하기
	totalday += (dt.d.day - 1);
	
	//총 day를 sec로 바꾸고 시/분/초 더하기
	long long totalsec = totalday * 24 * 3600;
	totalsec += dt.t.hour * 3600;
	totalsec += dt.t.min * 60;
	totalsec += dt.t.sec;

	return totalsec;
}

void main() {
	timestamp dt1, dt2;

	scanf("%d %d %d %d %d %d", &dt1.d.year, &dt1.d.month, &dt1.d.day, &dt1.t.hour, &dt1.t.min, &dt1.t.sec);
	scanf("%d %d %d %d %d %d", &dt2.d.year, &dt2.d.month, &dt2.d.day, &dt2.t.hour, &dt2.t.min, &dt2.t.sec);

	long long sec1 = totalsec(dt1);
	long long sec2 = totalsec(dt2);


	//두 시간 차이 구하기
	long long diff = sec2 - sec1;
	if (diff < 0) { //음수면 양수로 변환
		diff = -diff;
	}

	//초로 시, 분, 초 연산
	int final_h = diff / 3600;
	int final_m = (diff % 3600) / 60;
	int final_s = diff % 60;

	printf("%d시 %d분 %d초\n", final_h, final_m, final_s);
}


