# 🟢 62. Unique Paths

## 💡 Intuition

- ⬇️ Down moves = `m - 1`
- ➡️ Right moves = `n - 1`

Therefore,

```text
Total Moves = (m - 1) + (n - 1)
            = m + n - 2
```

Every valid path is simply an arrangement of these moves.

Hence,

```text
Unique Paths = C(m+n-2, m-1)
             = C(m+n-2, n-1)
```

---

## 🚀 Optimized Combination Formula

Instead of

```math
C(N,r)=\frac{N!}{r!(N-r)!}
```

use

```math
C(N,r)=
\frac{N(N-1)\cdots(N-r+1)}
{1\cdot2\cdots r}
```

Compute it iteratively:

```cpp
long long ans = 1;

for(int i=1;i<=r;i++)
{
    ans = ans * (N-r+i) / i;
}
```

where

```cpp
N = m + n - 2;
r = min(m-1, n-1);
```

---

## ⚠️ Overflow (Important)

❌ Don't compute factorials.

```cpp
N! / (r! * (N-r)!)
```

Even

```text
20! = 2,432,902,008,176,640,000
```

is already larger than what many integer types can safely handle for this approach, and for this problem `N` can be as large as **198**.

✅ Computing the combination **term by term** avoids creating these huge intermediate factorial values.

---

## ❌ Mistake I Made

I wrote

```cpp
ans *= (N-r+i)/i;
```

This is interpreted as

```cpp
ans = ans * ((N-r+i)/i);
```

Since `(N-r+i)` and `i` are integers,

```cpp
7/2 = 3
```

(not `3.5`)

So,

```text
6 × (7/2)
= 6 × 3
= 18 ❌
```

The correct code is

```cpp
ans = ans * (N-r+i) / i;
```

which evaluates as

```text
(6 × 7) / 2
= 21 ✅
```

> **Rule:** Multiply first, then divide.

---

## ⏱️ Complexity

| Time | Space |
|------|-------|
| 🟢 `O(min(m,n))` | 🟢 `O(1)` |

---

## ⭐ Key Points

- ✅ Total moves = `m + n - 2`
- ✅ Down moves = `m - 1`
- ✅ Right moves = `n - 1`
- ✅ Answer = `C(m+n-2, m-1)`
- ✅ Avoid factorials (overflow).
- ✅ Multiply first, then divide.
- ✅ Use `r = min(m-1, n-1)` to minimize iterations.