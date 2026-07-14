# 로봇들의 상태 데이터(이름, 배터리 잔량, 현재 좌표, 장애물과의 거리)를 담은 딕셔너리 리스트
robot_status = [
    {"name": "mobilebot", "battery": 82, "position": (1.2, 0.5), "distance": 0.8},
    {"name": "drone", "battery": 18, "position": (0.3, 1.5), "distance": 0.4},
    {"name": "manipulator", "battery": 45, "position": (2.0, 1.0), "distance": 1.2},
]

# 리스트에 있는 개별 로봇의 데이터를 하나씩 가져와서 반복문 실행
for i in robot_status:
    # 딕셔너리에서 각 항목의 키(Key)에 해당하는 값을 변수에 할당
    name = i["name"]
    battery = i["battery"]
    position = i["position"]
    distance = i["distance"]

    # 로봇 이름을 리스트 형태('[이름]')로 출력
    print([name])
    
    # [배터리 상태 분류]
    if battery >= 60:
        battery_Amount = "배터리 충분"                # 60% 이상일 때
    elif battery >= 20 and battery <= 60:
        battery_Amount = "배터리 주의"                # 20% 이상 ~ 60% 이하일 때 (※ 참고: 60은 위에서 걸러지므로 battery >= 20만 써도 무방합니다)
    else:
        battery_Amount = "충전 필요"                # 20% 미만일 때
        
    print(f"배터리 {battery_Amount}")               # 분류된 배터리 상태 출력
    print(f"위치: x={position[0]}, y={position[1]}") # 튜플로 저장된 x, y 좌표를 각각 인덱싱하여 출력

    # [주행 가능 여부 분류]
    if distance < 0.5:
        state = "장애물 감지"  # 거리가 0.5 미만으로 가까우면 위험
    elif distance >= 0.5:
        state = "전진 가능"   # 거리가 0.5 이상으로 여유 있으면 안전
        
    print(f"상태: {state}\n") # 로봇 상태 출력 및 줄바꿈(\n)으로 가독성 확보