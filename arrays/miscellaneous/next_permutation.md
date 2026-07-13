# 🔄 31. Next Permutation

**Pattern:** Greedy + Lexicographical Ordering

---

# 🎯 Goal

Find the **smallest permutation that is larger than the current permutation**.

Think:

> **Increase the number by the smallest possible amount, then make the remaining part as small as possible.**

---

# 🚀 Approach

## ✅ Step 1: Find the Pivot

Traverse from **right to left** and find the first index where

```
nums[i] < nums[i+1]
```

This index is called the **pivot**.

Example:

```
1 2 3 6 5 4
    ^
```

Everything after the pivot is guaranteed to be **descending**.

---

## ✅ Step 2: Find the Smallest Greater Element

Since the suffix is already **descending**, the smallest values are on the **right**.

So instead of searching for the minimum,

**scan from the end** and stop at the first element greater than the pivot.

---

## ✅ Step 3: Swap

Swap the pivot with the element found in Step 2.

This creates the **smallest possible increase**.

---

## ✅ Step 4: Reverse the Suffix

After the swap, the suffix is still descending.

Reverse it to make it ascending (the smallest possible arrangement).

This guarantees the **next lexicographical permutation**.

---

# 🧠 Why Reverse?

Current:

```
1 2 4 | 6 5 3
```

Suffix:

```
6 5 3
```

Smallest arrangement:

```
3 5 6
```

Reverse:

```
6 5 3
↓
3 5 6
```

---

# ❌ Mistakes I Made

### ❌ Mistake 1

```cpp
while(j > 0)
```

Didn't check index `0`.

✔️ Correct:

```
j >= 0
```

---

### ❌ Mistake 2

Tried to find the minimum element in the suffix.

Wrong thought:

> "Find the smallest element."

Correct thought:

> "Find the smallest element **greater than the pivot**."

---

### ❌ Mistake 3

Used a linear search to find the minimum greater element.

Unnecessary.

Since the suffix is **descending**, simply scan from the end until you find

```
nums[i] > nums[pivot]
```

The first such element is automatically the correct one.

---

# ⚡ Complexity

- **Time:** `O(n)`
- **Space:** `O(1)`

---

# 🎯 Memory Trick

```
Find Pivot
      ↓
Find First Greater From Right
      ↓
Swap
      ↓
Reverse Suffix
```

> **Pivot → Swap → Reverse**