# PmergeMe Explanation & Ford-Johnson Walkthrough

This file breaks down exactly how the `PmergeMe.cpp` code operates, and walks through the Ford-Johnson (Merge-Insertion) algorithm step-by-step using an example sequence of 9 elements.

## PART 1: Code Breakdown (What the functions do)

### 1) `process(int argc, char** argv)`
- This is the main driver. It reads the string arguments passed to the program and converts them to integers.
- It validates the input (checks for negative numbers or non-numeric characters).
- It places the same numbers into two different containers: `std::vector` and `std::deque`.
- It measures the time taken to parse the numbers.
- It calls the sorting functions (`mergeInsertSortVec` and `mergeInsertSortDeq`) and measures their time.
- Finally, it prints the "Before", "After", and the execution time strings.

### 2) `generateJacobsthal(size_t max_val)`
- Generates the Jacobsthal sequence, which dictates the optimal order to insert the "loser" elements back into the main sorted chain. 
- Jacobsthal formula: `J(n) = J(n-1) + 2 * J(n-2)`. (Sequence: 0, 1, 1, 3, 5, 11, 21, 43...)
- It stops generating when the numbers exceed the size of the array we need to insert.

### 3) `mergeInsertSortVec(std::vector<int>& arr)`
- The core sorting algorithm! 
- **Step A (Straggler check)**: If the array has an odd length, it removes the last element and sets it aside as a "straggler" so we are left with an even number of elements.
- **Step B (Pairing)**: Iterates through the array and groups elements in twos. The larger element is pushed into a "Winners" array (`A`), and the smaller element is pushed into a "Losers" array (`B`).
- **Step C (Recursion)**: It recursively calls `mergeInsertSortVec` on the `A` array until it is completely sorted.
- **Step D (Mapping)**: Since `A` was rearranged and sorted, the code finds where each element in `A` moved, and rearranges `B` in the exact same pattern so `B[x]` still matches `A[x]`.
- **Step E (Main Chain Initialization)**: It copies `B[0]` and all of `A` into `main_chain`. We know `B[0]` is the absolute smallest element because it was smaller than `A[0]`, and `A[0]` is the smallest of all the winners.
- **Step F (Jacobsthal Insertion)**: It iterates through the Jacobsthal numbers to insert the remaining elements of `B` in reverse-group order into `main_chain` using Binary Search (`std::lower_bound`).
- **Step G (Straggler Insertion)**: If there was a straggler, it inserts it via binary search at the very end.

## PART 2: Example with 9 Elements

Let's do a dry run of the algorithm on a 9-element array:
Input: `[12, 3, 7, 1, 9, 5, 2, 8, 6]`

**Step 1: Check Straggler**
Length is odd (9). We remove the last element (`6`) and mark it as a straggler.
Array becomes: `[12, 3, 7, 1, 9, 5, 2, 8]`

**Step 2: Create Pairs and Sort Each Pair**
Pairs: `(12, 3), (7, 1), (9, 5), (2, 8)`
The larger goes to `A`, the smaller goes to `B`.
`A` (Winners) = `[12, 7, 9, 8]`
`B` (Losers)  = `[ 3, 1, 5, 2]`

**Step 3: Recursively Sort `A` (The "Inception" Step)**
We call the sorting function again, but this time only on `A` (`[12, 7, 9, 8]`). 
Because the algorithm is recursive, it repeats the exact same process on this smaller array:
  1. **Pairing**: It pairs `(12, 7)` and `(9, 8)`.
  2. **Winners/Losers**: Winners (`A2`) = `[12, 9]`. Losers (`B2`) = `[7, 8]`.
  3. **Deep Recursion**: It calls the function a third time on `A2` (`[12, 9]`).
     - It pairs `(12, 9)`.
     - Winners (`A3`) = `[12]`. Losers (`B3`) = `[9]`.
     - It recursively sorts `A3`. Since `A3` only has one element (`12`), the function hits the "base case" (size < 2) and stops recursing.
     - It builds the main chain starting with `B3[0]` (`9`) followed by `A3` (`12`). Chain = `[9, 12]`.
     - The array `[12, 9]` has now been successfully sorted into `[9, 12]`!
  4. **Mapping**: It rearranges `B2` to match the new `[9, 12]` order. Since `9` (index 1) moved to the front, `B2`'s index 1 (`8`) moves to the front. `B2` becomes `[8, 7]`.
  5. **Main Chain**: Starts with `B2[0]` and all of `A2`. Chain = `[8, 9, 12]`.
  6. **Insertion**: Binary search inserts the remaining `B2` element (`7`) into `[8, 9, 12]`. It goes to the very front.
  7. **Result**: The array is now `[7, 8, 9, 12]`.

Now, back in our main execution, `A` has been replaced with the perfectly sorted result from that recursive call!
Sorted `A` = `[7, 8, 9, 12]`

**Step 4: Realignment of `B`**
We rearrange `B` so it matches the new positions of `A`:
- `7` was at index 1 in the old `A`, so we take `B[1]` (`1`).
- `8` was at index 3 in the old `A`, so we take `B[3]` (`2`).
- `9` was at index 2 in the old `A`, so we take `B[2]` (`5`).
- `12` was at index 0 in the old `A`, so we take `B[0]` (`3`).
Sorted `A` = `[7, 8, 9, 12]`
Sorted `B` = `[1, 2, 5, 3]`

**Step 5: Initialize Main Chain**
The main chain is created by taking `B[0]` and appending all of `A`.
`main_chain` = `[1, 7, 8, 9, 12]`
Remaining `B` elements to insert: `[2, 5, 3]` (from indices 1, 2, and 3).

**Step 6: Jacobsthal Insertion**
We use the Jacobsthal sequence: `0, 1, 1, 3, 5` to dictate our insertion groups.
We start inserting backwards from the Jacobsthal number `3`.

- **Group 1**: Jacobsthal number `3`. 
  We insert down to the last inserted boundary (which was index 1). We insert `B[2]`, then `B[1]`.
  - Insert `B[2]` (which is `5`): Binary search places it at index 1.
    `main_chain` = `[1, 5, 7, 8, 9, 12]`
  - Insert `B[1]` (which is `2`): Binary search places it at index 1.
    `main_chain` = `[1, 2, 5, 7, 8, 9, 12]`

- **Group 2**: Jacobsthal number `5`. 
  Since the size of `B` is only 4 elements (indices 0-3), we cap the number at 4.
  We insert down to the last inserted boundary (which was index 3).
  - Insert `B[3]` (which is `3`): Binary search places it at index 2.
    `main_chain` = `[1, 2, 3, 5, 7, 8, 9, 12]`

**Step 7: Insert Straggler**
Finally, we binary search and insert our straggler (`6`) into the main chain.
Binary search places it at index 4.
Final `main_chain` = `[1, 2, 3, 5, 6, 7, 8, 9, 12]`

The sequence is successfully sorted!
