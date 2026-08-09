# 🐄 Aggressive Cows

## 📌 Problem

Given stall positions and `k` cows, place the cows such that the **minimum distance between any two cows is as large as possible**.

### Example

```text
arr = [1, 2, 4, 8, 9]
k = 3
```

Optimal placement:

```text
1   2   4   8   9
🐄      🐄   🐄
│──────│──────│
   3      4
```

Minimum distance = `3`

**Answer = 3**

---

## 💡 Key Idea

We don't binary search for the positions of cows.

Instead, we binary search for the **minimum distance**.

```text
Possible minimum distance:

1  2  3  4  5  6  7  8
✓  ✓  ✓  ✗  ✗  ✗  ✗  ✗
      ↑
   Answer
```

This works because the answers are **monotonic**:

> If distance `4` is possible, then `1`, `2`, and `3` are also possible.

> If distance `4` is impossible, then `5`, `6`, ... are also impossible.

---

## 🔍 `isValid(mid)`

Question:

> Can we place `k` cows with at least `mid` distance between them?

First sort the stalls:

```text
[10, 1, 2, 7, 5]
       ↓ sort
[1, 2, 5, 7, 10]
```

Place the first cow at the first stall.

Then greedily place the next cow at the **earliest stall** that is at least `mid` away.

For `mid = 3`:

```text
1   2   5   7   10
🐄      🐄       🐄
│──────│────────│
   4        5
```

We placed 3 cows → `mid = 3` is valid.

### The important condition:

```cpp
if (arr[i] - last_placed_cow >= mid)
```

If valid:

```text
place cow 🐄
      ↓
last_placed_cow = arr[i]
```

---

## 🔄 Binary Search

```text
        mid
         ↓
[1  2  3  4  5  6  7  8]
         ✓  ✗
         ↑
      move right
```

* `mid` **valid** → try a larger distance
* `mid` **invalid** → try a smaller distance

```cpp
if (isValid(arr, mid, k)) {
    ans = mid;
    low = mid + 1;
}
else {
    high = mid - 1;
}
```

---

## 🧠 Algorithm

```text
Sort stalls
    ↓
Binary search minimum distance
    ↓
For every mid:
    ↓
Greedily place cows
    ↓
Can we place k cows?
   ↙       ↘
 YES       NO
  ↓         ↓
right      left
```


## ⏱️ Complexity

```text
Sorting       → O(n log n)
Binary Search → O(log(maxPosition))
Each check    → O(n)

Total         → O(n log n + n log(maxPosition))
```

### ⭐ Pattern

```text
Binary Search on Answer
          +
       Greedy
```

This same pattern appears in problems like **Allocate Pages, Split Array Largest Sum, and Capacity to Ship Packages**.
