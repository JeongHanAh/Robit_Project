robot_status = [
    {"name": "mobilebot", "battery": 82, "position":(1.2, 0.5), "distance": 0.8},
    {"name": "drone", "battery": 18, "position":(0.3, 1.5), "distance": 0.4},
    {"name": "manipulator", "battery": 45, "position":(2.0, 1.0), "distance": 1.2},
]

for i in robot_status:
    name = i["name"]
    battery = i["battery"]
    position = i["position"]
    distance = i["distance"]

    print([name])
    if battery >= 60:
        battery_Amount = "배터리 충분"
    elif battery >= 20 and battery <= 60:
        battery_Amount = "배터리 주의"
    else:
        battery_Amount = "충전 필요"
    print(f"배터리 {battery_Amount}")
    print(f"위치: x={position[0]}, y={position[1]}")
    if distance < 0.5:
        state = "장애물 감지"
    elif distance >= 0.5:
        state = "전진 가능"
    print(f"상태: {state}\n")