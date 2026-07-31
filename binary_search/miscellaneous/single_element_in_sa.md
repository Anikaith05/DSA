# 🔍 LeetCode 540 - Single Element in a Sorted Array

## Idea

Find the point where the **pairing pattern changes**.

---

## Key Observation

| Before Single Element | After Single Element |
|------------------------|----------------------|
| Pairs start at **even** indices | Pairs start at **odd** indices |

Example

```text
1 1 2 2 3 3 4 4
^   ^   ^   ^
0   2   4   6   (Even)

----------------------------

1 1 2 3 3 4 4 8 8
      ^
   Single

3 3 -> starts at 3 (Odd)
4 4 -> starts at 5 (Odd)
8 8 -> starts at 7 (Odd)
```

---

## Binary Search Logic

Always force `mid` to an **even index**.

```cpp
if(mid % 2 == 1)
    mid--;
```

Now compare only:

```cpp
nums[mid]
nums[mid + 1]
```

---

## Cases

| Condition | Meaning | Action |
|-----------|---------|--------|
| `nums[mid] == nums[mid+1]` | Pair is valid. Single element is on the **right**. | `low = mid + 2` |
| `nums[mid] != nums[mid+1]` | Pair is broken. Single element is at `mid` or on the **left**. | `high = mid` |

---

## Why move `mid` to an even index?

So `mid` always points to the **first element of a pair**.

Example

```text
Index : 0 1 2 3 4 5

Value : 1 1 2 2 3 3
            ^
        mid = 3 (second occurrence)

↓

mid--

Value : 1 1 2 2 3 3
          ^
      mid = 2 (first occurrence)
```

Now checking `nums[mid] == nums[mid+1]` is meaningful.

---

## Binary Search Invariant

At every step,

> **The single element always lies inside `[low, high]`.**

We only eliminate indices that **cannot** contain the answer.

---

## Why `low == high`?

When

```text
low == high
```

the search space contains exactly **one index**.

Since the answer was never discarded, that remaining index **must** be the answer.

---

## Example

```text
nums = [1,1,2,3,3,4,4,8,8]

[0........8]
      ↓
[0....4]
      ↓
[0..2]
      ↓
[2]
```

Return

```cpp
nums[2]
```

---

## Hidden Invariants

| Invariant | Reason |
|-----------|--------|
| Answer is always inside `[low, high]` | We only discard impossible indices |
| `low` is always even | Starts at 0 and moves by `mid + 2` |
| `high` is always even | Starts at `n-1` (even) and becomes `mid` |
| `mid` is even before comparison | `if(mid % 2) mid--;` |
| Search interval always shrinks | `low` increases or `high` decreases |

---

## Complexity

| Time | Space |
|------|-------|
| **O(log n)** | **O(1)** |

---

## One-Line Intuition

> **Binary search repeatedly removes indices that cannot contain the answer while maintaining the invariant that the answer always lies within `[low, high]`.**