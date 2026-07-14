import pygame
import sys
import math

# 1. 초기화 및 화면 설정
pygame.init()
WIDTH, HEIGHT = 1000, 750
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("3D 직선형 스케치툴")

# 색상 정의
BG_COLOR = (24, 28, 36)
NODE_COLOR = (80, 95, 120)
HOVER_COLOR = (255, 170, 0)
SELECT_COLOR = (0, 255, 120)
LINK_COLOR = (200, 210, 230)
LINK_HOVER_COLOR = (255, 100, 100) 
GRID_LINE_COLOR = (40, 48, 60)

BTN_COLOR_ACTIVE = (0, 255, 120)
BTN_COLOR_INACTIVE = (60, 70, 85)
BTN_TEXT_ACTIVE = (24, 28, 36)
BTN_TEXT_INACTIVE = (200, 210, 220)

font = pygame.font.SysFont('Arial', 16, bold=True)
label_font = pygame.font.SysFont('Arial', 14, bold=True) 

btn_05 = pygame.Rect(20, 20, 50, 30)
btn_10 = pygame.Rect(80, 20, 50, 30)
btn_20 = pygame.Rect(140, 20, 50, 30)

nodes = []
links = []
start_node_3d = None  
camera_yaw = 30
camera_pitch = -30
camera_distance = 10.0
current_density = 1.0

def generate_nodes(density):
    new_nodes = []
    spacing = 1.0 / density
    x_steps = int(4 * density) + 1
    y_steps = int(3 * density) + 1
    z_steps = int(4 * density) + 1
    
    for i in range(x_steps):
        x = -2 + i * spacing
        for j in range(y_steps):
            y = -1 + j * spacing
            for k in range(z_steps):
                z = -2 + k * spacing
                new_nodes.append((x * 1.5, y * 1.5, z * 1.5))
    return new_nodes

def set_density(density):
    global current_density, nodes, start_node_3d
    current_density = density
    nodes = generate_nodes(density)
    start_node_3d = None 

set_density(1.0)

def project_3d_to_2d(x, y, z):
    rad_yaw = math.radians(camera_yaw)
    cos_y, sin_y = math.cos(rad_yaw), math.sin(rad_yaw)
    x1 = x * cos_y - z * sin_y
    z1 = x * sin_y + z * cos_y

    rad_pitch = math.radians(camera_pitch)
    cos_x, sin_x = math.cos(rad_pitch), math.sin(rad_pitch)
    y2 = y * cos_x - z1 * sin_x
    z2 = y * sin_x + z1 * cos_x

    z_depth = z2 + camera_distance
    if z_depth <= 0.1: z_depth = 0.1

    scale = 400
    proj_x = int(WIDTH / 2 + (x1 * scale) / z_depth)
    proj_y = int(HEIGHT / 2 - (y2 * scale) / z_depth)
    return proj_x, proj_y, z_depth

def get_distance_to_segment(px, py, x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1
    if dx == 0 and dy == 0:
        return math.hypot(px - x1, py - y1)
    
    t = ((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy)
    t = max(0.0, min(1.0, t))
    closest_x = x1 + t * dx
    closest_y = y1 + t * dy
    return math.hypot(px - closest_x, py - closest_y)

def main():
    global camera_yaw, camera_pitch, camera_distance, start_node_3d
    clock = pygame.time.Clock()

    while True:
        mouse_pos = pygame.mouse.get_pos()
        
        # 1. 점(Node) 스냅 연산
        projected_nodes = []
        hovered_node_3d = None
        min_node_dist = 15
        
        for n in nodes:
            px, py, depth = project_3d_to_2d(n[0], n[1], n[2])
            projected_nodes.append((px, py, depth, n))
            
            if depth > 1.5:
                dist = math.hypot(mouse_pos[0] - px, mouse_pos[1] - py)
                if dist < min_node_dist:
                    min_node_dist = dist
                    hovered_node_3d = n

        # 2. 선(Link) 스냅 연산
        projected_links = []
        hovered_link = None
        min_link_dist = 12 # 선 인식 범위가 생각보다 넓어야함
        
        for link in links:
            p1_3d, p2_3d = link
            px1, py1, d1 = project_3d_to_2d(p1_3d[0], p1_3d[1], p1_3d[2])
            px2, py2, d2 = project_3d_to_2d(p2_3d[0], p2_3d[1], p2_3d[2])
            avg_depth = (d1 + d2) / 2.0
            projected_links.append((px1, py1, px2, py2, avg_depth, link))
            
            if d1 > 1.5 and d2 > 1.5:
                dist = get_distance_to_segment(mouse_pos[0], mouse_pos[1], px1, py1, px2, py2)
                if dist < min_link_dist:
                    min_link_dist = dist
                    hovered_link = link

        # 3. 마우스 및 키보드 이벤트 처리
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            # 마우스 클릭 이벤트
            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 4: camera_distance = max(4.0, camera_distance - 0.5)
                elif event.button == 5: camera_distance = min(20.0, camera_distance + 0.5)

                # 좌클릭 (점 연결 / 버튼 클릭)
                elif event.button == 1:
                    ui_clicked = False
                    for btn, val in [(btn_05, 0.5), (btn_10, 1.0), (btn_20, 2.0)]:
                        if btn.collidepoint(event.pos):
                            set_density(val)
                            ui_clicked = True
                            break
                    
                    if not ui_clicked:
                        if hovered_node_3d is not None:
                            if start_node_3d is None:
                                start_node_3d = hovered_node_3d
                            else:
                                if start_node_3d != hovered_node_3d:
                                    pair = tuple(sorted((start_node_3d, hovered_node_3d)))
                                    if pair not in links:
                                        links.append(pair)
                                start_node_3d = None
                        else:
                            start_node_3d = None

                # 우클릭 (선 삭제)
                elif event.button == 3:
                    if hovered_link is not None:
                        links.remove(hovered_link)
                    elif start_node_3d is not None:
                        start_node_3d = None # 선 그리기 취소

            # 키보드 이벤트 처리
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_DELETE:
                    if hovered_link is not None:
                        links.remove(hovered_link)
                        
                elif event.key == pygame.K_BACKSPACE:
                    if start_node_3d is not None: start_node_3d = None
                    elif links: links.pop() # ctrl + z 느낌

        # 4. 카메라 이동 처리 (WASD / 방향키)
        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT] or keys[pygame.K_a]: camera_yaw += 2.0
        if keys[pygame.K_RIGHT] or keys[pygame.K_d]: camera_yaw -= 2.0
        if keys[pygame.K_UP] or keys[pygame.K_w]: camera_pitch -= 1.5
        if keys[pygame.K_DOWN] or keys[pygame.K_s]: camera_pitch += 1.5
        camera_pitch = max(-85, min(85, camera_pitch))

        # 5. 화면 렌더링
        screen.fill(BG_COLOR)

        for i in range(-5, 6):
            p1_x, p1_y, _ = project_3d_to_2d(i, -1.5, -5)
            p2_x, p2_y, _ = project_3d_to_2d(i, -1.5, 5)
            pygame.draw.line(screen, GRID_LINE_COLOR, (p1_x, p1_y), (p2_x, p2_y), 1)
            p3_x, p3_y, _ = project_3d_to_2d(-5, -1.5, i)
            p4_x, p4_y, _ = project_3d_to_2d(5, -1.5, i)
            pygame.draw.line(screen, GRID_LINE_COLOR, (p3_x, p3_y), (p4_x, p4_y), 1)

        if start_node_3d is not None:
            sp_x, sp_y, _ = project_3d_to_2d(*start_node_3d)
            if hovered_node_3d is not None:
                hp_x, hp_y, _ = project_3d_to_2d(*hovered_node_3d)
                pygame.draw.line(screen, SELECT_COLOR, (sp_x, sp_y), (hp_x, hp_y), 3)
            else:
                pygame.draw.line(screen, (100, 150, 120), (sp_x, sp_y), mouse_pos, 2)

        draw_queue = []
        for px, py, depth, n in projected_nodes:
            draw_queue.append(('node', depth, n, px, py))
        for px1, py1, px2, py2, depth, link in projected_links:
            draw_queue.append(('link', depth, link, px1, py1, px2, py2))

        draw_queue.sort(key=lambda item: item[1], reverse=True)

        for item in draw_queue:
            if item[0] == 'node':
                _, depth, n, px, py = item
                radius = max(2, int(15 / depth))
                
                if n == start_node_3d:
                    pygame.draw.circle(screen, SELECT_COLOR, (px, py), radius + 2)
                elif n == hovered_node_3d:
                    pulse_radius = radius + 3 + int(math.sin(pygame.time.get_ticks() * 0.015) * 2)
                    pygame.draw.circle(screen, HOVER_COLOR, (px, py), pulse_radius, 2)
                    pygame.draw.circle(screen, HOVER_COLOR, (px, py), radius)
                else:
                    pygame.draw.circle(screen, NODE_COLOR, (px, py), radius)

            elif item[0] == 'link':
                _, depth, link_obj, px1, py1, px2, py2 = item
                thickness = max(1, int(18 / depth))
                
                if link_obj == hovered_link:
                    # 마우스 오버 시 빨간색 표시
                    pygame.draw.line(screen, LINK_HOVER_COLOR, (px1, py1), (px2, py2), thickness + 2)
                else:
                    pygame.draw.line(screen, LINK_COLOR, (px1, py1), (px2, py2), thickness)

        # 6. UI 버튼 렌더링
        for btn, label, val in [(btn_05, "0.5X", 0.5), (btn_10, "1.0X", 1.0), (btn_20, "2.0X", 2.0)]:
            is_active = (current_density == val)
            bg_color = BTN_COLOR_ACTIVE if is_active else BTN_COLOR_INACTIVE
            text_color = BTN_TEXT_ACTIVE if is_active else BTN_TEXT_INACTIVE
            pygame.draw.rect(screen, bg_color, btn, border_radius=5)
            text_surf = font.render(label, True, text_color)
            text_rect = text_surf.get_rect(center=btn.center)
            screen.blit(text_surf, text_rect)

        # 7. 치수(길이) 툴팁
        if hovered_link is not None:
            p1_3d, p2_3d = hovered_link
            real_distance = math.dist(p1_3d, p2_3d) / 1.5
            
            text_str = f"L: {real_distance:.2f} (R-Click or DEL to Delete)"
            text_surf = label_font.render(text_str, True, (255, 255, 255))
            text_rect = text_surf.get_rect(topleft=(mouse_pos[0] + 18, mouse_pos[1] + 18))
            bg_rect = text_rect.inflate(12, 8)
            
            pygame.draw.rect(screen, (30, 35, 45), bg_rect, border_radius=4)
            pygame.draw.rect(screen, (255, 100, 100), bg_rect, 1, border_radius=4)
            screen.blit(text_surf, text_rect)

        pygame.display.flip()
        clock.tick(60)

if __name__ == "__main__":
    main()