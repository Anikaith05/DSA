# K-th Element of Two Sorted Arrays

## Idea

Instead of merging the two arrays, we **binary search on the answer**.

Suppose we guess that the k-th smallest element is `mid`.

We count:

> **How many elements in both arrays are less than or equal to `mid`?**

If this count is at least `k`, then the k-th element is **less than or equal to `mid`**, so we search the left half.

Otherwise, the k-th element must be **greater than `mid`**, so we search the right half.

Eventually, binary search converges to the smallest value whose count of elements `<= value` is at least `k`. That value is the answer.

---

# Observation

For any number `x`,

```
count(x) = number of elements <= x
```

As `x` increases,

```
count(x)
```

never decreases.

Example:

```
Arrays:

A = [2,5,8]
B = [1,3,7]

x = 2 -> count = 2
x = 3 -> count = 3
x = 5 -> count = 5
x = 8 -> count = 6
```

Since the count is monotonic, binary search can be applied.

---

# Counting Elements

For each array,

```
upper_bound(array.begin(), array.end(), mid)
```

returns an iterator to the first element greater than `mid`.

Therefore,

```
upper_bound(...) - array.begin()
```

gives the number of elements less than or equal to `mid`.

So,

```cpp
count =
upper_bound(a.begin(), a.end(), mid) - a.begin()
+
upper_bound(b.begin(), b.end(), mid) - b.begin();
```

---

# Binary Search

Search space:

```
low  = minimum first element
high = maximum last element
```

For every `mid`,

### Case 1

```
count >= k
```

The answer could be `mid` or an even smaller value.

```
high = mid;
```

---

### Case 2

```
count < k
```

Not enough elements are `<= mid`.

The answer must be larger.

```
low = mid + 1;
```

---

Eventually,

```
low == high
```

which is the smallest value having at least `k` elements less than or equal to it.

That value is the k-th smallest element.

---

# Example

```
A = [2,3,6]
B = [1,4,8]

k = 4

Merged:

[1,2,3,4,6,8]

Answer = 4
```

Binary search:

```
low = 1
high = 8

mid = 4

count(4) = 4

Since count >= k,
search left.

Eventually,

low = high = 4
```

Answer:

```
4
```

---

# Time Complexity

Each binary search iteration performs:

- one `upper_bound` on array A
- one `upper_bound` on array B

```
O(log n + log m)
```

The binary search itself runs over the value range:

```
O(log(MaxValue - MinValue))
```

Overall:

```
O((log n + log m) × log(MaxValue - MinValue))
```

---

# Space Complexity

```
O(1)
```

No extra data structures are used.

---

# Key Insight

Rather than searching for the position of the k-th element directly, we search for the **smallest value** such that:

```
number of elements <= value >= k
```

Because this count increases monotonically with the value, binary search efficiently finds the k-th smallest element.