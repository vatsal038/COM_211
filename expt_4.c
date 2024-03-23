#include<stdio.h>
#include<string.h>
int top1 = -1, top2 = -1;
char operator[100];
int operand[100];
void process() {
    int x = operand[top1--];
    int y = operand[top1--];
    char op = operator[top2--];
    int z = 0;
    switch(op) {
        case '+':
            z = y + x;
            break;
        case '-':
            z = y - x;
            break;
        case '*':
            z = y * x;
            break;
        case '/':
            z = y / x;
            break;
    }
    operand[++top1] = z;
}
int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
int evaluateinfix(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if (ch >= '0' && ch <= '9') {
            operand[++top1] = ch - '0';
        } else if (ch == '+' || ch == '-' || ch == '/' || ch == '*') {
            if (top2 == -1) {
                operator[++top2] = ch;
            } else {
                while (top2 != -1 && precedence(ch) <= precedence(operator[top2])) {
                    process();
                }
                operator[++top2] = ch;
            }
        } else if (ch == '(') {
            operator[++top2] = ch;
        } else if (ch == ')') {
            while (operator[top2] != '(') {
                process();
            }
            top2--;
        }
    }
    while (top2 != -1) {
        process();
    }
    return operand[top1--];
}
int evaluatepostfix(char *str)
{
    int  i;
    for (i=0; str[i]!='\0';i++)
    {
        if(str[i]>='0' && str[i]<='9')
        {
            operand[++top1]=str[i]-'0';
        }
        else
        { 
            int x=operand[top1--];
            int y =operand[top1--];
            int z;
            switch(str[i])
            {
            case '+':
            z = y + x;
            break;
        case '-':
            z = y - x;
            break;
        case '*':
            z = y * x;
            break;
        case '/':
            z = y / x;
            break;
            }
            operand[++top1]=z;
        }
    }
    return operand[top1--];
}
int evaluateprefix(char *str)
{
    int  i;
    for (i=strlen(str)-1;i>=0;i--)
    {
        if(str[i]>='0' && str[i]<='9')
        {
            operand[++top1]=str[i]-'0';
        }
        else
        { 
            int x=operand[top1--];
            int y =operand[top1--];
            int z;
            switch(str[i])
            {
            case '+':
            z = y + x;
            break;
        case '-':
            z = y - x;
            break;
        case '*':
            z = y * x;
            break;
        case '/':
            z = y / x;
            break;
            }
            operand[++top1]=z;
        }
    }
    return operand[top1--];
}
int main() {
    char expression[100];
    int res;

    printf("Enter a prefix expression: ");
    scanf("%s", expression);
    res = evaluateprefix(expression);
    printf("The output of Prefix expression %s: %d\n", expression, res);

    printf("Enter an infix expression: ");
    scanf("%s", expression);
    res = evaluateinfix(expression);
    printf("The output of Infix expression %s: %d\n", expression, res);

    printf("Enter a postfix expression: ");
    scanf("%s", expression);
    res = evaluatepostfix(expression);
    printf("The output of Postfix expression %s: %d\n", expression, res);

    return 0;
}
