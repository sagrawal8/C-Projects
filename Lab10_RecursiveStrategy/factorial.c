// gcc factorial.c -o factorial
// ./factorial

#include <stdio.h>

long double factorial(long double n){
    long double result = 1;    
    for(long double i = n; i > 0; i--)
    {
        result = result * i;
    }
    return result;
};

long double factorial_rec(long double n){
    
    if(n == 0){
        return 1;
    }
    return n*factorial_rec(n - 1); 
}

int main(){

  // Both of these should print the same result!
  printf("factorial(100000000) = %Lf\n",factorial(1000000));
  printf("factorial_rec(10) = %Lf\n",factorial_rec(1000));


  return 0;
}
