# Aggressive Cows

## Problem

Given an array `arr[]` representing the positions of stalls and an integer `k` representing the number of cows, place exactly `k` cows in different stalls such that the **minimum distance between any two cows is maximized**.

### Example

```text
Input:
arr = [1, 2, 4, 8, 9]
k = 3

Output:
3
```

One optimal placement is:

```text
1   2   4   8   9
🐄      🐄   🐄
```

Cows are placed at:

```text
1, 4, 8
```

Distances:

```text
4 - 1 = 3
8 - 4 = 4
```

Therefore, the minimum distance is `3`, which is the maximum possible.

---

# Approach: Binary Search on Answer

The answer is the **maximum possible minimum distance**.

Instead of directly finding the answer, we binary search on the possible distance.

Suppose we want to check whether a minimum distance of `mid` is possible.

The question becomes:

> Can we place at least `k` cows such that every pair of consecutive cows is at least `mid` distance apart?

If yes, `mid` is a valid answer and we try a larger distance.

If no, we try a smaller distance.

---

## Why Do We Sort the Array?

First, sort the stall positions:

```cpp
sort(arr.begin(), arr.end());
```

For example:

```text
[10, 1, 2, 7, 5]
```

becomes:

```text
[1, 2, 5, 7, 10]
```

Sorting allows us to greedily place each cow at the **earliest possible stall**.

This is important because after placing a cow, we only need to look forward for the next valid stall.

---

# `isValid()` Function

The function:

```cpp
bool isValid(vector<int>& arr, int capacity, int cows)
```

checks whether it is possible to place at least `cows` cows with a minimum distance of `capacity`.

### Important variables

```cpp
int curr_cows = 1;
int last_placed_cow = arr[0];
```

We initially place the first cow at the first stall.

Then for every other stall:

```cpp
if(abs(arr[i] - last_placed_cow) >= capacity)
```

If the current stall is at least `capacity` away from the last placed cow, we place another cow there:

```cpp
curr_cows++;
last_placed_cow = arr[i];
```

At the end:

```cpp
return curr_cows >= cows;
```

If we managed to place at least `k` cows, then the distance is feasible.

---

# Why Greedy Placement Works

Suppose:

```text
arr = [1, 2, 4, 8, 9]
capacity = 3
```

Place the first cow at:

```text
1
```

Now find the earliest stall at least `3` away:

```text
4 - 1 = 3
```

So place the second cow at `4`.

Next:

```text
8 - 4 = 4
```

So place the third cow at `8`.

Thus:

```text
1 → 4 → 8
```

We successfully placed 3 cows.

### Why choose the earliest possible stall?

Because placing a cow as early as possible leaves **more space for the remaining cows**.

Therefore, if the greedy approach cannot place `k` cows, no other placement can do so for that particular `capacity`.

---

# Binary Search

The possible minimum distance lies between:

```cpp
low = 1;
high = max_n - min_n;
```

where:

* `1` is the smallest meaningful distance.
* `max_n - min_n` is the largest possible distance between two stalls.

We calculate:

```cpp
int mid = low + (high - low) / 2;
```

Then:

### If `mid` is valid

```cpp
if(isValid(arr, mid, k))
```

We can place the cows with at least `mid` distance.

Therefore, try a larger distance:

```cpp
ans = mid;
low = mid + 1;
```

### If `mid` is invalid

We cannot maintain that much distance.

Therefore, try a smaller distance:

```cpp
high = mid - 1;
```

---

# Dry Run

Consider:

```text
arr = [1, 2, 4, 8, 9]
k = 3
```

After sorting:

```text
[1, 2, 4, 8, 9]
```

Search range:

```text
low = 1
high = 8
```

Suppose:

```text
mid = 4
```

Can we place 3 cows with minimum distance `4`?

Place first cow:

```text
1
```

Next valid stall:

```text
8 - 1 = 7 >= 4
```

Place second cow at `8`.

Next:

```text
9 - 8 = 1 < 4
```

Cannot place another cow.

Only 2 cows can be placed.

Therefore:

```text
4 is invalid
```

Search the smaller half.

Eventually:

```text
mid = 3
```

Placement:

```text
1 → 4 → 8
```

Distances:

```text
3, 4
```

So 3 cows can be placed.

Therefore:

```text
3 is valid
```

Try a larger distance.

No larger distance works, so:

```text
Answer = 3
```

# Complexity

### Sorting

```text
O(n log n)
```

### `isValid()`

Each call scans the array once:

```text
O(n)
```

### Binary Search

The answer range is at most `10^8`, so:

```text
O(log(maxPosition - minPosition))
```

Therefore, total complexity is:

```text
O(n log n + n log(maxPosition))
```

Since `maxPosition ≤ 10^8`, this is effectively:

```text
O(n log n)
```

### Space Complexity

Sorting uses:

```text
O(log n)
```

auxiliary space depending on the sorting implementation.

---

# Key Pattern to Remember

This problem is a classic example of:

> **Binary Search on Answer + Greedy**

The general pattern is:

```text
1. Sort the array
2. Binary search the answer
3. For each mid:
       Greedily check whether mid is feasible
4. If feasible:
       search right
   Otherwise:
       search left
```

The most important line in this problem is:

```cpp
if(arr[i] - last_placed_cow >= mid)
```

It means:

> "Can I place the next cow at this stall while maintaining a minimum distance of `mid`?"
