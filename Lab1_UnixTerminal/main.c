#include <stdio.h>

double power(double base, double n){
	int i;
    int product = base;
    for (i = 0; i < n; i++){
        product *= base;
    }
    return product;
}

int main(){
	int i;

    char* str = "";
	for(i = 0; i < 10; i++){
		if(i == 0){
			str = "st";
        }
        else if(i == 1){
            str = "nd";
        }
        else if(i == 2){
            str = "rd";
        }
        else{
            str = "th";
        }
		printf("2 to the %d%s power is: %f\n", i+1, str, power(2, i));
	}
	
}
