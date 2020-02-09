// This program implements a simple calculator to evaluate a simple arithmetic expression.
// Author: Bazillah Zargar

#include <stdio.h>
#include <stdlib.h>

// Functions
float s_exp(void);
float m_exp(float sub_exp, char op);
char get_op();
float get_num();

// Input: none, the s_expressin will be read in from stdin
// Effect: the s_expression is evaluated using 
//          a while loop or a do while loop: 
//          repeatedly get num with m_exp() and then get op with 
//          get_op() while op is '+' or '-'; when op is '\n', exit loop.
// Output: this function returns the value of the s_expression.
float s_exp(void){
    float num;
    char op;
    num = m_exp(1, '*');
    op = get_op();
    
    // while the operator is not a new line character
    while (op != '\n'){
        // if op is '+' perform addition operation
        if (op == '+'){
            num = num + m_exp(1, '*');
            op = get_op();
        }
        // if op is '-' perform subtraction operation
        else if (op == '-'){
            num = num - m_exp(1, '*');
            op = get_op();
        }
        else {
            return 0;
        }
    }
    return num;

}

// Input:'sub_exp': the value of the current sub m_expression 
//                  to the left of 'op' location in stdin.
//          'op': an operator, '*' or '/'. 'op' could also be 
//                  '+', '-', or '\n' indicating the end of the m_expression. 
//                  '+', '-' or '\n\ should be pushed back to stdin.
//          the rest of the m_expression will be read in from stdin.
// Effect: the m_expression is evaluated using recursion:
//          get next_num with get_num() and then get next_op with get_op()
//          use 'sub_exp op next_num' and 'next_op' to do recursive call
// Output: this function returns the value of the current m_expression.
float m_exp(float sub_exp, char op){
    // if operator is new line character
    if (op == '\n'){
        ungetc('\n', stdin);
        return sub_exp;
    }
    // if operator is '+'
    else if (op == '+'){
        ungetc('+', stdin);
        return sub_exp;
    }

    // If operator is '-'
    else if (op == '-'){
        ungetc('-', stdin);
        return sub_exp;
    }
    // If operator is '*' or '/' then perform the multiplication or division operation followed by a new recursive call.
    else{
        float next_num;
        float next_op;
        float next_sub_exp;
        if (op == '*'){
            next_num = get_num();
            next_op = get_op();
            next_sub_exp = sub_exp * next_num;
            return m_exp(next_sub_exp, next_op);
        }
        else if (op == '/'){
            next_num = get_num();
            next_op = get_op();
            next_sub_exp = sub_exp / next_num;
            return m_exp(next_sub_exp, next_op);
        }
        // If operator is invalid then exit the program
        else {
            printf("That is an invalid operator\n");
            exit(EXIT_FAILURE);
            return 0;
        }
    }
}

// Input: none, read from stdin
// Effect: get the next operator of the expression
//          this operator can be +, -, *, /, '\n'
//          '\n' indicates the end of the expression input
//          leading spaces should be skipped
// Output: return the next operator of the expression.
char get_op(){

    char op = getc(stdin);

    if (op == '+' || op == '-' || op == '*' || op == '/' || op == '\n'){
        return op;
    }
    else if (op == ' '){
        while (op == ' '){
            op = getc(stdin);
        }
    } 
    else {
        return 0;
    }
}

// Input: none, read from stdin
// Effect: get the next numeric value of the expression
// Output: return the next numeric value of the expression
float get_num(){
    float num;
    scanf("%f", &num);
    return num;
}

// Input: none
// Effect: Prompts user to enter a simple arithmetic expression.
//          Keeps prompting user for a new expression unless 
//          they enter an invalid operator or the user chooses to exit.
// Output: Prints the result of the simple arithmetic expression 
int main(void){
    float result;
    char cont='Y';

    do {
        printf("Input a simple arithmetic expresion: ");
        result = s_exp();
        
        printf(" The result is %f\n", result);
    
        printf("Do you want to continue? Y/N\n");
        scanf("%c", &cont);
    } while ((cont == 'Y') || (cont == 'y'));

    if (cont == 'N' || cont == 'n'){
        exit(0);
    }
    
}
