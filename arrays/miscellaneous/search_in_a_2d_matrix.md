# 🔍 LeetCode 74 — Search a 2D Matrix

> **Pattern:** Binary Search on a Virtual 1D Array

---

## 💡 Intuition (Striver's Approach)

Since:

- ✅ Every row is sorted.
- ✅ First element of a row > Last element of previous row.

The entire matrix can be **imagined as one sorted array**.

```
Matrix

1   3   5   7
10 11 16 20
23 30 34 60

↓

Virtual Array

[1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 60]
```

> **Don't actually flatten the matrix.**
> Just perform Binary Search on the virtual array.

---

# 🚀 Algorithm

### Step 1

Treat the search space as

```text
0 → (rows × cols - 1)
```

---

### Step 2

Binary Search

```cpp
mid = (low + high) / 2;
```

---

### Step 3

Convert `mid` into matrix coordinates.

```cpp
row = mid / cols;
col = mid % cols;
```

Access

```cpp
matrix[row][col]
```

---

### Step 4

Binary Search Update

```text
if value == target
    return true

if value < target
    low = mid + 1

else
    high = mid - 1
```

---

# 🧠 Why does the mapping work?

Suppose

```
rows = 3
cols = 4
```

```
Index

0  1  2  3
4  5  6  7
8  9 10 11
```

Every **4 elements** (number of columns), we move to the next row.

Hence,

```cpp
row = index / cols;
col = index % cols;
```

Example:

```
mid = 6

row = 6 / 4 = 1
col = 6 % 4 = 2
```

```
matrix[1][2] = 16
```

---

# 📊 Dry Run

Target = **16**

```
low = 0
high = 11

mid = 5
value = 11

11 < 16
↓

low = 6

----------------

mid = 8
value = 23

23 > 16
↓

high = 7

----------------

mid = 6
value = 16

Found ✅
```

---

# ⏱ Complexity

| Complexity | Value |
|------------|-------|
| Time | **O(log(m × n))** |
| Space | **O(1)** |

---

# 📝 Revision Notes

- ✅ Matrix behaves like one sorted array.
- ✅ Don't flatten the matrix.
- ✅ Binary Search from `0` to `rows × cols - 1`.
- ✅ `row = mid / cols`
- ✅ `col = mid % cols`
- ✅ If smaller → `low = mid + 1`
- ✅ If larger → `high = mid - 1`

---

# 🎯 Pattern

```
Sorted Matrix
      │
      ▼
Virtual Sorted Array
      │
      ▼
Binary Search
      │
      ▼
mid → (row, col)
      │
      ▼
Answer
```