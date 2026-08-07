# 🚢 Ship Packages Within D Days (Binary Search on Answer)

## 🧠 Intuition

We are asked to find the **minimum ship capacity** such that all packages can be shipped within `days`.

Notice:

- A **larger capacity** allows shipping in **fewer days**.
- A **smaller capacity** requires **more days**.

This forms a **monotonic relationship**:

| Capacity | Can Ship Within `days`? |
|----------|--------------------------|
| Small | ❌ No |
| Medium | ❌ No |
| Large | ✅ Yes |
| Larger | ✅ Yes |

Since the answer changes only once (`No → Yes`), we can use **Binary Search on the Answer**.

---

# 🔍 Binary Search Space

## Lowest Possible Capacity

The minimum capacity can be **1** (our validation function will reject capacities smaller than the largest package).

```cpp
low = 1;
```

---

## Highest Possible Capacity

If the ship carries **all packages in one day**, its capacity must be

```cpp
sum(weights)
```

```cpp
high = sum(weights);
```

---

# ✅ Validation Function

For a given capacity:

1. Start with Day 1.
2. Keep loading packages while they fit.
3. If the next package doesn't fit:
   - Ship the current load.
   - Start a new day.
4. Count the number of days used.

If

```text
days_used <= given_days
```

then this capacity is valid.

---

## Example

```
weights = [3,2,2,4,1,4]
days = 3

Capacity = 6
```

### Day 1

```
3 + 2 = 5
Next package = 2

5 + 2 > 6

Ship:
[3,2]
```

---

### Day 2

```
2 + 4 = 6

Ship:
[2,4]
```

---

### Day 3

```
1 + 4 = 5

Ship:
[1,4]
```

Used exactly **3 days**

✅ Valid capacity.

---

# 🔄 Binary Search

For every middle capacity:

```
mid = (low + high) / 2
```

If

```
isValid(mid)
```

is true

→ Try finding a **smaller capacity**

```cpp
ans = mid;
high = mid - 1;
```

Otherwise

→ Capacity is too small

```cpp
low = mid + 1;
```

---

# 📌 Why Move Left After Finding a Valid Capacity?

We are looking for the **minimum** valid capacity.

Once a capacity works, there might still exist a smaller one.

Example:

```
Capacity 12 ✅
Capacity 10 ✅
Capacity 9 ❌
```

We don't stop at 12—we continue searching to the left.

---

# 💻 Algorithm

1. Compute the total weight.
2. Binary search from `1` to `sum(weights)`.
3. For every capacity:
   - Simulate shipping.
   - Count days required.
4. If days required ≤ given days:
   - Store answer.
   - Search left.
5. Otherwise:
   - Search right.
6. Return the minimum valid capacity.

---

# ⏱️ Complexity Analysis

Let:

- `n` = number of packages
- `S` = sum of all package weights

### Time Complexity

Binary Search:

```
O(log S)
```

Validation:

```
O(n)
```

Overall:

```
O(n log S)
```

---

### Space Complexity

```
O(1)
```

Only a few variables are used.

---

# ✅ Key Observations

- Capacity increases → Required days decrease.
- The answer space is monotonic.
- Binary Search on Answer is applicable.
- The validation function greedily fills each day as much as possible.
- We search the **left half** after finding a valid capacity because we want the **minimum** valid answer.