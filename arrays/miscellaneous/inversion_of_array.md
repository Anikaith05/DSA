# Count Inversions using Merge Sort

## Problem

Count pairs `(i, j)` such that:

- `i < j`
- `arr[i] > arr[j]`

Example:

```text
Input : [2,4,1,3,5]

Inversions:
(2,1)
(4,1)
(4,3)

Answer = 3
```

---

# Idea

Merge Sort divides the array into two **sorted** halves.

During merging:

- Left half inversions → Already counted
- Right half inversions → Already counted
- Only **cross inversions** remain to be counted.

---

# Why Merge Sort?

| Method | Time | Space |
|---------|------|-------|
| Brute Force | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n) |

---

# Merge Process

Suppose we're merging

```text
Left  = [2,4,7,9]
Right = [1,3,8]
```

Pointers:

```text
Left                  Right

2   4   7   9         1   3   8
^                     ^
i                     j
```

Since

```text
2 > 1
```

All remaining elements in the left half are also greater than `1`.

```text
(2,1)
(4,1)
(7,1)
(9,1)
```

So instead of

```cpp
count++;
```

we do

```cpp
count += (mid - i + 1);
```

---

# Why `mid - i + 1`?

Suppose

```text
Left indices

0   1   2   3
        ^
        i

mid = 3
```

Remaining elements

```text
index 2
index 3
```

Count

```text
3 - 2 + 1 = 2
```

General Formula

```cpp
count += (mid - i + 1);
```

---

# Merge Logic

```cpp
if(arr[i] <= arr[j])
```

- Move left element.
- No inversion.

---

```cpp
if(arr[i] > arr[j])
```

- Move right element.
- Add

```cpp
count += (mid - i + 1);
```

because every remaining left element forms an inversion.

---

# Algorithm

```text
MergeSort(left)

MergeSort(right)

Merge(left, right)
    Compare elements
    Count cross inversions
    Copy merged array back
```

---

# Complexity

| Complexity | Value |
|------------|-------|
| Time | O(n log n) |
| Space | O(n) |

---

# Common Mistakes

| Mistake | Correct |
|----------|---------|
| `j = mid` | `j = mid + 1` |
| `while(i < mid)` | `while(i <= mid)` |
| `while(j < high)` | `while(j <= high)` |
| `count++` | `count += (mid - i + 1)` |
| Counting while copying leftovers | Don't count |
| Forgetting to copy merged array back | Copy `temp` to `arr` |
| Wrong recursion | `(low, mid)` and `(mid + 1, high)` |
| Wrong base case | `if(low >= high) return;` |
| Using `int` for answer | Prefer `long long` |

---

# Code Flow

```text
                MergeSort(arr)

                     │
         ┌───────────┴───────────┐
         │                       │
     Left Half              Right Half
         │                       │
     MergeSort              MergeSort
         │                       │
         └───────────┬───────────┘
                     │
                  Merge
                     │
     Count Cross Inversions
                     │
               Sorted Array
```

---

# Key Takeaway

During merge,

```text
Left                  Right

2 4 7 9               1
^                     ^
```

If

```text
2 > 1
```

then

```text
4 > 1
7 > 1
9 > 1
```

automatically.

Hence,

```cpp
count += (mid - i + 1);
```

This is the core idea behind the **O(n log n)** inversion count algorithm.