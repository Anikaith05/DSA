# Find Nth Root of M

## Approach

The goal is to find an integer `x` such that:

\[
x^n = m
\]

If no such integer exists, return `-1`.

---

# Step 1: Observe the Pattern

Consider the function:

\[
f(x) = x^n
\]

For positive integers, it is **monotonically increasing**.

| x | xⁿ |
|---|----|
| 1 | 1 |
| 2 | 2ⁿ |
| 3 | 3ⁿ |
| 4 | 4ⁿ |

Since the values are increasing, we can **Binary Search** on the answer.

---

# Step 2: Define the Search Space

The possible integer root lies between:

| Variable | Value |
|----------|-------|
| Low | `0` |
| High | `m` |

For every middle value:

```
mid = (low + high) / 2
```

Compute:

```
midⁿ
```

and compare it with `m`.

---

# Step 3: Binary Search Decisions

| Condition | Meaning | Move |
|-----------|---------|------|
| `midⁿ == m` | Root found | Return `mid` |
| `midⁿ < m` | Root is larger | `low = mid + 1` |
| `midⁿ > m` | Root is smaller | `high = mid - 1` |

Repeat until `low > high`.

---

# Step 4: Efficiently Compute `midⁿ`

Computing powers naively takes **O(n)**.

Instead, use **Binary Exponentiation**.

### Idea

| Exponent | Operation |
|----------|-----------|
| Odd | Multiply answer by `x`, decrease exponent |
| Even | Square the base, halve the exponent |

### Algorithm

```
ans = 1

while (n > 0)

    if n is odd
        ans *= x
        n--

    else
        x *= x
        n /= 2
```

This computes `xⁿ` in **O(log n)**.

---

# Dry Run

### Input

```
n = 3
m = 27
```

| low | high | mid | mid³ | Decision |
|-----|------|-----|------|----------|
| 0 | 27 | 13 | 2197 | Search Left |
| 0 | 12 | 6 | 216 | Search Left |
| 0 | 5 | 2 | 8 | Search Right |
| 3 | 5 | 4 | 64 | Search Left |
| 3 | 3 | 3 | 27 | Answer Found |

Output:

```
3
```

---

# Complexity

| Operation | Time |
|-----------|------|
| Binary Search | `O(log m)` |
| Binary Exponentiation | `O(log n)` |
| Overall | **O(log m × log n)** |
| Space | **O(1)** |

---

# Key Takeaways

- The function `xⁿ` is monotonic, making Binary Search possible.
- Search over the **answer space**, not an array.
- Use Binary Exponentiation to compute powers efficiently.
- Move:
  - Right if `midⁿ < m`
  - Left if `midⁿ > m`
- Use `long long` while computing powers to reduce overflow risk.