# N-Queens (Backtracking)

Solves the classic **N-Queens** problem: place `n` queens on an `n x n` chessboard so that no two queens attack each other, and return every distinct valid board.

Each solution is a `vector<string>` where `'Q'` is a queen and `'.'` is an empty square.

## Approach

The solution uses **backtracking, one row at a time**.

1. Start at row `0`.
2. For the current row, try every column `j`.
3. If placing a queen at `(row, j)` is safe (`isValid`), place it and recurse to the next row.
4. If the recursion returns (whether or not it found solutions), remove the queen and try the next column.
5. When `row == n`, all `n` queens have been placed safely, so the board is copied into `answer`.

Because exactly one queen is placed per row, row conflicts can never occur between queens placed by the recursion, which keeps the search space far smaller than trying all `C(n², n)` placements.

## Board initialization

```cpp
vector<string> buffer(n);

for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        buffer[i] += ".";
    }
}
```

- `vector<string> buffer(n)` creates `n` empty strings, one per row.
- The nested loop appends `'.'` `n` times to each row, producing an `n x n` grid of empty squares.
- The result for `n = 4`:

```
....
....
....
....
```

(A shorter equivalent is `vector<string> buffer(n, string(n, '.'))`.)

`buffer` is passed **by value** into `n_queens`, so each recursive call works on its own copy. That is why the `buffer[i][j] = '.'` reset after the recursive call is technically redundant. It keeps the logic correct and readable if you ever switch to passing by reference.

## `isValid(matrix, i, j, n)`

Checks whether a queen can safely be placed at row `i`, column `j`, given the queens already on the board.

### 1. Row and column check

```cpp
for (int k = 0; k < n; k++) {
    if (matrix[k][j] == 'Q' || matrix[i][k] == 'Q') return false;
}
```

- `matrix[k][j]` scans the whole **column** `j`.
- `matrix[i][k]` scans the whole **row** `i`.

### 2. Diagonal and anti-diagonal check

```cpp
for (int k = 0; k < n; k++) {
    for (int q = 0; q < n; q++) {
        if ((abs(k - i) == abs(q - j)) || ((k + q) == (i + j))) {
            if (matrix[k][q] == 'Q') return false;
        }
    }
}
```

Every cell `(k, q)` on the board is examined, and the two conditions identify cells that share a diagonal with `(i, j)`:

| Line | Condition | Idea |
|------|-----------|------|
| **Diagonal** (top-left to bottom-right, `\`) | `abs(k - i) == abs(q - j)` | Moving `d` rows away along a diagonal moves `d` columns away, so the row and column distances are equal. |
| **Anti-diagonal** (top-right to bottom-left, `/`) | `k + q == i + j` | Along a `/` line, row increases while column decreases, so `row + col` stays constant. |

Note that `abs(k - i) == abs(q - j)` actually covers **both** diagonals (it is true for any cell at equal row and column distance), so the `(k + q) == (i + j)` clause is redundant. It is harmless but can be dropped.

If any of these cells holds a `'Q'`, the position is attacked and `isValid` returns `false`.

### Example

For `(i, j) = (2, 1)` on a 4x4 board:

- Anti-diagonal cells have `k + q == 3`: `(0,3)`, `(1,2)`, `(2,1)`, `(3,0)`.
- Diagonal cells have `k - q == 1`: `(1,0)`, `(2,1)`, `(3,2)`.

If a queen sits on any of those, column `1` is rejected for row `2`.

## Complexity

- **`isValid`**: O(n²) because of the full-board scan for diagonals.
- **Overall**: exponential in the worst case, roughly O(n!) pruned by the validity checks, with an extra O(n²) factor per placement attempt and O(n²) per copied board (`buffer` is passed by value).
- **Space**: O(n²) per recursion level for the board copies, depth `n`, plus the stored solutions.

## Possible optimizations

- Only check rows **above** the current row, since later rows are still empty. This reduces the diagonal check from O(n²) to O(n).
- Use boolean arrays or bitmasks for columns, diagonals (`row - col + n - 1`) and anti-diagonals (`row + col`) to make each validity check O(1).
- Pass `buffer` by reference to avoid copying the board on every call.

## Usage

```cpp
Solution s;
vector<vector<string>> result = s.solveNQueens(4);
// result.size() == 2
```

Output for `n = 4`:

```
.Q..      ..Q.
...Q      Q...
Q...      ...Q
..Q.      .Q..
```