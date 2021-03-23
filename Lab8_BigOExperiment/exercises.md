Please edit this document below with your responses. Each question is worth 1/8 of your lab.

# Exercise 1

1. Record here how long it took you to run bubblesort and csort (Note: If you want to run several trials, say '10' and take an average that is an even better result!).

Bubble Sort:
real 0.355s
user 0.352s
sys 0.002s

CSort:
real 0.009	
user 0.006	
sys 0.003

# Exercise 2

What is the Big-O complexity of bubblesort?

O(n^2)

# Exercise 3

Do a little research and discover what algorithm qsort is in the C standard library. What is the algorithm? https://en.wikipedia.org/wiki/Qsort

Quick sort algorithm.
The comparator function takes two void pointers, p1 and p2, as arguments and returns their difference; this is how qsort() determines which element is smaller, or larger, than the other.

# Exercise 4

What is the Big-O complexity of 'qsort' that we use in the csort program?

O(logn)

# Exercise 5

Is qsort's Big-O complexity better or worse than bubblesort? (Anser: Yes it is better/ No it is worse/ It is equal)

Yes it is better

# Exercise 6

List the following functions in terms of their Big-O complexity from **smallest** to **largest**.
<img src="./media/bigo.jpg"/>

1. *edit your answer here for question 6*

# Exercise 7

- Given: f(n) = 3n^3 + n^2 + 27
- What is the O(n) of f(n)?

1. *edit your answer here for question 7*

# Exercise 8

- Given: f(n) = 3n^3 + n^2 + 27
- What are two constants c and k that prove your answer in exercise 7.
