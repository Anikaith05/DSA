# 🧩 Set Matrix Zeroes

> If any cell is `0`, make its entire row and column `0` using **O(1)** extra space.

---

## 💡 Approach: Use the Matrix as Markers

Instead of storing rows and columns in extra arrays, use:

```txt
matrix[i][0] → row i should become zero
matrix[0][j] → column j should become zero
```

The first column stores **row markers**, and the first row stores **column markers**.

---

## ⚠️ First Row and First Column

Since the first row and column are also used as markers, store whether they originally contain a zero.

```cpp
bool firstRowZero = false;
bool firstColZero = false;
```

```txt
firstRowZero → zero the entire first row at the end
firstColZero → zero the entire first column at the end
```

---

## 🧠 Algorithm

### 1️⃣ Check the First Row and Column

Before changing the matrix, check whether the first row or first column already contains a `0`.

```txt
If first row has 0 → firstRowZero = true
If first column has 0 → firstColZero = true
```

---

### 2️⃣ Mark Required Rows and Columns

Traverse the matrix starting from `(1, 1)`.

If:

```cpp
matrix[i][j] == 0
```

mark its row and column:

```cpp
matrix[i][0] = 0; // Mark row i
matrix[0][j] = 0; // Mark column j
```

---

### 3️⃣ Zero Marked Rows

For every row `i`:

```cpp
if (matrix[i][0] == 0)
```

set all elements in that row to `0`.

---

### 4️⃣ Zero Marked Columns

For every column `j`:

```cpp
if (matrix[0][j] == 0)
```

set all elements in that column to `0`.

---

### 5️⃣ Handle the First Row and Column

Finally:

```txt
If firstRowZero is true → zero the first row
If firstColZero is true → zero the first column
```

They must be handled last because they store the markers.

---

## 🔍 Example

### Input

```txt
1  1  1
1  0  1
1  1  1
```

### After Marking

```txt
1  0  1
0  0  1
1  1  1
```

```txt
matrix[1][0] = 0 → zero row 1
matrix[0][1] = 0 → zero column 1
```

### Output

```txt
1  0  1
0  0  0
1  0  1
```

---

## ⏱️ Complexity

| Complexity | Value      |
| ---------- | ---------- |
| ⏱️ Time    | `O(m × n)` |
| 🧠 Space   | `O(1)`     |
