#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Node {
	int data;
	struct _Node* next;
}Node;

typedef struct Queue {	
	Node* rear; //나가는 곳
	Node* front; //들어오는 곳
	int size;
} Queue;

int isEmpty(Queue* q) {
	if (q->size == 0) { 
		return 1;
	}
	return 0;
}

void Enqueue(Queue* q, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 노드
	newNode->data = data;
	newNode->next = NULL;
	
	if (isEmpty(q) == 1) {
		q->front = newNode;
		q->rear = newNode;
	}
	else {
		q->rear->next = newNode;
		q->rear = newNode;
	}
	q->size++;
}

void Dequeue(Queue* q) {
	if (isEmpty(q) == 1) {
		printf("비어있음.\n");
		return;
	}

	Node* temp = q->front;
	int dequeuedata = temp->data;

	q->front = q->front->next;
	free(temp);
	q->size--;

	if (isEmpty(q) == 1) {
		q->rear = NULL;
	}

	printf("%d\n", dequeuedata);
}

void size(Queue* q) {
	printf("%d\n", q->size);
}

int front(Queue* q) {
	if (isEmpty(q) == 1) {
		return -1;
	} return q->front->data;
}

int rear(Queue* q) {
	if (isEmpty(q) == 1) { //예외처리
		return -1;
	} return q->rear->data;
}

void printQueue(Queue* q) {
	if (isEmpty(q) == 1) {
		printf("비어있음.\n");
		return;
	}
	Node* current = q->front;
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void main() {
	Queue q = { NULL, 0 };

	char command[20]; //명령어용 배열
	int data;
	printf("종료하려면 exit 입력.\n");

	while (1) {
		scanf("%s", command);

		if (strcmp(command, "Enqueue") == 0) {
			scanf("%d", &data);
			Enqueue(&q, data);
		}
		else if (strcmp(command, "Dequeue") == 0) {
			Dequeue(&q);
		}
		else if (strcmp(command, "size") == 0) {
			size(&q);
		}
		else if (strcmp(command, "front") == 0) {
			int topValue = front(&q);
			if (topValue == -1) {
				printf("비어있음.");
			}
			else printf("%d\n", topValue);
		}
		else if (strcmp(command, "rear") == 0) {
			int value = rear(&q);
			if (value == -1) {
				printf("비어있음.");
			}
			else printf("%d\n", value);
		}
		else if (strcmp(command, "isEmpty") == 0) {
			if (isEmpty(&q) == 1) {
				printf("true\n");
			}
			else printf("False\n");
		}
		else if (strcmp(command, "printQueue") == 0) {
			printQueue(&q);
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
		else printf("잘못된 입력.");
	}
}
