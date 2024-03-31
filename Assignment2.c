#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPRESSION_SIZE 100

// Stack implementation for postfix conversion
typedef struct {
    int top;
    char items[MAX_STACK_SIZE];
} Stack;

void push(Stack *s, char c) {
    if (s->top == MAX_STACK_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++s->top] = c;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top--];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(char *infix, char *postfix) {
    Stack operatorStack;
    operatorStack.top = -1;
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char token = infix[i];
        if (isdigit(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&operatorStack, token);
        } else if (token == ')') {
            while (operatorStack.top != -1 && operatorStack.items[operatorStack.top] != '(') {
                postfix[j++] = pop(&operatorStack);
            }
            pop(&operatorStack); // Discard the '('
        } else {
            while (operatorStack.top != -1 && precedence(token) <= precedence(operatorStack.items[operatorStack.top])) {
                postfix[j++] = pop(&operatorStack);
            }
            push(&operatorStack, token);
        }
        i++;
    }

    while (operatorStack.top != -1) {
        postfix[j++] = pop(&operatorStack);
    }

    postfix[j] = '\0'; // Null-terminate the postfix string
}

int main() {
    char infix[MAX_EXPRESSION_SIZE];
    char postfix[MAX_EXPRESSION_SIZE];
    printf("Enter an infix expression: ");
    fgets(infix, MAX_EXPRESSION_SIZE, stdin);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
