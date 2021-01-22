# Exercises

In order to start thinking a bit algorithmically, modify this file and answer the following questions. Be sure to add/commit/push any changes made to this file to our repository.

1. In the worst case in our guessing game--how many guesses could it take to get the right number if we had no hint at all? Explain.
2. In the worst case in our guessing game--how many guesses does it take to get the right number if we get a hint of 'higher or lower' when guessing numbers 1-10? *Hint* In your answer show this mathematically with the [log function](https://www.mathsisfun.com/algebra/logarithms.html).

## Answers

1. Since there are 10 numbers and the range of numbers is known (1-10), and we assume this is the worst case possibility, the user could take upto 10 guesses to guess the number right. This would mean the user guesses the correct number on the last guess.
2. If the user gets a hint on whether his guess is higher or lower, this would make it quite similar to a binary search where the worst case possibility is log2(n) [base-2 log of n, where n is 10 in this case]. This is because the number of guesses is halved each instance the user gets a hint. log2(10) = 3.3 which means a maximum of 4 guesses. 
