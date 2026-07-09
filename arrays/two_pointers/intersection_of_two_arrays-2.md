# Intersection of Two Arrays II

## Problem

Given two integer arrays `nums1` and `nums2`, return their intersection.

Each element in the result should appear as many times as it appears in both arrays.

## Example

```txt
nums1 = [1, 2, 2, 1]
nums2 = [2, 2]

Output = [2, 2]
```

## Approach

* Create a frequency map for `nums1`.
* Create a frequency map for `nums2`.
* Iterate through the first frequency map.
* If a number exists in both maps, find the smaller frequency.
* Add that number to the result the smaller number of times.

For example:

```txt
nums1 = [1, 2, 2, 2]
nums2 = [2, 2, 3]

Frequency of 2 in nums1 = 3
Frequency of 2 in nums2 = 2

Common frequency = min(3, 2) = 2
```

So `2` is added twice to the result.

## Concepts Learned

* `unordered_map<int, int>` to store frequencies.

* `map[key]++` to count how many times a number appears.

* Structured bindings:

  ```cpp
  for (const auto& [key, value] : frequencyMap)
  ```

  * `key` stores the number.
  * `value` stores its frequency.

* `contains(key)` to check whether a key exists in an `unordered_map`.

* `min(a, b)` to find the common frequency.

* Nested loops to push a value multiple times into a vector.

* `vector<int>` to store the final intersection.

## Time Complexity

* Creating frequency maps: `O(n + m)`
* Iterating through the first map and building the result: `O(n)`

Overall:

`O(n + m)`

## Space Complexity

Two frequency maps and one result vector are used.

`O(n + m)`
