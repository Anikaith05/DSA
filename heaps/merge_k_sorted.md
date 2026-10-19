# Merge K Sorted Arrays using Min Heap

## Problem Statement

Given a 2D matrix `mat` containing `n` sorted arrays, merge all the arrays into a single sorted array.

Each individual array is sorted in ascending order. The goal is to combine all elements into one sorted array efficiently.

## Approach: Min Heap (Priority Queue)

We use a **Min Heap** to efficiently find the smallest element among the current elements of all arrays.

Instead of comparing every element, we maintain only one candidate element from each array in the priority queue.

### How It Works

1. **Initialize the Min Heap:** Insert the first element of every array into the priority queue along with its array index and element index.
2. **Extract the Minimum:** Remove the smallest element from the heap and add it to the result array.
3. **Insert the Next Element:** After removing an element, insert the next element from the same array, if one exists.
4. **Repeat:** Continue until the priority queue becomes empty.
5. **Return the Result:** The result array contains all elements merged in ascending order.

## Data Structure Used

We store three values in the priority queue:

`{value, arrayIndex, elementIndex}`

- `value`: The current element's value.
- `arrayIndex`: The index of the array containing the element.
- `elementIndex`: The index of the element within that array.

The priority queue is declared as:

```cpp
priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
```

This creates a min heap using lexicographical ordering of the vectors. The smallest value is therefore extracted first.


## Example

**Input:**

```text
mat = [
    [1, 4, 7],
    [2, 5, 8],
    [3, 6, 9]
]
```

**Output:**

```text
[1, 2, 3, 4, 5, 6, 7, 8, 9]
```

### Dry Run

Initially, the heap contains the first element of each array:

```text
Heap: [1, 2, 3]
```

| Step | Extracted Element | Next Element Inserted | Result |
|---|---:|---:|---|
| 1 | 1 | 4 | 1 |
| 2 | 2 | 5 | 1, 2 |
| 3 | 3 | 6 | 1, 2, 3 |
| 4 | 4 | 7 | 1, 2, 3, 4 |
| 5 | 5 | 8 | 1, 2, 3, 4, 5 |
| 6 | 6 | 9 | 1, 2, 3, 4, 5, 6 |
| 7 | 7 | None | 1, 2, 3, 4, 5, 6, 7 |
| 8 | 8 | None | 1, 2, 3, 4, 5, 6, 7, 8 |
| 9 | 9 | None | 1, 2, 3, 4, 5, 6, 7, 8, 9 |

The process ends when the heap is empty.

## Time Complexity

Let:
- `n` = number of sorted arrays.
- `m` = number of elements in each array.
- `N = n × m` = total number of elements.

**Time Complexity: `O(N log n)`**

- Initializing the heap takes `O(n log n)` time using repeated insertions.
- Each of the `N` elements is extracted once, and at most one new element is inserted.
- Each heap operation takes `O(log n)` time because the heap contains at most `n` elements.

Therefore, the overall complexity is `O(N log n)`.

**Space Complexity: `O(n)` auxiliary space for the min heap.**

The result array requires an additional `O(N)` space.

## Key Takeaways

- A min heap efficiently tracks the smallest available element across multiple sorted arrays.
- Only one element from each array needs to be in the heap at a time.
- After extracting an element, insert the next element from that same array.
- This technique is more efficient than combining all elements and sorting them again.
- The same approach is useful for merging K sorted linked lists and other K-way merging problems.

## Related Concepts

- Priority Queue
- Min Heap
- K-Way Merge
- Heap Operations
- Merge K Sorted Linked Lists
