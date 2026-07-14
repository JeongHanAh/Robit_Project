import sys # 프로그램 강제 종료(sys.exit())를 사용하기 위해 sys 모듈 임포트

# 10x10 미로 맵 데이터 정의 (1: 벽, 0: 갈 수 있는 길, 2: 목적지, 9: 지나간 길)
maze = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 1, 0, 0, 0, 1, 2, 1],
    [1, 0, 0, 1, 0, 1, 0, 1, 0, 1],
    [1, 0, 1, 1, 0, 1, 0, 1, 0, 1],
    [1, 0, 0, 1, 0, 1, 0, 1, 0, 1],
    [1, 1, 0, 1, 0, 1, 0, 1, 0, 1],
    [1, 0, 0, 1, 0, 1, 0, 1, 0, 1],
    [1, 0, 1, 1, 0, 1, 0, 1, 0, 1],
    [1, 0, 0, 0, 0, 1, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
]

# 플레이어의 초기 시작 좌표 설정 (x=1, y=1)
pos_x = 1
pos_y = 1

print("Moving to wasd")
maze[pos_y][pos_x] = 9 # 시작 위치를 '지나간 길(9)'로 표시

# 미로 탐색을 위한 무한 루프 시작
while True:
    maze[pos_y][pos_x] = 9 # 현재 플레이어의 위치를 '지나간 길(9)'로 실시간 갱신
    
    # 현재 미로의 전체 상태를 행(row) 단위로 화면에 출력
    for row in maze:
        print(row)
        
    # [고립 여부 체크] 상, 하, 좌, 우 모든 방향이 0(갈 수 있는 길)이 아닌 경우
    if(maze[pos_y - 1][pos_x] != 0 and 
        maze[pos_y + 1][pos_x] != 0 and 
        maze[pos_y][pos_x - 1] != 0 and 
        maze[pos_y][pos_x + 1] != 0):
        
        # 사방이 막혀있는데 그중 목적지(2)도 없다면 완전히 갇힌 상태로 판정
        if 2 not in [maze[pos_y-1][pos_x], maze[pos_y+1][pos_x], maze[pos_y][pos_x-1], maze[pos_y][pos_x+1]]:
            print("All Blocked")
            sys.exit() # 게임 오버로 프로그램 종료
            
    # 사용자로부터 이동 명령 입력 받기
    move = input("To Where: ")
    
    # [w 입력: 위로 이동]
    if(move == "w"):
        # 위쪽 칸이 벽(1)이거나 이미 지나간 길(9)이면 이동 불가
        if maze[pos_y - 1][pos_x] == 1 or maze[pos_y - 1][pos_x] == 9:
            print("Blocked")
            continue # 아래 코드를 건너뛰고 입력 단계로 돌아감
        pos_y = pos_y - 1 # 이동이 가능하면 y 좌표를 1 감소(위로 한 칸)
        
    # [a 입력: 왼쪽으로 이동]
    elif(move == "a"):
        # 왼쪽 칸이 벽(1)이거나 이미 지나간 길(9)이면 이동 불가
        if maze[pos_y][pos_x - 1] == 1 or maze[pos_y][pos_x - 1] == 9:
            print("Blocked")
            continue
        pos_x = pos_x - 1 # 이동이 가능하면 x 좌표를 1 감소(왼쪽으로 한 칸)
        
    # [s 입력: 아래로 이동]
    elif(move == "s"):
        # 아래쪽 칸이 벽(1)이거나 이미 지나간 길(9)이면 이동 불가
        if maze[pos_y + 1][pos_x] == 1 or maze[pos_y + 1][pos_x] == 9:
            print("Blocked")
            continue
        pos_y = pos_y + 1 # 이동이 가능하면 y 좌표를 1 증가(아래로 한 칸)
        
    # [d 입력: 오른쪽으로 이동]
    elif(move == "d"):
        # 오른쪽 칸이 벽(1)이거나 이미 지나간 길(9)이면 이동 불가
        if maze[pos_y][pos_x + 1] == 1 or maze[pos_y][pos_x + 1] == 9:
            print("Blocked")
            continue
        pos_x = pos_x + 1 # 이동이 가능하면 x 좌표를 1 증가(오른쪽으로 한 칸)
        
    # w, a, s, d 외의 잘못된 키를 입력했을 때 예외 처리
    else: 
        print("Invalid input")
        continue
        
    # [목적지 도달 체크] 새로 이동한 좌표의 값이 목적지(2)인 경우
    if maze[pos_y][pos_x] == 2:
        print("Clear!")
        sys.exit() # 미로 탈출 성공으로 프로그램 종료