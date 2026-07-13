print("Enter 0 to exit the program.")
mode = []
mylist = []
while True:
    my_input = input("Enter your command: ")
    if my_input == "0": break
    mode = my_input.split()
    if not mode: continue
    if(mode[0] == "append"): 
        mylist.append(mode[1])
    elif(mode[0] == "insert"): 
        mylist.insert(int(mode[1]), mode[2])
    elif(mode[0] == "remove"):
        if mode[1] in mylist:
            mylist.remove(mode[1])
        else:
            print("Not Found")
    elif(mode[0] == "pop"):
        if 0 <= int(mode[1]) and int(mode[1]) < len(mylist):
            mylist.pop(int(mode[1]))
        else:
            print("Not Found")
    elif(mode[0] == "len"): print(len(mylist))
    elif(mode[0] == "print"): print(mylist)
    elif(mode[0] == "clear"): mylist.clear()
    else: print("Invalid input")
            

