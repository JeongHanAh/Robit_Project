import csv
import json
import os
import sys

# 파일 읽기에서 계속 버그가 발생하여 동적으로 파일 위치를 계산하도록 수정
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CSV_PATH = os.path.join(BASE_DIR, "students.csv")
CLEAN_CSV_PATH = os.path.join(BASE_DIR, "clean_students.csv")
SUMMARY_JSON_PATH = os.path.join(BASE_DIR, "summary.json")

valid_students = []
total_score = 0
max_score = 0 #본격적으로 만들 때는 -1로 처리하는게 예외처리에 유리

try:
    with open(CSV_PATH, "r", newline = "", encoding = "utf-8") as file:
        reader = csv.reader(file)
        header = next(reader) #name, score 건너뛰기

        for row in reader:
            if not row or len(row) < 2:
                continue #빈 행 예외 처리
            name = row[0]
            raw_score = row[1]

            try:
                #숫자로 변환, 범위 검사
                score = int(raw_score)
                if not (0 <= score <= 100):
                    raise ValueError(f"허용 범위(0~100) 초과: {score}")
                total_score += score
                #유효 데이터 저장
                valid_students.append([name, score])
                if score >max_score:
                    max_score = score
            
            except ValueError as e:
                #오류 행 처리 후 다음 행
                print(f"[오류 발생] 학생: {name} | 사유: {e}")
except FileNotFoundError:
    print("Error: Students.csv 파일을 찾을 수 없습니다.")
    sys.exit(1)

#쓰기도 마찬가지
with open(CLEAN_CSV_PATH, "w", newline = "", encoding = "utf-8") as file:
    writer = csv.writer(file)
    writer.writerow(["name", "score"]) #헤더
    writer.writerows(valid_students)

count = len(valid_students)
average = total_score / count if count > 0 else 0 #ZeroDivisionError 방지

summary = {
    "count": count,
    "average": round(average, 2), 
    "max_score": max_score
}

# 동적 경로
with open(SUMMARY_JSON_PATH, "w", encoding = "utf-8") as file:
    json.dump(summary, file, ensure_ascii = False, indent = 4)

print("\n Mission Complete!")