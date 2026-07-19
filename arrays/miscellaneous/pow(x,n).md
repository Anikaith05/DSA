# ⚡ LeetCode 50 — Pow(x, n)

## 💡 Key Idea

Instead of multiplying `x` by itself `n` times:

```text
x¹⁰ = x × x × x × ... (10 times)
```

Use **Binary Exponentiation**:

```text
x¹⁰ = (x⁵)²

x⁵ = x × (x²)²
```

At every step:

```text
n → n/2
```

```text
10 → 5 → 2 → 1 → 0
```

⏱ **Time Complexity:** `O(log n)`

---

# 🌳 Recursive Relation

### Base Case

```cpp
if (n == 0)
    return 1;
```

Because

```text
x⁰ = 1
```

---

### Recursive Case

```cpp
double y = power(x, n / 2);
```

If `n` is even:

```text
x⁸ = (x⁴)²
```

```cpp
return y * y;
```

If `n` is odd:

```text
x⁵ = x × (x²)²
```

```cpp
return x * y * y;
```

---

# 📚 Call Stack

```text
power(10)
    ↓
power(5)
    ↓
power(2)
    ↓
power(1)
    ↓
power(0)
```

Returns in reverse:

```text
0 → 1 → 2 → 5 → 10
```

---

# ❌ Why `n == 1` is NOT enough

If the function is called with `n = 0`:

```text
power(0)
   ↓
power(0)
   ↓
power(0)
```

Infinite recursion.

Always use

```cpp
if (n == 0)
    return 1;
```

---

# ➖ Negative Exponents

Use the identity:

```text
x⁻ⁿ = (1/x)ⁿ
```

So,

```cpp
if (N < 0) {
    x = 1 / x;
    N = -N;
}
```

Now recursion only deals with **positive exponents**.

---

# ⚠️ INT_MIN Overflow

```cpp
int n = -2147483648;
```

Doing

```cpp
n = -n;
```

tries to create

```text
2147483648
```

But an `int` can only store

```text
-2147483648  →  2147483647
```

So it overflows.

### Fix

```cpp
long long N = n;
```

Then

```cpp
N = -N;
```

is safe.

---

# 🧠 Two's Complement

To get a negative number:

1. Flip all bits
2. Add 1

Example:

```text
+5

0101

↓

1010

↓

1011

= -5
```

This is why `INT_MIN` has no positive counterpart.

---

# ✅ Final Code

```cpp
class Solution {
public:
    double power(double x, long long n) {
        if (n == 0)
            return 1;

        double y = power(x, n / 2);

        if (n % 2 == 0)
            return y * y;

        return x * y * y;
    }

    double myPow(double x, int n) {
        long long N = n;

        if (N < 0) {
            x = 1 / x;
            N = -N;
        }

        return power(x, N);
    }
};
```

---

# 📝 Checklist

- ✅ Binary Exponentiation
- ✅ Divide & Conquer
- ✅ Base Case
- ✅ Recursive Relation
- ✅ Call Stack
- ✅ Negative Exponents
- ✅ `INT_MIN` Overflow
- ✅ `long long` Fix
- ✅ Time: **O(log n)**
- ✅ Space: **O(log n)**