**Learning Outcomes:**

This program will cover the following topics:

*   Templates
*   Inheritance
*   Recursion
*   Sorting
*   Memory Management with dynamic allocated memory. 

While this contains many concepts, this assignment largely lets you mimic what has been shown previously. 

As you code this problem, make sure to keep checking back at the Help and Get Help discussion board to help others or get help programming this problem.

# K-way Merge Sort Overview

The merge sort is popular for two reasons: 1) its worst case is O(n log n), and 2) it has a property known as stable. Like all sorting algorithms, it has downsides. Here the downside requiring O(n) additional memory, and it doesn't perform quite as fast as some other O(n log n) sorts. The upsides are often highly desired. 

The merge sort algorithm has a faster approach compared to the standard approach: using a k-way merge process. Previously, the merge sort worked by merging together *two* already sorted smaller input subarrays into one larger sorted array. (Note, the term subarray is used because the two inputs are conceptually treated as two separate arrays, but in reality are just two parts of the same array.) The k-way merge sort works by merging together *k* already sorted smaller input subarrays into one larger sorted array. 

# Examples of Regular Merge Sort and K-way Merge Sort

Suppose the regular merge sort has progressed to the last merge step shown below, where the array is two sorted regions ready to be merged into one fully sorted array. Note that the first five sorted five elements  followed by the sorted second five elements:

`Array: | a f j k p b d g l m |`

For simplicity, this one array is just conceptually treated as though they are two separate arrays, split in half.

`Subarray 0: | a f j k p |   Subarray 1: | b d g l m |`

The regular merge sort looks at the first unsorted element of subarray 0 and subarray 1, which are `a` and `b`. It compares the two with `<`. `a` is smaller:

`Merged Array: | a `

The regular merge sort then looks at the first unsorted element of subarray 0 and subarray 1, which are `f` and `b`. It compares the two with `<`. `b` is smaller:

`Merged Array: | a b`

The regular merge sort then looks at the first unsorted element of subarray 0 and subarray 1, which are `f` and `d`. It compares the two with `<`. `d` is smaller:

`Merged Array: | a b d`

And so on, until:

`Merged Array: | a b d f g j k l m p |`

The k-way merge sort approach works by merging together *k* input arrays instead of two arrays. Implemented correctly, this yeilds performance speedups over the prior 2-way merge sort. For example, suppose *k* is 4, and the merge sort is running on the following array:

`Subarray 0: | a h k r y |   Subarray 1: | c g m n p |   Subarray 2: | e i j o t |   Subarray 3: | d q u v x |`

The k-way merge sort looks at the first unsorted element of each subarray, which are `a`, `c`, `e`, and `d`. Somehow all four must be compared to find the smallest, which is `a`:

`Merged Array: | a`

The k-way merge sort looks at the first unsorted element of each subarray, which are `h`, `c`, `e`, and `d`. Somehow all four must be compared to find the smallest, which is `c`:

`Merged Array: | a c`

And so on, until: 

`Merged Array: | a c d e g h i j k m n o p q r t u v x y |`

# How to Implement a K-way Merge Sort

As described earlier for the merging process: "Somehow all four must be compared to find the smallest". This "somehow" is not trivial. The naive approach is to simply perform a `<` check for each pair, remembering the mininum each time. For small *k*, this is fine. In fact, the homework assignment has this already implemented as an ArrayKMerge sort. Review the code. It is not pretty.

For large *k*, this will not work. For example, if *k* = 4, then 3 `<` comparisons are required to find the minimum. If *k* = 16, then 15 comparisons are required to find the minimum. **Those 15 comparisons make the naive k-way merge sort performance worse than the regular 2-way merge sort.**

One approach to efficiently find the minimum value of *k* items is using a min heap tree. In short, a heap tree works by making sure the parent is always smaller than its two children. For example, suppose *k* = 16, and thus 16 input arrays are used. Further suppose these array values are three digit numbers. An example min heap of the first value of 16 input arrays may look like the following:
```
              14
         /         \
      152             82
    /     \         /     \
   210    350      198     418
  /  \    /  \    /  \    /   \ 
 301 322 461 439 313 299 500 499
/
349
```
Note that each parent is smaller than its two children. A min heap tree itself is not ordered or sorted in any way, it only means that every parent is smaller than its children. That also means the root of the tree, 14, is the smallest of them all. This last characteristic is exactly what we can use for the k-way merge sort. Again recall that each of these 16 values represent the first value of the 16 input sorted arrays. Instead of performing 15 `<` comparisons to find the smallest, the k-way merge sort need only refer to the root of the min heap tree, 14, and copy that to the output array. Once 14 is pulled out of the tree, it needs to be replaced. Suppose the subarray contained `14 199 222 450 512`. Since the next value in the subarray is 199, the 14 in the heap tree is replaced by 199. 
```
              199
         /         \
      152             82
    /     \         /     \
   210    350      198     418
  /  \    /  \    /  \    /   \ 
 301 322 461 439 313 299 500 499
/
349
```
The tree is now no longer a heap tree, 199 is bigger than its children. This is fixed easily. First, compare 199 with its children 152 and 82. Two `<` comparisons yeild that 82 is the smallest. 82 is swapped up. 
```
              82
         /         \
      152             199
    /     \         /     \
   210    350      198     418
  /  \    /  \    /  \    /   \ 
 301 322 461 439 313 299 500 499
/
349
```
Better, but the tree is still not a heap tree. The parent 199 is not the smallest. Again compare 199 with 198 and 418. Two `<` comparisons yeild that 198 is the smallest. 198 is swapped up:
```
              82
         /         \
      152             198
    /     \         /     \
   210    350      199     418
  /  \    /  \    /  \    /   \ 
 301 322 461 439 313 299 500 499
/
349
```
Good. The tree is a min heap tree again. All parents are smaller than their children. **All it took was 4 operator `<`, and not 15 operator `<` like the prior naive k-way approach.**  Now the k-way merge sort can iterate again. The root, 82, is the smallest value. It is put into the output array (after 14 from earlier). This entire process repeats, sorting one value each iteration, ultimately using fewer operator `<` steps. This approach now allows the k-way merge performance to substantially improve over a 2-way merge sort and over the prior naive k-way approach.

Note that implementing a performant heap data structure isn't trivial as it requires using a single array and clever indexing math. Fortunately, this homework assignment provides this min heap data structure and its logic. You will not implement any heaping logic. You will only use min heap code already supplied.

The overview here is largely to assist you in explaining why the k-way merge sort works using a heap.

## Requirements:
Implement the k-way merge sort in the file `HeapKMergeSort.hpp`, as found in the `inc` directory.  

Code construction can be divided into two primary tasks, 1) declaring the class and 2) implementing the runSort() methods

### 1. **Preparing the class**

Create a class called `HeapKMerge`. Use the the prior `Merge` and `ArrayKMerge` classes as a guide. They are found in `inc\MergeSort.hpp` and `inc\ArrayKMergeSort.hpp`.
* The class requires two template variables: `template <typename T, unsigned int K>`
* The class is named `HeapKMerge`. It publicly inherits from BaseSort<T>.
* A public constructor has a const unsigned int capacity parameter. This constructor invokes `BaseSort`'s constructor, and for the first argument passes in the name of this sort algorithm, `"Heap - K-Way Merge"`, and for the second argument passes in the capacity. The `HeapKMerge`'s public consturctor itself has no code logic, and thus its code body can simply be `{}`.
* A `public void runSort()` method. Declare the method in the class, and also provide the definition of the method after the class.
    * The definition requires two template variables: `template <typename T, unsigned int K>`
    * The method returns void. The `runSort()` method should be prefixed with `HeapKMerge<T, K>::`. The method body itself should be `{}` for now.
* A `private void runSort()` method with two parameters. The first is an unsigned int called `firstIndex`, the second is an unsigned int called `lastIndex`. 
    * The definition requires two template variables: `template <typename T, unsigned int K>`
    * The method returns void. This `runSort()` method should be prefixed with `HeapKMerge<T, K>::`. Supply the two parameters. The method body itself should be `{}` for now.
* In `src\k-way-mergesort-test.cpp`, uncomment the tests for the k-way merge sort.

At this point, your code should at least compile. No sort logic exists, but at least it compiles. Test that your program can build and run.

### 2. **Defining the methods**

The `HeapKMerge`'s public `runSort()` definition contains the same C++ logic the same as the `MergeSort`'s `runSort()` method. Change the currently empty method body so that it simply invokes the private method, passing in `0` for the first argument and `this->capacity` for the second argument. 

The `HeapKMerge`'s private `runSort()` definition is where the sorting logic occurs. The logic works through these steps:

1. Determine if recursion is done because the current working section of the array is only 1 item in size.
2. Recursively call `runSort()` *k* times, passing in indexes where each input subarray starts.
3. Create a copy of the current working section of the array.
4. Build the min heap tree using the array copy made in step 3.
5. Iterate.  For as long as there are values to sort
    1. obtain the smallest item on the min heap tree (the min heap object will rebuild its own heap tree correctly) and
    2. write that value to the correct spot in the current working section of the array

A full description is below:

1) The method works only within one region of the array at a time. That region starts at firstIndex and ends at lastIndex. For example, if the array has 1000 items, a method could have `firstIndex = 562` and `lastIndex = 625`. Thus, this method is currently working on an array region of size 625 - 562 = 63 items. In code, compute the number of items in this array region and store it in a variable. For this part 1, check if the array region size is less than 2. If so, no more sorting is necessary and the method simply calls `return;`.  

2) Recursive calls. The goal here is to subdivide the current array region into *k* ways for *k* smaller array regions, then recurisvely repeat the process. This requires indexing math. As an example, suppose this method is at a point where the array region contains 63 items, `firstIndex = 562`, `lastIndex = 625`, and  `k = 4`. A for loop would call `runSort()` *k* = 4 times, spliting those 63 items into 4 groups. The first group contains 15 items, the next contains of 16 items, the next contains of 16 items, and the final group of 16 itmes. Said another way, in the first iteration (*i* = 0) the arguments passed into a recursive runSort() call are 562 and 577. The second iteration (*i* = 1) the arguments for the recursive call are 577 and 593. The third itration (*i* = 2) the arguments for the recursive call are 593 and 609. The fourth iteration (*i* = 3) the arguments for the recursive call are 609 and 625.

The math here can be confusing at first. Indexing math often is often confusing, even for graduate students. Don't despair, just work at it out on paper until a solution is found. Note that all division math uses integer division. Use the example numbers in the prior section and simple artimetic to compute correct. Only `firstIndex`, `k`, `i`, and the number of values in this array region are needed in the arithmetic. Try it out on paper before you write it in code. For example, 
```	
firstIndex |  lastIndex | Total values in array region | i | K |  The first index to compute | The second index to compute
562           625         63                             0   4    562                          577
562           625         63                             1   4    577                          593
562           625         63                             2   4    593                          609
562           625         63                             3   4    609                          625
```	
Your task is to apply some basic arithmetic to values in the first, fourth, and fifth columns to compute the sixth and seventh columns. (Hint, do not immediately divide the number of values in array region by K. Due to integer division math in the example, it will round down to 15 every time and then the math won't work. You will use division, just later in the arithmetic.)  

3) Prior recursion has completed and sorted subarrays into smaller regions. Now the algorithm prepares to merge the prior sorted subarrays into a larger array. First create a copy of the current array region. An array can be dynamically allocated with the following line of code:

`T* arrayCopy = new T[number_of_array_values];`

A good rule of thumb is that whenever C++'s new is used to create an array, write the line of code right now to reclaim it (programmers often forget this). So at the end of this `runSort()` method, write:

``delete[] arrayCopy; ``

No code should be placed after that `delete[]` call.

After the C++ new call to create a new array, create for loop that iterates through the current array region. Copy each item to the arrayCopy. For example, if the current array region has `firstIndex = 562` and `lastIndex = 625`, then arrayCopy will be 63 items in size. The for loop must iterates 63 times. At `i = 0`, `this->arr` at index 562 is copied into `arrayCopy` at index 0. At `i = 1`, `this->arr` at index 563 is copied into `arrayCopy` at index 1. And so on, until `i = 62`, when `this->arr` at index 624 is copied into `arrayCopy` at index 62. Use simple indexing arithmetic to generalize these values.

4) Build the min heap tree using the array copy made in step 3. As this is a provided tool, only one line of code is required:

	``MinHeap<T, K> minHeap(arrayCopy, number_of_array_values);``

(Note, this min heap doesn't physically build a tree. The object just conceptually tracks where the trees elements are throughout the array. Further, this object also knows that the arrayCopy is split *k* ways, and has logic to know when a kth region is fully used up for the purposes of a k-way merge sort.)

5) Iterate and sort one element per iteration. This loop iterates equal to the amount of elements in the array region. For example, if the array region is 63 elements in size, this loop iterates 63 times.

Use the minHeap object to get the smallest unused item of the *k* arrays. You can do this simply through `minHeap.getSmallest();`. This method returns the value. Store that value in the next slot of `this->arr`. For example, with `firstIndex = 562`, `lastIndex = 625`, and iteration `i = 0`, then  `minHeap.getSmallest()` returns the smallest item in `arrayCopy`. Store that returned value in `this->arr` at index 562. At iteration `i = 1`, `minHeap.getSmallest()` returns the second smallest item in `arrayCopy`. Store that returned value in `this->arr` at index 563. And so on, until `i = 62`, then `minHeap.getSmallest()` returns the largest item in `arrayCopy`. Store that returned value in `this->arr` at index 624. Use simple indexing arithmetic to generalize these values.

This completes the algorithm. (Make sure the `delete[] arrayCopy;` line is still the last line of this method.)  The sort should now work. If it doesn't immediately work, try a test run with 8 array elements and `K = 2` with `runMySort(HeapKMerge<unsigned int, 2>(8));`. Use the debugger judiciously. Step in, step out, and step over where appropriate. Note that a step over on a recursive call will run all subsequent recursive calls, and so step into should usually be used on recursion. Consider also printing the arrays on the console as well as all the variable values for each `runSort()` call to help you see what the program is doing.  


### 3. **Expected output**

The program's output should resemble the following (times will vary depending on the speed of your machine and compiler optimizations). Note that merge sort will run a bit slower than quick sort and heap sort, largely due to frequent dynamic memory allocations and deallocations (an optimized version of merge sort would utilize a memory pool to avoid this.). If your IDE easily supports running in an optimized release mode and without debug flags, your times will improve by several factors.
```
--------testPresuppliedSorts Tests--------
Running sort: Bubble
Sorted!
Sort completed in 694.784 milliseconds
Passed Test 1. Bubble sort

Running sort: Selection
Sorted!
Sort completed in 614.948 milliseconds
Passed Test 2. Selection sort

Running sort: Insertion
Sorted!
Sort completed in 227.474 milliseconds
Passed Test 3. Insertion sort

Running sort: Heap
Sorted!
Sort completed in 408.375 milliseconds
Passed Test 4. Heap sort

Running sort: Quick
Sorted!
Sort completed in 214.669 milliseconds
Passed Test 5. Quick sort

Running sort: Array K-Way Merge
Sorted!
Sort completed in 733.575 milliseconds
Passed Test 6. K-Way Array Merge: 2-Way sort

Running sort: Array K-Way Merge
Sorted!
Sort completed in 572.317 milliseconds
Passed Test 7. K-Way Array Merge: 3-Way sort

Running sort: Array K-Way Merge
Sorted!
Sort completed in 613.787 milliseconds
Passed Test 8. K-Way Array Merge: 4-Way sort

Running sort: Array K-Way Merge
Sorted!
Sort completed in 458.036 milliseconds
Passed Test 9. K-Way Array Merge: 5-Way sort

Running sort: Array K-Way Merge
Sorted!
Sort completed in 496.46 milliseconds
Passed Test 10. K-Way Array Merge: 6-Way sort

Running sort: Array K-Way Merge
Sorted!
Sort completed in 596.656 milliseconds
Passed Test 11. K-Way Array Merge: 7-Way sort

Running sort: Array K-Way Merge
Sorted!
Sort completed in 489.695 milliseconds
Passed Test 12. K-Way Array Merge: 8-Way sort

##########################################################
## Note, some prior tests may fail on GitHub, that's ok ##
##########################################################
--------testKWayMerge Tests--------
########################################
## Uncomment these when ready to test ##
########################################
Running sort: Merge
Sorted!
Sort completed in 692.028 milliseconds
Passed Test 1. Merge sort

For information, this Merge Sort time will be the baseline: 692.028 milliseconds

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 741.08 milliseconds
Passed Test 2. K-Way Heap Merge: 2-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 559.562 milliseconds
Passed Test 3. K-Way Heap Merge: 3-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 476.592 milliseconds
Passed Test 4. K-Way Heap Merge: 4-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 421.259 milliseconds
Passed Test 5. K-Way Heap Merge: 5-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 448.904 milliseconds
Passed Test 6. K-Way Heap Merge: 6-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 477.825 milliseconds
Passed Test 7. K-Way Heap Merge: 7-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 383.791 milliseconds
Passed Test 8. K-Way Heap Merge: 8-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 392.513 milliseconds
Passed Test 9. K-Way Heap Merge: 9-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 523.459 milliseconds
Passed Test 10. K-Way Heap Merge: 10-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 441.972 milliseconds
Passed Test 11. K-Way Heap Merge: 11-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 384.976 milliseconds
Passed Test 12. K-Way Heap Merge: 12-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 366.887 milliseconds
Passed Test 13. K-Way Heap Merge: 13-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 399.579 milliseconds
Passed Test 14. K-Way Heap Merge: 14-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 495.377 milliseconds
Passed Test 15. K-Way Heap Merge: 15-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 850.619 milliseconds
Passed Test 16. K-Way Heap Merge: 31-Way sort

Running sort: Heap - K-Way Merge
Sorted!
Sort completed in 570.945 milliseconds
Passed Test 17. K-Way Heap Merge: 63-Way sort

##########################################################
## Note, some prior tests may fail on GitHub, that's ok ##
##########################################################
--------test_KWayMergeSpeedup Test--------
For information, the fastest sort was K-Way Heap Merge: 13-Way at 366.887 milliseconds,
which is a 46.9839 % speedup over the Merge Sort

Passed Test 1

--------test_KWayTemplates Tests--------
########################################
## Uncomment these when ready to test ##
########################################
Running sort: Heap - K-Way Merge
0.256297 0.784174 0.919149 0.535283 0.824701 0.0549552 0.24888 0.21832 0.0379265 0.927769 0.929766 0.208533 0.423646 0.229082 0.672457 0.690549 0.0810374 0.721979 0.215385 0.296597
0.0379265 0.0379265 0.0549552 0.0810374 0.208533 0.215385 0.215385 0.21832 0.229082 0.229082 0.24888 0.256297 0.423646 0.535283 0.535283 0.690549 0.721979 0.784174 0.919149 0.929766
Sorted!
Sort completed in 0.0051 milliseconds
Passed Test 1. K-Way Heap Merge: 4-Way, doubles sort

Running sort: Heap - K-Way Merge
fiwh vjqv saka hbzb rrgp atqt wjoy akpg jgua suwv uxxw auff gdhu udsk ywni qudv fttr jkrf mpyp hkqv
akpg atqt auff fiwh fttr gdhu hbzb hbzb hkqv hkqv jgua jgua jkrf qudv saka udsk udsk uxxw vjqv wjoy
Sorted!
Sort completed in 0.0512 milliseconds
Passed Test 2. K-Way Heap Merge: 4-Way, strings sort

----------------
Passed 4 out of 4 group tests
--End of tests--
```
