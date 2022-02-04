#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10

typedef struct {
  int top;
  int arr[SIZE];
} Stack;

typedef struct {
  Stack s1;
  Stack s2;
} Queue;

// Stack Operations
void push(Stack *, int);
int pop(Stack *);

// Queue Operations
Queue *initQ(void);
void peek(Queue *);
int enqueue(Queue *, int);
int dequeue(Queue *);
void display(Queue *);
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

        if (enqueue(q, data) == -1)
          printf("!!! QUEUE OVERFLOW !!!\n");

        break;

      case 2:
        result = dequeue(q);

        if (result == -1) {
          printf("!!! QUEUE UNDERFLOW !!!\n");
          break;
        }

        printf("Dequeued data: %d\n", result);
        break;

      case 3:
        display(q);
        break;

      case 4:
        menu();
        break;

      case 5:
        peek(q);
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


void push(Stack *s, int data)
{
  s->arr[++(s->top)] = data;
}


int pop(Stack *s)
{
  return s->arr[s->top--];
}


Queue *initQ(void)
{
  Queue *q = malloc(sizeof(Queue));
  q->s1.top = -1;
  q->s2.top = -1;
  return q;
}


void peek(Queue *q)
{
  printf("Front: ");

  if (q->s1.top > -1) {
    int top = q->s1.top; 
    printf("%d\n", q->s1.arr[top]);
  }
}


int enqueue(Queue *q, int data)
{
  if (q->s1.top + 1 >= SIZE)
    return -1;

  while (q->s1.top > -1)
    push(&q->s2, pop(&q->s1));

  push(&q->s1, data);

  while (q->s2.top > -1)
    push(&q->s1, pop(&q->s2));

  return 0;
}


int dequeue(Queue *q)
{
  if (q->s1.top > -1)
    return pop(&q->s1);

  return -1;
}


void display(Queue *q)
{
  printf("Queue: ");

  for (int i = q->s1.top; i >= 0; --i)
    printf("%d ", q->s1.arr[i]);

  printf("\n");
}


void destroy(Queue *q)
{
  free(q);
}


void menu(void)
{
  printf("\n\n*******************  QUEUE USING STACK *********************\n");
  printf("************************************************************\n");
  printf("* <1> To ENQUEUE data in the queue.                        *\n");
  printf("* <2> To DEQUEUE data from the queue.                      *\n");
  printf("* <3> To DISPLAY data in the queue.                        *\n");
  printf("* <4> To display this MENU.                                *\n");
  printf("* <5> To PEEK the queue.                                   *\n");
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