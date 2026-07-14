import sys

def compress(text):
    """
    문자열을 런렝스 압축하는 함수 (예: "AAABBBCC" -> "A3B3C2")
    """
    if not text: return
    arr = []
    a = text[0]  # 현재 연속 여부를 확인할 기준 문자
    count = 0    # 문자의 연속 횟수 카운터
    arr.append(text[0]) # 압축 결과 배열에 첫 문자 추가
    
    for i in range(len(text)):
        if text[i] == a:
            # 기준 문자와 같으면 카운트 증가
            count += 1
        else: 
            # 다른 문자가 등장하면 지금까지의 카운트를 추가하고 새로운 문자 등록
            arr.append(count)
            arr.append(text[i])
            
            count = 1  # 새로운 문자의 카운트 시작
            if i + 1 >= len(text): break # 마지막 문자라면 루프 종료 조건 체크
            a = text[i]  # 기준 문자 갱신
            
    arr.append(count) # 마지막으로 세고 있던 문자의 카운트 추가
    print("".join(str(x) for x in arr)) # 배열을 문자열로 변환하여 출력


def decompress(code):
    """
    압축된 코드를 원래 문자열로 복원하는 함수 (예: "A3B3C2" -> "AAABBBCC")
    """
    if not is_valid_code(code): return "ERROR" # 올바른 형식의 압축 코드인지 검증
    arr = []
    a = 0  # 문자(알파벳)의 인덱스 위치를 기억하는 포인터
    b = 0  # 숫자가 끝나고 다음 문자가 시작되는 위치를 기억하는 포인터

    for i in range(len(code)):
        # 첫 번째 이후로 등장하는 문자를 찾았을 때 (숫자 파싱의 경계면)
        if i > 0 and code[i].isalpha():
            b = i
            c = code[a] # 복원할 대상 문자
            t = 0
            # 자릿수를 계산하여 뒤의 숫자(반복 횟수)를 정수로 변환
            for j in range(b - a - 1):
                t += int(code[b - 1 - j]) * (10 ** j)
            # 파싱한 횟수만큼 문자를 결과 배열에 추가
            for j in range(t):
                arr.append(c)
            a = b # 다음 문자의 시작점을 현재 위치로 갱신

    # 루프가 끝난 후, 가장 마지막에 남은 문자-숫자 세트 처리
    b = len(code)
    c = code[a]   
    t = 0
    # 마지막 숫자의 자릿수 변환
    for i in range(b - a - 1):
        t += int(code[b - 1 - i]) * (10 ** i)
    
    c = code[a]
    arr.append(c*t) # 파이썬 문자열 곱셈 연산을 이용해 마지막 문자 복원 및 추가
        
    return "".join(arr) # 배열을 하나의 문자열로 합쳐 반환

def is_valid_code(code):
    """
    입력된 압축 코드가 문법적으로 올바른지 검사하는 함수
    조건: 첫 글자는 문자, 끝 글자는 숫자, 빈 문자열 제외, 문자 뒤에는 반드시 1개 이상의 숫자가 와야 함.
    """
    if not code: return False
    if not code[0].isalpha(): # 첫 글자가 문자가 아니면 거짓
        return False
    if not code[-1].isdigit(): # 마지막 글자가 숫자가 아니면 거짓
        return False
        
    num_count = 0 # 연속된 숫자의 개수를 세는 카운터
    
    for i in range(len(code)):
        char = code[i]
        if char.isalpha():
            # 새로운 문자를 만났는데, 그 전 문자 뒤에 숫자가 한 개도 없었다면 잘못된 형식 (예: "AB3")
            if i > 0 and num_count < 1:
                return False
            num_count = 0 # 숫자가 나와야 하므로 카운터 초기화
        elif char.isdigit():
            num_count += 1 # 숫자 카운트 증가
        else:
            return False # 알파벳과 숫자가 아닌 특수문자나 공백이 있으면 거짓
            
    if num_count < 1: # 마지막 문자 뒤에도 숫자가 없으면 거짓
        return False
    return True


print("프로그램 종료: 0 입력")
while True:
    user_input = input("Enter your command: ")
    
    # 입력된 명령어가 압축 해제인지 압축인지 판별
    if "decompress(" in user_input:
        command = "decompress"
    elif "compress(" in user_input: # 'decompress' 스펠링 안에 'compress'가 포함되어 있으므로 반드시 이 순서대로 체크해야 함
        command = "compress"
    elif user_input == "0":
        print("프로그램 종료")
        sys.exit()
    else: 
        print("유효하지 않은 입력")
        continue
        
    # 명령어 형식에서 실제 데이터만 추출 (예: compress("AAABBB") -> AAABBB)
    raw_data = user_input.split(command + '("')[1]
    data = raw_data.split('")')[0]
    
    # 추출한 데이터를 가지고 알맞은 함수 호출
    if command == "compress":
        compress(data)
    elif command == "decompress":
        print(decompress(data))