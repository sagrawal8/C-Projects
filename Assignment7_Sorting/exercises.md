# Exercises

Discuss and answer the following questions (Please make sure to elaborate and justify your responses):

1. Explain what do you think the Big-Oh (worst-case) complexity of this algorithm is? Why?
2. What do you think the best-case complexity of this algorithm is?
   - Provide an example of an array of elements that fit the best-case.
3. Does insertion sort require any additional storage beyond the original array? Explain why or why not.
4. What is a 'stable sorting' algorithm? Is insertion sort a 'stable' algorithm, why or why not?

## Answers:

1. O(n^2)
2. O(n); array = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} or array = {1,2,3,4,5,6,7,8,9}
3. No it sorts elements in the same array by swapping values within the array.
4. A sorting algorithm is said to be stable if two objects with equal keys appear in the same order in sorted output as they appear in the input array to be sorted. Insertion sort is stable as it only swaps values if array[j+1] < array[j] and not if array[j+1] <= array[j].
