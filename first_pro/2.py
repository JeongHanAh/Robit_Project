# 로봇의 배터리 로그를 기록하는 함수
# (주의: logs=[] 처럼 기본 인자로 가변 객체를 사용하면, 함수를 호출할 때마다 기존 리스트가 계속 유지되어 누적됩니다.)
def add_log(robot_name, battery, logs = []):
    """
    [자료형 변환 이유]
    문자열(str)과 숫자형(int)은 '+' 연산자로 직접 더할 수 없어 타입 에러가 발생합니다.
    따라서 문자열 조립을 위해 숫자형인 battery를 str(battery)로 변환해 줍니다.
    """
    log = robot_name + " battery: " + str(battery)
    
    # 기존 logs 리스트에 새 log가 담긴 리스트를 더해(연결해) 새로운 리스트를 반환합니다.
    # 인자로 넘어온 기본 리스트(logs) 자체가 계속 업데이트되므로 결과가 누적되는 효과가 있습니다.
    return logs + [log] 


# 함수를 호출하여 각 로봇의 로그를 출력합니다.
# 파이썬 특성상 logs 리스트가 공유되므로 호출할 때마다 이전 기록이 누적되어 출력됩니다.
print(add_log("frontbot", 80))  # 출력: ['frontbot battery: 80']
print(add_log("rearbot", 50))   # 출력: ['frontbot battery: 80', 'rearbot battery: 50']
print(add_log("armbot", 20))    # 출력: ['frontbot battery: 80', 'rearbot battery: 50', 'armbot battery: 20']

# [오류 발생 지점] 
# logs 변수는 add_log 함수 내부에서 선언된 '지역 변수'이므로 함수 외부에서는 접근할 수 없습니다.
# 이 줄을 실행하면 NameError가 발생합니다.
print(logs)