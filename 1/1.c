#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

typedef struct Stack {
	Node* top;
	int size;
} Stack;

int isEmpty(Stack* s) {
	if (s->size == 0) { //(*s).size랑 동일
		return 1;
	}
	return 0;
}

void push(Stack* s, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 노드 만들기
	newNode->data = data;
	newNode->next = s->top;
	s->top = newNode;
	s->size++;
}

void pop(Stack* s) {
	if (isEmpty(s) == 1) {
		printf("비어있음.");
		return;
	}

	Node* temp = s->top;
	int popdata = temp->data;
	
	s->top = s->top->next;
	free(temp);
	s->size--;

	printf("%d\n", popdata);
}

void size(Stack* s) {
	printf("%d\n", s->size);
}

int top(Stack* s) {
	if (isEmpty(s) == 1) { //예외처리
		return -1;
	} return s->top->data;
}

void printStack(Stack* s) {
	if (isEmpty(s) == 1) {
		printf("비어있음.\n");
		return;
	}
	Node* current = s->top;
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void main() {
	/*Stack s;
	s.top = NULL;
	s.size = 0;*/  //초기화가 되지 않았다고 인식돼 에러 뜸
	Stack s = { NULL, 0 };

	char command[20]; //명령어용 배열
	int data;
	printf("종료하려면 exit 입력.\n");

	while (1) {
		scanf("%s", command);

		if (strcmp(command, "push") == 0) {
			scanf("%d", &data);
			push(&s, data);
		}
		else if (strcmp(command, "pop") == 0) {
			pop(&s);
		}
		else if (strcmp(command, "size") == 0) {
			size(&s);
		}
		else if (strcmp(command, "top") == 0) {
			int topValue = top(&s);
			if (topValue == -1) {
				printf("비어있음.");
			}
			else printf("%d\n", topValue);
		}
		else if (strcmp(command, "isEmpty") == 0) {
			if (isEmpty(&s) == 1) {
				printf("true\n");
			}
			else printf("False\n");
		}
		else if (strcmp(command, "printStack") == 0) {
			printStack(&s);
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		else printf("잘못된 입력.");
	}


}

