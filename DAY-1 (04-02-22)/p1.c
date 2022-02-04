#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10

typedef struct {
  int top;
  int arr[SIZE];
} Stack;

// Stack Operations
Stack *initS(void);
void push(Stack *, int);
int pop(Stack *);
int peek(Stack *);
void print(Stack *);
int isFull(Stack *);
int isEmpty(Stack *);
void destroy(Stack *);

// Program menu
void menu(void);

// flush any unnecessary input
void flush(FILE *);


int main(void)
{
  menu();
  Stack *s = initS();
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

        push(s, data);
        break;

      case 2:
        result = pop(s);

        if (result == -1) {
          printf("!!! STACK UNDERFLOW !!!\n");
          break;
        }

        printf("Popped data: %d\n", result);
        break;

      case 3:
        print(s);
        break;

      case 4:
        menu();
        break;

      case 5:
        result = peek(s);

        if (result == -1) {
          printf("!!! STACK UNDERFLOW !!!\n");
          break;
        }

        printf("Top data: %d\n", result);
        break;

      default:
        printf("Invalid Choice. Try again.\n");
        break;
    }

    flush(stdin);
    choice = -1;
  }

  destroy(s);
  return 0;
}


Stack *initS(void)
{
  Stack *s = malloc(sizeof(Stack));
  s->top = -1;
  return s;
}


void destroy(Stack *s)
{
  free(s);
}


void push(Stack *s, int data)
{
  if (isFull(s)) {
    printf("!!! STACK OVERFLOW !!!\n");
    return;
  }
  s->arr[++(s->top)] = data;
}


int pop(Stack *s)
{
  if (isEmpty(s))
    return -1;
  
  return s->arr[s->top--];
}


int peek(Stack *s)
{
  if (isEmpty(s))
    return -1;
  
  return s->arr[s->top];
}


void print(Stack *s)
{
  printf("Stack:\n");
  for (int i = s->top; i >= 0; i--)
    printf("%d\n", s->arr[i]);
}


int isFull(Stack *s)
{
  return s->top == SIZE - 1;
}


int isEmpty(Stack *s)
{
  return s->top == -1;
}


void menu(void)
{
  printf("\n\n*******************  STACK USING ARRAY  ********************\n");
  printf("************************************************************\n");
  printf("* <1> To PUSH data in the stack.                           *\n");
  printf("* <2> To POP data from the stack.                          *\n");
  printf("* <3> To DISPLAY data in the stack.                        *\n");
  printf("* <4> To display this MENU.                                *\n");
  printf("* <5> To PEEK the top element of the stack.                *\n");
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