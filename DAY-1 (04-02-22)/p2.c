#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10

typedef struct {
  int front;
  int rear;
  int arr[SIZE];
} Queue;

// Queue Operations
Queue *initQ(void);
void insert(Queue *, int);
int del(Queue *);
void print(Queue *);
int isFull(Queue *);
int isEmpty(Queue *);
void destroy(Queue *);

// Program menu
void menu(void);

// flush any unnecessary input
void flush(FILE *);


int main(void)
{
  menu();
  Queue *q = initQ();
  bool quit = false;

  int data, choice, result;
  while (!quit) {
    printf("\nChoice: ");
    scanf("%d", &choice);

    switch(choice) {
      case 0:
        quit = true;
        break;

      case 1:
        printf("Data: ");
        scanf("%d", &data);

        insert(q, data);
        break;

      case 2:
        result = del(q);

        if (result == -1) {
          printf("!!! QUEUE UNDERFLOW !!!\n");
          break;
        }

        printf("Dequeued data: %d\n", result);
        break;

      case 3:
        print(q);
        break;

      case 4:
        menu();
        break;

      default:
        printf("Invalid Choice. Try again.\n");
        break;
    }

    flush(stdin);
    choice = -1;
  }

  destroy(q);
  return 0;
}


Queue *initQ(void)
{
  Queue *q = malloc(sizeof(Queue));
  q->front = -1;
  q->rear = -1;
  return q;
}


void destroy(Queue *q)
{
  free(q);
}


void insert(Queue *q, int data)
{
  if (isFull(q)) {
    printf("!!! QUEUE OVERFLOW !!!\n");
    return;
  }

  if (q->front == -1)
    q->front = 0;

  q->arr[++q->rear] = data;
}


int del(Queue *q)
{
  if (isEmpty(q))
    return -1;

  int item = q->arr[q->front++];
  if (q->front > q->rear) {
    q->front = -1;
    q->rear = -1;
  }
  return item;
}


int isFull(Queue *q)
{
  return q->rear + 1 == SIZE;
}


int isEmpty(Queue *q)
{
  return q->front == -1;
}


void print(Queue *q)
{
  printf("Queue: ");

  for (int i = q->front; i <= q->rear; ++i)
    printf("%d ", q->arr[i]);

  printf("\n");
}


void menu(void)
{
  printf("\n\n*******************  QUEUE USING ARRAY ********************\n");
  printf("************************************************************\n");
  printf("* <1> To ENQUEUE data in the queue.                        *\n");
  printf("* <2> To DEQUEUE data from the queue.                      *\n");
  printf("* <3> To DISPLAY data in the queue.                        *\n");
  printf("* <4> To display this MENU.                                *\n");\
  printf("* <0> To EXIT!                                             *\n");
  printf("************************************************************\n\n");
}


void flush(FILE *in)
{
  int ch;
  clearerr(in);
  do ch = getc(in);
  while (ch != '\n' && ch != EOF);
  clearerr(in);
}