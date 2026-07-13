def add_log(robot_name, battery, logs = []):
    """
    log = robot_name + " battery: " + battery에서 battery는 산술연산자로 처리되므로 오류가 일어난다.
    따라서 log는 str 형태로 나타낼 예정이므로 battery 자료형을 바꿔준다.
    """
    log = robot_name + " battery: " + str(battery)
    #append는 기존에 있던 logs 리스트에 덧붙이듯 값을 추가하는 것이므로 한 가지 값만 되돌리고 싶을 때 권장되지 않음.
    #따라서 새 리스트를 만들어 리턴하는 방식으로 log를 누적하면서 정상적으로 출력되도록 함. 
    return logs + [log] 


print(add_log("frontbot", 80))
print(add_log("rearbot", 50))
print(add_log("armbot", 20))
