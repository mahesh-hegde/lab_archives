#include<stdio.h>
#include<stdlib.h>
#define MAX 20

typedef struct op_stack {
    int top;
    char ops[MAX];
} op_stack;

void push(op_stack *s, char op) {
    if(s->top == MAX) return;
    s->ops[s->top++] = op;
}

char pop(op_stack *s) {
    if (s->top == 0) return '?';
    s->top--;
    return s->ops[s->top];
}

char peek(op_stack *s) {
    if (s->top == 0) return '?';
    return s->ops[s->top - 1];
}

int is_op (char op) {
    return (op == '+' || op == '-' || op == '*' ||
        op == '/' || op == '^');
}


int preced (char ch) {
    switch(ch) {
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    case '^': return 3;
    default: return 0;
    }
}

int main() {
    char input[32];
    op_stack stack;

    char *string;
    stack.top = 0;
    printf("enter infix expression: ");
    scanf("%30[^\n]", input);
    input[30] = (char)0;
    for(string = input; *string; string++) {
        char ch = *string;

        if (ch == ' ') {
            string ++;
            continue;
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while(peek(&stack) != '(') {
                printf(" %c", pop(&stack));
            }
            pop(&stack);
        } else if (is_op(ch)) {
            // if stack is empty or has left bracket, we get lower precedence anyway
            // see implementation of preced()
            while((preced(peek(&stack)) > preced(ch))
					|| (ch != '^' && preced(peek(&stack)) >= preced(ch))) {
                printf(" %c", pop(&stack));
            }

            // ensure a space occurs between any two operands in output
            putchar(' ');
            push(&stack, ch);
        } else {
            // For simplicity, We ignore spaces while parsing
            // and manually print them between operands
            putchar(ch);
        }
        string ++;
    }

    while(stack.top != 0) {
        printf(" %c", pop(&stack));
    }

    printf("\n");
    return 0;
}

