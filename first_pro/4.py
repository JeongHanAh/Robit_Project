import sys

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
pos_x = 1
pos_y = 1
print("Moving to wasd")
maze[pos_y][pos_x] = 9
while True:
    maze[pos_y][pos_x] = 9
    for row in maze:
        print(row)
    if(maze[pos_y - 1][pos_x] != 0 and 
        maze[pos_y + 1][pos_x] != 0 and 
        maze[pos_y][pos_x - 1] != 0 and 
        maze[pos_y][pos_x + 1] != 0):
        if 2 not in [maze[pos_y-1][pos_x], maze[pos_y+1][pos_x], maze[pos_y][pos_x-1], maze[pos_y][pos_x+1]]:
            print("All Blocked")
            sys.exit()
    move = input("To Where: ")
    if(move == "w"):
        if maze[pos_y - 1][pos_x] == 1 or maze[pos_y - 1][pos_x] == 9:
            print("Blocked")
            continue
        pos_y = pos_y - 1
    elif(move == "a"):
        if maze[pos_y][pos_x - 1] == 1 or maze[pos_y][pos_x - 1] == 9:
            print("Blocked")
            continue
        pos_x = pos_x - 1
    elif(move == "s"):
        if maze[pos_y + 1][pos_x] == 1 or maze[pos_y + 1][pos_x] == 9:
            print("Blocked")
            continue
        pos_y = pos_y + 1
    elif(move == "d"):
        if maze[pos_y][pos_x + 1] == 1 or maze[pos_y][pos_x + 1] == 9:
            print("Blocked")
            continue
        pos_x = pos_x + 1
    else: 
        print("Invalid input")
        continue
    if maze[pos_y][pos_x] == 2:
        print("Clear!")
        sys.exit()
    
    
