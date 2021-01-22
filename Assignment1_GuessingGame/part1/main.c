#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(){
    int guesses[5];
    int counter = 0;
    
    while(counter < 5){
        srand(time(NULL));      //randomize seed
        int correctAnswer = rand() % 10 + 1;  //generate random integer 
        printf("Game %d:\n", counter+1);
        int userGuess;
        int guessesPerGame = 0;
        printf("Guess a number between 1 and 10?\n");
        bool flag = false;   //flag to check if user guess = random num generated
       
        while(flag == false){
            scanf("%d",&userGuess);  //takes user guess
            if(userGuess == correctAnswer){
                printf("You guessed it right.\n");
                flag = true;
            }
            else if(userGuess > correctAnswer){
                printf("Your guess is higher than the correct answer.\n");
            }
            else{
                printf("Your guess is lower than the correct answer.\n");
            }
            guessesPerGame++; //increments user guess
        } 

        guesses[counter] = guessesPerGame;  //stores guesses for each round after user has guessed it right
        counter++;   //increments number of rounds played
    }
    int i;
    printf("5 rounds have been played.\nNumber of guesses per game:\n");
    for(i = 0; i < (sizeof(guesses)/sizeof(guesses[0])); i++){    //prints guesses for each of the 5 rounds
        printf("Game %d: %d\n", i+1, guesses[i]);
    
    }
}
