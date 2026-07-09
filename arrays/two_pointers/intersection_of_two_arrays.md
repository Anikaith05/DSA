# Intersection of Two Arrays

This repository contains my solution for the **Intersection of Two Arrays** problem using C++ and `unordered_set`.

## Problem Statement

Given two integer arrays `nums1` and `nums2`, return an array containing their intersection.

Each element in the result must be unique. The order of elements does not matter.

### Example

```txt
Input:
nums1 = [1, 2, 2, 1]
nums2 = [2, 2]

Output:
[2]
```

## Approach Used

I used two `unordered_set`s.

1. Convert `nums1` into a set.
2. Convert `nums2` into another set.
3. Iterate through the first set.
4. If an element also exists in the second set, add it to the result vector.

Using sets automatically removes duplicate values.

## Concepts Learned

### `unordered_set`

`unordered_set` stores only unique values. It automatically removes duplicate values when elements are inserted.

For example:

```txt
nums1 = [1, 2, 2, 1]

set1 = {1, 2}
```

### Creating a Set from a Vector

A set can be created using a vector's `begin()` and `end()` iterators.

* `nums1.begin()` points to the first element.
* `nums1.end()` points just after the last element.
* The set constructor inserts every vector element into the set.

### Iterating Through a Set

A range-based `for` loop can be used to visit each unique element in a set.

### Checking Whether an Element Exists

`count(value)` checks whether a value exists in an `unordered_set`.

* Returns `1` if the value exists.
* Returns `0` if the value does not exist.

### `vector<int>`

A vector is used to store and return the final intersection values.

`push_back()` adds an element to the end of the vector.

## Time Complexity

* Creating the first set: `O(n)`
* Creating the second set: `O(m)`
* Checking common elements: `O(n)`

Overall: `O(n + m)`

## Space Complexity

Two sets are used to store the unique elements from both arrays.

`O(n + m)`

## Key Takeaway

Use `unordered_set` when you need:

* Unique values
* Fast existence checks
* Automatic duplicate removal
* Common elements between collections
