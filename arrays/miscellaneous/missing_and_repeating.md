# 📌 Missing & Repeating Number (Math Solution)

**Time:** `O(n)`  
**Space:** `O(1)`

---

## 💡 Idea

Let:

- `D` = Duplicate number
- `M` = Missing number

Compute:

- Difference of sums → `D - M`
- Difference of square sums → `D² - M²`

Then use the identity:

\[
D^2 - M^2 = (D - M)(D + M)
\]

to find `D + M`, and solve the two equations.

---

## Step 1: Sum

### Expected Sum

\[
\frac{n(n+1)}{2}
\]

### Actual Sum

```cpp
sum += arr[i];
```

### Difference

```cpp
d = actualSum - expectedSum;
```

\[
d = D - M
\]

---

## Step 2: Sum of Squares

### Expected Square Sum

\[
\frac{n(n+1)(2n+1)}{6}
\]

### Actual Square Sum

```cpp
sum1 += 1LL * arr[i] * arr[i];
```

### Difference

```cpp
d1 = actualSquareSum - expectedSquareSum;
```

\[
d_1 = D^2 - M^2
\]

---

## Step 3: Find `D + M`

Using

\[
D^2 - M^2 = (D - M)(D + M)
\]

\[
D + M = \frac{d_1}{d}
\]

```cpp
s = d1 / d;
```

---

## Step 4: Solve

We now have:

\[
D - M = d
\]

\[
D + M = s
\]

Therefore,

```cpp
duplicate = (s + d) / 2;
missing = (s - d) / 2;
```

---

## Code Mapping

| Variable | Meaning |
|----------|---------|
| `sum` | Actual sum |
| `sum1` | Actual square sum |
| `d` | `D - M` |
| `d1` | `D² - M²` |
| `s` | `D + M` |
| `duplicate` | Repeating number |
| `missing` | Missing number |

---

## ⚠️ Why `1LL`?

```cpp
1LL * n * (n + 1)
```

ensures the multiplication is performed using `long long`.

Without `1LL`:

```cpp
n * (n + 1)
```

is computed as an `int`, which can **overflow before** being assigned to a `long long`.

---

## Complexity

- **Time:** `O(n)`
- **Space:** `O(1)`