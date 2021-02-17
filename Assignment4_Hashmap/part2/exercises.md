# Exercises

Discuss and answer the following questions (Make sure to elaborate and justify your responses):

1. How good is the provided hash function--are we really getting constant time operations with our hashmap?
2. What is one other way you could implement the hash function? Anything creative is acceptable in this answer.
3. If I have to resize the hashmap to add more buckets, what is th Big-O complexity?
4. What is 'open addressing' in regards to hash maps and hash tables?

## Answers:

1. Maybe if the number of items in the hashmap is low; but since we are putting words with same number of letters in the same bucket, the size of the bucket can grow to be really big. When this occurs, we won't get constant time when that occurs.
2. NewHashFunction = (Add integer values for each character in string)%(size of array)
3. O(N)
4. A way of handling collisions which consists of linear probing, quadratic probing, etc.


