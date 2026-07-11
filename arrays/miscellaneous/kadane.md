# ⚡ Kadane's Algorithm (Maximum Subarray)

## 🧠 DP State

`sum` = Maximum subarray sum **ending at the current index**.

---

## 🔄 Transition

```cpp
sum = max(nums[i], nums[i] + sum);
```

Choose the better option:

- 🟢 Start a new subarray from `nums[i]`
- 🔵 Extend the previous subarray

---

## 📌 Decision Rule

| Previous `sum` | Action |
|---------------|--------|
| ➕ Positive | Extend |
| ➖ Negative | Start New |

> **Positive sum helps. Negative sum hurts.**

---

## 🌍 Global Answer

Keep track of the best sum seen so far.

```cpp
msum = max(msum, sum);
```

---

## 📝 Algorithm

```cpp
sum = 0
msum = INT_MIN

for every element:
    sum = max(nums[i], nums[i] + sum)
    msum = max(msum, sum)

return msum
```

---

## ❗ Why `INT_MIN`?

Handles the case when **all elements are negative**.

Example:

```text
[-5, -2, -8]
```

Answer = `-2`

---

## ⏱️ Complexity

- **Time:** `O(n)`
- **Space:** `O(1)`

---

## 💡 One-Liner to Remember

> **At every index, either extend the previous subarray or start a new one—whichever gives the larger sum.**