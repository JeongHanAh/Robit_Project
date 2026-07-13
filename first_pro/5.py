import sys

def compress(text):
    if not text: return
    arr = []
    a = text[0]
    count = 0
    arr.append(text[0])
    
    for i in range(len(text)):
        if text[i] == a:
            count += 1
        else: 
            arr.append(count)
            arr.append(text[i])
            
            count = 1
            if i + 1 >= len(text): break
            a = text[i]
            
    arr.append(count)
    print("".join(str(x) for x in arr))


def decompress(code):
    if not is_valid_code(code): return "ERROR"
    arr = []
    a = 0
    b = 0

    for i in range(len(code)):
        if i > 0 and code[i].isalpha():
            b = i
            c = code[a]
            t = 0
            for j in range(b - a - 1):
                t += int(code[b - 1 - j]) * (10 ** j)
            for j in range(t):
                arr.append(c)
            a = b

    b = len(code)
    c = code[a]   
    t = 0
    for i in range(b - a - 1):
        t += int(code[b - 1 - i]) * (10 ** i)
    
    c = code[a]
    arr.append(c*t)
        
    return "".join(arr)

def is_valid_code(code):
    if not code: return False
    if not code[0].isalpha():
        return False
    if not code[-1].isdigit():
        return False
        
    num_count = 0
    
    for i in range(len(code)):
        char = code[i]
        if char.isalpha():
            if i > 0 and num_count < 1:
                return False
            num_count = 0
        elif char.isdigit():
            num_count += 1
        else:
            return False
            
    if num_count < 1:
        return False
    return True


print("프로그램 종료: 0 입력")
while True:
    user_input = input("Enter your command: ")
    if "decompress(" in user_input:
        command = "decompress"
    elif "compress(" in user_input:
        command = "compress"
    elif user_input == "0":
        print("프로그램 종료")
        sys.exit()
    else: 
        print("유효하지 않은 입력")
        continue
        
    raw_data = user_input.split(command + '("')[1]
    data = raw_data.split('")')[0]
    if command == "compress":
        compress(data)
    elif command == "decompress":
        print(decompress(data))