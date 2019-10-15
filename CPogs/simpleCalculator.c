// Adapted From: https://www.programiz.com/c-programming/examples/calculator-switch-case

 // Performs addition, subtraction, multiplication or division depending the input from user
 
# include <stdio.h>
 
 int main() {
 //Just declare variables as normal, then access them via their addresses rather than declaring them as pointers
     char operator;
     double firstNumber, secondNumber;
 
     printf("Enter an operator (+, -, *,): ");
     scanf("%c", &operator);
 
     printf("Enter two operands: ");
     scanf("%lf %lf", &firstNumber, &secondNumber);
 
     switch(operator)
     {
         case '+':
             printf("\n%.1lf + %.1lf = %.1lf\n",firstNumber, secondNumber, firstNumber + secondNumber);
             break;
 
         case '-':
             printf("\n%.1lf - %.1lf = %.1lf\n",firstNumber, secondNumber, firstNumber - secondNumber);
             break;
 
         case '*':
             printf("\n%.1lf * %.1lf = %.1lf\n",firstNumber, secondNumber, firstNumber * secondNumber);
             break;
 
         case '/':
             printf("\n%.1lf / %.1lf = %.1lf\n",firstNumber, secondNumber, firstNumber / secondNumber);
             break;
 
         // operator doesn't match any case constant (+, -, *, /)
         default:
             printf("\n\nError!!! operator is not recognized");
     }
     
     return 0;
 }