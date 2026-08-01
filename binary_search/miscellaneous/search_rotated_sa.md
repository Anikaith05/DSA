# 🔍 Search in Rotated Sorted Array

## Key Observation

In a rotated sorted array, **at least one half is always sorted**.

```text
4 5 6 7 | 0 1 2
---------+---------
 Left       Right
 Sorted    Rotated
```

or

```text
6 7 | 0 1 2 4 5
----+------------
Rotated   Sorted
```

---

## Algorithm

### Step 1

Perform Binary Search.

```cpp
mid = (low + high) / 2;
```

If

```cpp
nums[mid] == target
```

return `mid`.

---

### Step 2: Find the Sorted Half

| Condition | Meaning |
|-----------|---------|
| `nums[low] <= nums[mid]` | Left half is sorted |
| `else` | Right half is sorted |

### Why `nums[low] <= nums[mid]`?

If the left half is sorted,

```text
low        mid
 ↓          ↓
4 5 6 7 | 0 1 2
```

then

```cpp
nums[low] <= nums[mid]
```

must be true.

The `<=` is important because when only **one element** remains on the left,

```text
3 | 1
↑
low = mid
```

```cpp
nums[low] <= nums[mid]
```

becomes

```cpp
3 <= 3   ✔
```

A single element is always sorted.

Using `<` would incorrectly classify this case.

---

### Step 3: Check if the Target Lies in the Sorted Half

#### Left Half Sorted

```cpp
if(target >= nums[low] && target < nums[mid])
```

| Condition | Action |
|-----------|--------|
| True | `high = mid - 1` |
| False | `low = mid + 1` |

---

#### Right Half Sorted

```cpp
if(target > nums[mid] && target <= nums[high])
```

| Condition | Action |
|-----------|--------|
| True | `low = mid + 1` |
| False | `high = mid - 1` |

---

## Why `while(low <= high)`?

When

```text
low == high
```

one element is still left to check.

Using

```cpp
while(low < high)
```

would skip that final element.

---

## Complexity

| Time | Space |
|------|-------|
| **O(log n)** | **O(1)** |