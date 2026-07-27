# Longest Subarray with Sum K (Prefix Sum + Hash Map)

## 💡 Key Observation

### ❌ Sliding Window doesn't work

Sliding window relies on the sum changing **monotonically**.

- Expand window → Sum increases
- Shrink window → Sum decreases

This property **breaks** when negative numbers are present.

Example:

```text
[2, -1, 2]
```

Removing `2` from the left may not decrease the sum as expected because of `-1`.

➡️ Since the array contains **negative numbers**, we use **Prefix Sum + Hash Map**.

---

## 🧠 Core Idea

Let

```text
prefixSum(i) = arr[0] + arr[1] + ... + arr[i]
```

Suppose a subarray from `(j+1 ... i)` has sum `k`.

Then,

```text
prefixSum(i) - prefixSum(j) = k
```

Rearranging,

```text
prefixSum(j) = prefixSum(i) - k
```

So while traversing the array:

- Compute the current prefix sum.
- Check whether `prefixSum - k` has appeared before.
- If yes, we've found a valid subarray.

---

## 🗺️ Hash Map

Store

```cpp
prefixSum -> first index where it occurs
```

Example:

```text
Prefix Sum : 10 15 17 24 25 15
Index      :  0  1  2  3  4  5
```

Store only the **first occurrence**:

```text
10 -> 0
15 -> 1
17 -> 2
24 -> 3
25 -> 4
```

Do **not** overwrite existing entries.

Why?

The subarray length is

```text
length = currentIndex - previousIndex
```

The earliest occurrence gives the **maximum** possible length.

---

## 🚀 Algorithm

1. Compute the running prefix sum.
2. Initialize

```cpp
mp[0] = -1;
```

to handle subarrays starting from index `0`.

3. For every prefix sum:
   - If it is not in the map, store its index.
   - Search for `prefixSum - k`.
   - If found,

```cpp
length = currentIndex - previousIndex;
```

4. Update the maximum length.

---

## ⚡ Dry Run

```text
arr = [10, 5, 2, 7, 1, -10]
k = 15
```

| i | Prefix Sum | Need (`prefix-k`) | Found | Max Length |
|---|-----------:|------------------:|------:|-----------:|
|0|10|-5|❌|0|
|1|15|0|✅ (-1)|2|
|2|17|2|❌|2|
|3|24|9|❌|2|
|4|25|10|✅ (0)|4|
|5|15|0|✅ (-1)|6|

Answer = **6**

---

## ⏱ Complexity

- **Time:** `O(n)`
- **Space:** `O(n)`

---

## 📌 Pattern Recognition

| Condition | Approach |
|-----------|----------|
| All positive numbers | Sliding Window |
| Positive + Zero | Sliding Window |
| Positive + Negative | Prefix Sum + Hash Map |

> **Interview Rule:** If the problem asks for **Longest Subarray with Sum K** and **negative numbers are allowed**, think **Prefix Sum + Hash Map**.