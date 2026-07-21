#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data; //data 자료형 int로 설정
	struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
} //노드 만드는 함수

void insert_first(Node** head, int data) {
    Node* new_node = create_node(data);
    new_node->next = *head; //next 연결
    *head = new_node; //head를 새 노드로 변경
}

void insert_back(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    } //리스트가 비어있을 땐 insert_frst처럼
    Node* curr = *head;
    while (curr->next != NULL) { //맨 끝 노드로 이동
        curr = curr->next;
    }
    curr->next = new_node; //끝 노드 뒤에 새 노드 연결
}

void insert_by_index(Node** head, int idx, int data) { //원하는 인덱스 위치에 추가
    if (idx == 0) {
        insert_first(head, data); //idx가 0이면 그냥 처음에 넣는 것처럼
        return;
    }
    Node* curr = *head;
    for (int i = 0; i < idx - 1 && curr != NULL; i++) {
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("인덱스 범위를 벗어남.\n");
        return;
    }
    Node* new_node = create_node(data);
    new_node->next = curr->next;
    curr->next = new_node;
}

//특정 데이터를 가진 노드 바로 뒤에 추가

void insert_by_data(Node** head, int target_data, int data) {
    Node* curr = *head;
    while (curr != NULL && curr->data != target_data) {
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("%d 데이터를 찾을 수 없음.", target_data);
        return;
    }
    Node* new_node = create_node(data);
    new_node->next = curr->next;
    curr->next = new_node;
}

//맨 처음 노드 삭제
void delete_first(Node** head) {
    if (*head == NULL) return;
    Node* temp = *head; //지울 노드 임시 보관
    *head = (*head)->next; //다음 노드로 머리를 옮김
    free(temp);
}

//맨 마지막 노드 삭제
void delete_back(Node** head) {
    if (*head == NULL) return; //없으면 삭제 못 함
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    } //노드가 1개인 경우
    Node* curr = *head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }
    free(curr->next); //마지막 노드 해제
    curr->next = NULL; //새로운 마지막 노드 표시
}

//원하는 인덱스 노드 삭제
void delete_by_index(Node** head, int idx) {
    if (*head == NULL) return;
    if (idx == 0) {
        delete_first(head);
        return;
    }
    Node* curr = *head;
    for (int i = 0; i < idx - 1 && curr->next != NULL; i++) {
        curr = curr->next;
    }
    if (curr->next == NULL) {
        printf("삭제할 인덱스가 존재하지 않음.");
        return;
    }
    Node* temp = curr->next;
    curr->next = temp->next;
    free(temp);
}

//특정 데이터를 가진 노드 삭제
void delete_by_data(Node** head, int target_data) {
    if (*head == NULL) return;
    if ((*head)->data == target_data) {
        delete_first(head);
        return;
    }
    Node* curr = *head;
    while (curr->next != NULL && curr->next->data != target_data) {
        curr = curr->next;
    }
    if (curr->next == NULL) {
        printf("%d 데이터가 없어 삭제할 수 없음.", target_data);
        return;
    }
    Node* temp = curr->next;
    curr->next = temp->next;
    free(temp);
}

//요소를 데이터로 찾아 인덱스 반환
int get_entry_by_data(Node* head, int target_data) {
    int idx = 0;
    Node* curr = head;
    while (curr != NULL) {
        if (curr->data == target_data) return idx;
        curr = curr->next;
        idx++;
    }
    return -1; // 못 찾으면 -1 반환
}

//인덱스로 찾아 데이터 반환
int get_entry_by_index(Node* head, int index) {
    Node* curr = head;
    for (int i = 0; i < index && curr != NULL; i++) {
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("인덱스 범위를 벗어남.\n");
        return -9999;
    }
    return curr->data;
}

//리스트 전체 길이 반환
int get_length(Node* head) {
    int count = 0;
    Node* curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

//리스트 모든 요소 출력
void print_list(Node* head) {
    Node* curr = head;
    printf("List: ");
    while (curr != NULL) {
        printf("[%d] -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

//역순
void reverse(Node** head) {
    Node* prev = NULL;
    Node* curr = *head;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next; //다음 위치 미리 저장
        curr->next = prev; //화살표 방향을 이전 노드로 바꿈
        prev = curr; //prev가 현재 노드
        curr = next; //curr이 다음 노드
    }
    *head = prev; //머리를 맨 끝이었던 노드로 변경
}

void main() {
    Node* head = NULL;
    char cmd[50];
    int val1, val2;

    printf("=== 연결 리스트 테스트 프로그램 ===\n");
    printf("사용 예시:\n");
    printf(" - insert_first 10\n");
    printf(" - insert_by_index 1 20\n");
    printf(" - print_list\n");
    printf(" - reverse\n");
    printf(" - exit (종료)\n");
    printf("===================================\n");

    while (1) {
        printf("\n명령어와 원하는 값을 입력하십시오: ");
        scanf("%s", cmd);

        //insert 명령어 처리
        if (strcmp(cmd, "insert_first") == 0) {
            scanf("%d", &val1);
            insert_first(&head, val1);
            print_list(head);
        }
        else if (strcmp(cmd, "insert_back") == 0) {
            scanf("%d", &val1);
            insert_back(&head, val1);
            print_list(head);
        }
        else if (strcmp(cmd, "insert_by_index") == 0) {
            scanf("%d %d", &val1, &val2);
            insert_by_index(&head, val1, val2);
            print_list(head);
        }
        else if (strcmp(cmd, "insert_by_data") == 0) {
            scanf("%d %d", &val1, &val2);
            insert_by_data(&head, val1, val2);
            print_list(head);
        }

        // delete 명령어 처리
        else if (strcmp(cmd, "delete_first") == 0) {
            delete_first(&head);
            print_list(head);
        }
        else if (strcmp(cmd, "delete_back") == 0) {
            delete_back(&head);
            print_list(head);
        }
        else if (strcmp(cmd, "delete_by_index") == 0) {
            scanf("%d", &val1);
            delete_by_index(&head, val1);
            print_list(head);
        }
        else if (strcmp(cmd, "delete_by_data") == 0) {
            scanf("%d", &val1);
            delete_by_data(&head, val1);
            print_list(head);
        }

        // 탐색, 기타 명령어 처리
        else if (strcmp(cmd, "get_entry_by_data") == 0) {
            scanf("%d", &val1);
            int idx = get_entry_by_data(head, val1);
            if (idx != -1) printf("=> %d 데이터의 인덱스는 %d입니다.\n", val1, idx);
            else printf("=> 리스트에 %d 데이터가 없습니다.\n", val1);
        }
        else if (strcmp(cmd, "get_entry_by_index") == 0) {
            scanf("%d", &val1);
            int data = get_entry_by_index(head, val1);
            if (data != -9999) printf("=> 인덱스 %d의 데이터는 %d입니다.\n", val1, data);
        }
        else if (strcmp(cmd, "get_length") == 0) {
            printf("=> 리스트의 전체 길이는 %d입니다.\n", get_length(head));
        }
        else if (strcmp(cmd, "print_list") == 0) {
            print_list(head);
        }
        else if (strcmp(cmd, "reverse") == 0) {
            reverse(&head);
            print_list(head);
        }

        //종료
        else if (strcmp(cmd, "exit") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("알 수 없는 명령어입니다. 다시 입력해주세요.\n");
            // 무한루프 방지
            while (getchar() != '\n');
        }
    }

    // 메모리 누수 방지(전체 삭제)
    while (head != NULL) {
        delete_first(&head);
    }
}
