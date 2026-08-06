# Allocate Minimum Pages

## Intuition

The objective is to **minimize the maximum number of pages assigned to any student**.

At first glance, this looks like an optimization problem, but instead of directly searching for the answer, we can convert it into a **decision problem**.

Instead of asking:

> "What is the minimum possible maximum number of pages?"

we ask:

> "Is it possible to allocate all books such that no student receives more than `X` pages?"

This question has only two possible answers:

- **Yes**
- **No**

If it is possible for some value `X`, then it will also be possible for every value larger than `X`.

If it is impossible for some value `X`, then it will also be impossible for every value smaller than `X`.

This creates a monotonic pattern:

```
Invalid Invalid Invalid ... Valid Valid Valid
```

which is exactly the pattern required for **Binary Search on Answer**.

---

# Search Space

We now determine the minimum and maximum possible answers.

### Lower Bound

The answer can never be smaller than the largest book.

Why?

Because one student must read that book.

```
low = max(arr)
```

### Upper Bound

The largest possible answer occurs when one student receives every book.

```
high = sum(arr)
```

Therefore, our search space becomes

```
[max(arr), sum(arr)]
```

---

# Greedy Feasibility Check

For every candidate answer (`mid`), we check whether an allocation is possible.

We process the books from left to right.

For the current student,

- If the next book fits within the current page limit, assign it.
- Otherwise, allocate a new student and assign that book to them.

This greedy strategy always uses the **minimum number of students** required for the chosen page limit.

If the number of students required is

```
<= k
```

then the allocation is possible.

Otherwise, it is impossible.

---

# Why do we check `students <= k`?

The greedy algorithm computes the **minimum number of students required**.

Suppose

```
Books = [10,20,30]
k = 3
mid = 100
```

Greedy gives

```
Student 1 : 10 20 30
```

Only one student is used.

This is still valid because we can split the contiguous allocation into

```
Student 1 : 10
Student 2 : 20
Student 3 : 30
```

Every student still receives at least one book.

The allocation remains contiguous.

No student's pages exceed `mid`.

Therefore,

```
students <= k
```

is the correct feasibility condition.

---

# Algorithm

1. If `k > n`, return `-1` since every student must receive at least one book.
2. Compute
   - `low = max(arr)`
   - `high = sum(arr)`
3. Perform Binary Search on the answer.
4. For every `mid`
   - Run the greedy feasibility check.
   - If allocation is possible, search the left half.
   - Otherwise, search the right half.
5. Return the smallest valid value found.

---

# Dry Run

```
Books = [12,34,67,90]
k = 2
```

Search Space

```
low = 90
high = 203
```

Suppose

```
mid = 113
```

Allocation

```
Student 1 : 12 + 34 + 67 = 113
Student 2 : 90
```

Students used = 2

Valid.

Now Binary Search continues searching for a smaller valid answer.

Eventually,

```
Answer = 113
```

---

# Complexity Analysis

Let

- `n` = number of books
- `S` = sum of all pages

For every Binary Search iteration, we scan the array once.

Time Complexity

```
O(n × log(S))
```

Space Complexity

```
O(1)
```

---

# Key Observation

This problem belongs to the class of **Binary Search on Answer** problems.

Whenever a problem asks you to

- Minimize the maximum
- Maximize the minimum
- Partition an array into `k` contiguous parts
- Allocate work among `k` people

and the answer forms a monotonic pattern

```
FFFFFTTTTT
```

think of

> **Binary Search on Answer + Greedy Feasibility Check**