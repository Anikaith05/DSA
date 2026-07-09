# 🌟 Pascal's Triangle — LeetCode 118

<p align="center">
  <img src="https://img.shields.io/badge/LeetCode-118-orange?style=for-the-badge&logo=leetcode" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus" />
</p>

## 📌 Problem Statement

Given an integer `numRows`, return the first `numRows` of Pascal's Triangle.

In Pascal's Triangle:

* Every row starts with `1`.
* Every row ends with `1`.
* Each middle element is the sum of the two elements directly above it.

---

## 🧠 Approach

I used a **bottom-up simulation approach**.

Instead of calculating values using factorials or combinations, the triangle is built row by row using values from the previous row.

### 💡 Key Observation

```txt
First element = 1
Last element = 1
Middle elements = sum of two values from the previous row
```

For example:

```txt
Previous row: [1, 2, 1]

New row:
1
1 + 2 = 3
2 + 1 = 3
1

Result: [1, 3, 3, 1]
```

---

## ⚙️ Algorithm

1. Create a 2D vector named `pascal`.
2. Add the first row `[1]`.
3. Loop from row `1` to `numRows - 1`.
4. Create a new vector called `row`.
5. Add `1` as the first element.
6. Add middle values using the previous row.
7. Add `1` as the last element.
8. Push the completed row into `pascal`.
9. Return `pascal`.

---

## ⏱️ Complexity Analysis

| Type                |   Complexity  | Reason                                               |
| :------------------ | :-----------: | :--------------------------------------------------- |
| ⏳ Time Complexity   | `O(numRows²)` | All values in the triangle are generated.            |
| 💾 Space Complexity | `O(numRows²)` | The returned 2D vector stores the complete triangle. |

---

## ⚠️ Common Mistakes

| Mistake                                      | Fix                                              |
| :------------------------------------------- | :----------------------------------------------- |
| Forgetting to store a completed row          | Use `pascal.push_back(row);`                     |
| Making the first row `[1, 1]`                | Start the triangle with `pascal.push_back({1});` |
| Using incorrect previous-row indices         | Use `pascal[i - 1][j - 1] + pascal[i - 1][j]`    |
| Including boundary values in the middle loop | Keep the loop from `j = 1` to `j < i`            |

---

## 🎯 Key Takeaways

* 🧩 How to use **2D vectors** in C++.
* 🏗️ How to build an output **incrementally**.
* 🔁 How to reuse values from a **previously generated row**.
* 📍 How to handle **boundary elements** separately.
* 🔢 How to avoid **indexing mistakes** in nested loops.
* 📐 How nested loops are used for triangle and matrix-style problems.

---

<p align="center">
  ⭐ If this repository helped you, consider giving it a star!
</p>
