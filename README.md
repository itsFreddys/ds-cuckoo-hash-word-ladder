Word Ladder 

This program provides a C++ implementation of a WordSet (hash table) data structure and a word conversion algorithm. The WordSet data structure is a custom made hash table utilizing the cuckoo hash algorithm for its Efficient hashing, collision handling, and dynamic resizing.

The convert function implements a breadth-first search algorithm to find the shortest word ladder between two given words. It uses my custom hash table, WordSet, to efficiently check word validity and explore possible transformations.  

example:
converting from start word to end word in the fewest steps.
  Cat -> Dog
  Requires the following steps:
  cat -> cot -> dot -> dog
