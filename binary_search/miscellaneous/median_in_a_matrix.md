# Median in a Row-Wise Sorted Matrix

## 📌 Problem

Given an `n × m` **row-wise sorted** matrix (both `n` and `m` are odd), find the median **without flattening or sorting the entire matrix**.

---

# 💡 Core Idea

The matrix is **not globally sorted**, so we **cannot binary search on indices**.

Instead, **binary search on the value of the median**.

The median is the **smallest value** for which:

```text
Number of elements ≤ value > (n × m) / 2
```

---

# 🔍 Search Space

The median must lie between:

```cpp
low  = minimum element among the first column
high = maximum element among the last column
```

```text
low  = min(mat[i][0])
high = max(mat[i][m-1])
```

---

# 📊 Counting Elements ≤ mid

For every guessed value `mid`, count how many elements are **≤ mid**.

Since every row is sorted, use:

```cpp
upper_bound(row.begin(), row.end(), mid)
```

The index returned by `upper_bound` is exactly the number of elements **≤ mid**.

Example:

```text
Row:
2 5 8 11

upper_bound(...,8)

2 5 8 |11
       ^
```

```cpp
count += upper_bound(row.begin(), row.end(), mid) - row.begin();
```

Overall counting complexity:

```text
O(n log m)
```

---

# 🧠 Binary Search Logic

Let

```cpp
required = (n * m) / 2;
```

### Case 1

```text
count ≤ required
```

Too few elements are ≤ `mid`.

So the median must be **greater** than `mid`.

```cpp
low = mid + 1;
```

---

### Case 2

```text
count > required
```

Enough elements are ≤ `mid`.

`mid` **can be the median**, but there might be a smaller valid answer.

```cpp
high = mid;
```

---

# ❓Why not check for count == required + 1 ?

Because of duplicates.

Example:

```text
1 2 3
3 3 3
4 5 6
```

Sorted:

```text
1 2 3 3 3 3 4 5 6
```

Median = **3**

Counts:

| Value | Count ≤ Value |
|------:|--------------:|
|2|2|
|3|6|

Notice that the count jumps from **2 → 6**.

It never becomes **5**.

Hence we search for the **first value** where:

```text
count > required
```

instead of checking equality.

---

# 📈 Example Walkthrough

Matrix:

```text
1 3 5
2 6 9
3 6 9
```

```text
Total elements = 9
required = 4
```

| mid | count(≤mid) | Decision |
|----:|------------:|----------|
|5|5|Enough → high = 5|
|3|4|Too few → low = 4|
|4|4|Too few → low = 5|

```text
low = high = 5
```

Answer:

```text
5
```

---

# ✅ Algorithm

```text
Find minimum and maximum possible values.

Binary Search:

    mid = (low + high) / 2

    count = number of elements ≤ mid

    if(count <= required)
        low = mid + 1
    else
        high = mid

Return low.
```

---

# ⏱ Complexity

| Operation | Complexity |
|-----------|------------|
|Counting elements ≤ mid|O(n log m)|
|Binary search over values|O(log(maxVal − minVal))|

### Overall

```text
Time  : O(n log m × log(maxVal − minVal))
Space : O(1)
```

---

# 📝 Key Takeaways

- Binary search on **values**, not matrix indices.
- Use `upper_bound()` to count elements **≤ mid** in each row.
- If `count <= (n*m)/2`, search **right**.
- Otherwise, search **left** (including `mid`).
- Duplicates make checking `count == required + 1` incorrect.
- Final answer is **`low`**.