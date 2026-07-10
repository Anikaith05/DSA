# 🧩 3Sum — Two Pointers Approach

## 🎯 Goal

Find all **unique triplets** whose sum is `0`.

A triplet must use three different indices.

---

## 💡 Core Idea

1. **Sort** the array.
2. Fix one number using `k`.
3. Use two pointers for the remaining part:

   * `i = k + 1`
   * `j = last index`
4. Move pointers based on the sum:

   * Sum too small → move `i` right.
   * Sum too large → move `j` left.
   * Sum is `0` → store the triplet and move both pointers.

---

## 🧠 Why Sorting Helps

After sorting:

* Moving `i` right increases the sum.
* Moving `j` left decreases the sum.
* Duplicate values become adjacent, making them easy to skip.

---

## 🔁 Pointer Rules

| Condition  | Action                           |
| ---------- | -------------------------------- |
| Sum `< 0`  | Move `i` right                   |
| Sum `> 0`  | Move `j` left                    |
| Sum `== 0` | Save triplet, move both pointers |

Use `i < j` because `i` and `j` must represent two different elements. When they meet, there are no valid pairs left.

---

## 🚫 Avoiding Duplicate Triplets

### Skip duplicate `k`

When `k` moves left to right, compare it with its previous value.

If the current value equals the previous value, skip this `k`.

This avoids repeating the same full search for the same fixed number.

### Skip duplicate `i` and `j`

After finding a valid triplet:

* Move `i` forward and skip values equal to the previous `i` value.
* Move `j` backward and skip values equal to the previous `j` value.

This prevents adding the same triplet multiple times.

---

## 🔍 Important Example

Sorted array:

`[0, 0, 0, 0, 0, 1, 1, 2]`

When `k` is the first `0`, `i` and `j` can still use other zeroes.

So `[0, 0, 0]` can be found.

Skipping later duplicate `k` values does **not** remove zeroes from the array. It only avoids repeating the same search with another identical fixed value.

---

## ⚠️ Mistakes to Avoid

* ❌ Not moving `i` and `j` after finding a triplet
  This can cause an infinite loop and Memory Limit Exceeded.

* ❌ Using a `while` loop with `continue` to skip duplicate `k` values
  `continue` does not change `k`, so the loop can run forever.

* ❌ Comparing duplicate `k` with `k + 1` in a normal `for` loop
  Compare with `k - 1` because `k` moves forward.

* ❌ Using `i < n` for the two-pointer loop
  Use `i < j` so the same element is never used twice.

* ❌ Skipping duplicates before checking the sum
  A duplicate can still be needed for a valid answer, such as `[0, 0, 0]`.

* ❌ Forgetting that `k` needs two elements after it
  Stop the outer loop when fewer than two elements remain.

---

## ⏱️ Complexity

| Type  | Complexity                           |
| ----- | ------------------------------------ |
| Time  | `O(n²)`                              |
| Space | `O(1)` extra space, excluding output |

Sorting takes `O(n log n)`, but the two-pointer searches dominate with `O(n²)`.
