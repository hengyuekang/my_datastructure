#include "stdafx.h"
// the numbers of operator
#define N_OPTR 7
// char to number
#define charonnum(x) (x - '0')
// + - * / () \0
typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV,
    L_P,
    R_P,
    EOE
} Operator;
// priority[top][curr]
const char pri[N_OPTR][N_OPTR] = {
    /*              curr             */
    /*           +     -     *    /   (    )   \0     */
    /*      + */ '>', '>', '<', '<', '<', '>', '>',
    /*      - */ '>', '>', '<', '<', '<', '>', '>',
    /*   t  * */ '>', '>', '>', '>', '<', '>', '>',
    /*   o  / */ '>', '>', '>', '>', '<', '>', '>',
    /*   p  ( */ '<', '<', '<', '<', '<', '=', ' ',
    /*      ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /*      \0*/ '<', '<', '<', '<', '<', ' ', '='};
double evaluate(char *E);
// store numbers in expression
void readNumber(char *&S, Stack<double> &ope);
// priority
char orderBetween(char &opttop, char curr);
// binary operation
double calcu(double &opend1, char &ope, double &opend2);
int main()
{
    double res = 0.0;
    std::cout << "input the expression: " << std::endl;
    char *expre = new char[1024];
    // to RPN
    std::cin >> expre;
    res = evaluate(expre);
    delete[] expre;
    std::cout << "result is: " << res << std::endl;
    system("pause");
    return 0;
}
double evaluate(char *E)
{
    // opend:numbers operator:optr
    Stack<double> opend;
    Stack<char> optr;
    // end caculate
    optr.push('\0');
    // scan left to right
    while (!optr.empty())
    {
        if (isdigit(*E))
        {
            readNumber(E, opend);
        }
        else
        {
            // Compare priority
            switch (orderBetween(optr.top(), *E))
            {
            case '<':
                // put off caculation
                optr.push(*E);
                E++;
                break;
            case '=':
                optr.pop();
                E++;
                break;
            case '>':
            {
                // caculate part of expression
                char op = optr.pop();
                double num2 = opend.pop();
                double num1 = opend.pop();
                opend.push(calcu(num1, op, num2));
                break;
            }
                // error
            default:
                throw(0);
            }
        }
    }
    return opend.pop();
}
void readNumber(char *&S, Stack<double> &ope)
{
    Stack<int> resolver;
    // get complete number
    while (isdigit(*S))
    {
        resolver.push((double)charonnum(*S));
        S++;
    }
    int cnt = 1;
    int res = 0;
    // substr to number
    while (!resolver.empty())
    {
        res += resolver.pop() * cnt;
        cnt *= 10;
    }
    ope.push(res);
}
char orderBetween(char &opttop, char curr)
{
    // char to index of pri
    int row = 0, col = 0;
    switch (opttop)
    {
    case '+':
        row = ADD;
        break;
    case '-':
        row = SUB;
        break;
    case '*':
        row = MUL;
        break;
    case '/':
        row = DIV;
        break;
    case '(':
        row = L_P;
        break;
    case ')':
        row = R_P;
        break;
    default:
        row = EOE;
        break;
    }
    switch (curr)
    {
    case '+':
        col = ADD;
        break;
    case '-':
        col = SUB;
        break;
    case '*':
        col = MUL;
        break;
    case '/':
        col = DIV;
        break;
    case '(':
        col = L_P;
        break;
    case ')':
        col = R_P;
        break;
    default:
        col = EOE;
        break;
    }
    return pri[row][col];
}
double calcu(double &opend1, char &ope, double &opend2)
{
    double res = 0.0;
    switch (ope)
    {
    case '+':
        res = opend1 + opend2;
        break;
    case '-':
        res = opend1 - opend2;
        break;
    case '*':
        res = opend1 * opend2;
        break;
    case '/':
        res = opend1 / opend2;
        break;
    default:
        break;
    }
    return res;
}