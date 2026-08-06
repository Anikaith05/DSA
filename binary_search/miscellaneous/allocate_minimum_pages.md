# Allocate Minimum Pages

## 💡 Core Observation

We need to **minimize the maximum pages assigned to any student**.

Instead of directly finding the answer, convert it into a **Yes/No** question:

> **Can every student be assigned books such that no student gets more than `mid` pages?**

This makes it a **Binary Search on Answer** problem.

---

# 🔍 Search Space

| Lower Bound | Upper Bound |
|-------------|-------------|
| `max(arr)` | `sum(arr)` |

### Why?

| Bound | Reason |
|--------|--------|
| `max(arr)` | One student must take the largest book. |
| `sum(arr)` | One student can take all books. |

---

# 📈 Monotonic Property

```
mid

❌ ❌ ❌ ❌ ✅ ✅ ✅ ✅
```

If a page limit is possible,

then every larger page limit is also possible.

This monotonicity allows Binary Search.

---

# ✅ Feasibility Check (`isValid()`)

Greedily assign books.

| Condition | Action |
|-----------|--------|
| `pages + book <= mid` | Give current book to same student |
| Otherwise | Allocate a new student |

Finally,

```cpp
students <= k
```

means **Valid**.

---

# ❓Why `students <= k` instead of `students == k`?

The greedy algorithm computes the **minimum students required**.

Example:

```
Books = [10,20,30]
k = 3
mid = 100
```

Greedy gives

```
Student 1 : 10 20 30
```

Students used = **1**

We can always split it into

```
Student 1 : 10
Student 2 : 20
Student 3 : 30
```

without exceeding `mid`.

> **Greedy finds the minimum students needed, not the final allocation.**

Hence,

```cpp
students <= k
```

---

# 🚀 Algorithm

1. If `k > n`, return `-1`.
2. Set

```cpp
low = max(arr);
high = sum(arr);
```

3. Binary Search on `[low, high]`.
4. Run `isValid(mid)`.
5. If valid, search left half.
6. Else, search right half.

---

# ⏱ Complexity

| Metric | Complexity |
|---------|------------|
| Time | **O(n log(sum))** |
| Space | **O(1)** |

---

# 🧠 Key Takeaways

- ✅ Convert optimization into a **decision problem**.
- ✅ Binary Search on **Answer**, not on the array.
- ✅ Search space = **`[max(arr), sum(arr)]`**.
- ✅ Greedy computes the **minimum students required**.
- ✅ Feasible if **`students <= k`**.
- ✅ Binary Search returns the **smallest valid** answer.

---

# 📚 Pattern Recognition

Whenever a problem asks you to:

- Minimize the **maximum**
- Maximize the **minimum**
- Allocate work among `k` people
- Partition an array into contiguous parts

Think:

> **Binary Search on Answer + Greedy Feasibility Check**