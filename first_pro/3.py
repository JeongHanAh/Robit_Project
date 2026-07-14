print("Enter 0 to exit the program.") # 프로그램 종료 방법 안내 출력

mode = []    # 사용자가 입력한 명령어 분할 배열을 저장할 변수 초기화
mylist = []  # 명령어를 통해 조작할 메인 리스트 생성

# 사용자가 0을 입력할 때까지 무한 반복하는 루프
while True:
    my_input = input("Enter your command: ") # 사용자로부터 명령어 입력받기
    
    if my_input == "0": break # 입력값이 "0"이면 반복문을 빠져나가 프로그램 종료
    
    mode = my_input.split() # 공백을 기준으로 입력 문자열을 잘라 리스트로 저장 (예: "append apple" -> ["append", "apple"])
    
    if not mode: continue # 아무것도 입력하지 않고 엔터를 쳤을 경우(빈 리스트인 경우) 루프의 처음으로 이동
    
    # [append 명령어] 리스트 맨 뒤에 값 추가 (예: append apple)
    if(mode[0] == "append"): 
        mylist.append(mode[1])
        
    # [insert 명령어] 지정한 인덱스 위치에 값 삽입 (예: insert 0 banana)
    elif(mode[0] == "insert"): 
        mylist.insert(int(mode[1]), mode[2]) # 인덱스는 숫자가 필요하므로 int()로 형변환
        
    # [remove 명령어] 리스트에서 특정 값을 찾아 삭제 (예: remove apple)
    elif(mode[0] == "remove"):
        if mode[1] in mylist:      # 삭제하려는 값이 리스트에 존재하는지 확인
            mylist.remove(mode[1]) # 존재하면 삭제
        else:
            print("Not Found")     # 존재하지 않으면 에러 메시지 출력
            
    # [pop 명령어] 지정한 인덱스 위치의 값을 제거 (예: pop 1)
    elif(mode[0] == "pop"):
        # 입력한 인덱스가 리스트의 올바른 범위(0부터 리스트 길이 미만) 내에 있는지 확인
        if 0 <= int(mode[1]) and int(mode[1]) < len(mylist):
            mylist.pop(int(mode[1])) # 범위 내에 있으면 해당 위치 값 삭제
        else:
            print("Not Found")       # 인덱스 범위를 벗어나면 에러 메시지 출력
            
    # [len 명령어] 현재 리스트의 요소 개수(길이) 출력
    elif(mode[0] == "len"): print(len(mylist))
    
    # [print 명령어] 현재 리스트 전체 상태 출력
    elif(mode[0] == "print"): print(mylist)
    
    # [clear 명령어] 리스트의 모든 요소 삭제하여 비우기
    elif(mode[0] == "clear"): mylist.clear()
    
    # 정의되지 않은 엉뚱한 명령어를 입력했을 경우 처리
    else: print("Invalid input")