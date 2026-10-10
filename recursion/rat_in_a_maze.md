# 🐀 Rat in a Maze: Mistakes Review

A visual recap of what went wrong (and what's still wrong) in the backtracking solution.

---

## 🗺️ The problem in one picture

Find every path from the top-left `S` to the bottom-right `E`, moving `U`, `D`, `L`, `R` through cells marked `1`, never visiting a cell twice. Return the paths in **lexicographic order**.

```
 S  0  0  0          S = (0,0)
 1  1  0  1          E = (n-1,n-1)
 1  1  0  0          1 = open, 0 = wall
 0  1  1  E
```

Expected output: `["DDRDRR", "DRDDRR"]`

---

## 📊 Scoreboard

| # | Mistake | Status |
|---|---------|--------|
| 1 | Direction order was not alphabetical | ✅ Fixed in your latest code |
| 2 | Returns `{""}` when the start is blocked | ❌ **Still in your code** |
| 3 | `buffer.pop_back()` does nothing useful | ⚠️ Harmless, but remove it |
| 4 | Redundant bounds checks | ⚠️ Cosmetic |

---

## ❌ Mistake 1: Wrong direction order (fixed)

Paths come out in the order you **explore** directions. So the exploration order must be alphabetical.

```
Alphabetical:   D  <  L  <  R  <  U
```

| Attempt | Your order | Verdict |
|---------|-----------|---------|
| 1 | `D, U, R, L` | ❌ `U` before `R` and `L`; `R` before `L` |
| 2 | `U, D, L, R` | ❌ `U` first, but `U` should be last |
| 3 | `D, L, R, U` | ✅ Correct |

Why it matters: if both a `U`-first path and a `D`-first path reach the goal, `"D..."` must appear first in the answer. Exploring `U` first would put `"U..."` first and fail the judge.

---

## ❌ Mistake 2: Blocked start returns the wrong thing (still present)

```diff
  vector<string> ratInMaze(vector<vector<int>>& maze) {
      vector<string> answer;
-     if(maze[0][0]==0) return {""};
+     if(maze[0][0]==0) return answer;     // or: return {};
```

`{""}` is a vector holding **one empty string**, which means "there is one path and it is empty". The correct answer for "no path" is an **empty vector**: `[]`.

```
 expected:  []          ← zero paths
 yours:     [""]        ← one path, of length 0   ✗
```

Tip: you can even delete this `if` entirely. When `maze[0][0] == 0`, your neighbours check `maze[next] == 1`, so you'd only ever step into open cells. But then also keep in mind `n == 1` edge cases, so the early return is a fine, explicit guard as long as it returns an empty vector.

---

## ⚠️ Mistake 3: `buffer.pop_back()` is dead weight

```cpp
void calc_all_routes(..., string buffer, int i, int j)   // ← by VALUE
```

Every recursive call gets **its own copy** of `buffer`. Appending to the copy never changes the caller's string, so there's nothing to undo.

```
call A: buffer = "D"
   └─ call B receives a COPY "D", appends "R" → "DR"
      when B returns, A's buffer is still "D"   ← no pop needed
```

Two valid styles, pick one:

| Style | `buffer` parameter | Needs `pop_back()`? |
|-------|-------------------|---------------------|
| Copy (yours) | `string buffer` | ❌ No |
| Shared | `string &buffer` | ✅ Yes |

Note that your **`maze[i][j] = 1` restore is required**, because `maze` *is* passed by reference. Keep that one.

---

## ⚠️ Mistake 4: Redundant bounds checks

```cpp
if(i+1<n && i+1>=0 && j<n && j>=0 && maze[i+1][j]==1)
//          ^^^^^^   ^^^^^^^^^^^^
//          always true / already guaranteed
```

`i` and `j` are always valid when the function is called, so only the **neighbour** needs checking:

```cpp
if(i+1<n && maze[i+1][j]==1)    // D
if(j-1>=0 && maze[i][j-1]==1)   // L
if(j+1<n && maze[i][j+1]==1)    // R
if(i-1>=0 && maze[i-1][j]==1)   // U
```

---

## ✅ What you got right

- Mark the cell visited → recurse → **unmark** (the core of backtracking).
- Base case at `(n-1, n-1)` pushes the path.
- Passing `maze` and `answer` by reference.
- Fixing the direction order after the hint.

---

## 🧾 Cleaned-up version

```cpp
class Solution {
public:
    void solve(vector<vector<int>>& maze, vector<string>& answer,
               string path, int i, int j) {
        int n = maze.size();
        if (i == n-1 && j == n-1) {
            answer.push_back(path);
            return;
        }

        maze[i][j] = 0;                                   // mark visited

        if (i+1 < n  && maze[i+1][j] == 1) solve(maze, answer, path + "D", i+1, j);
        if (j-1 >= 0 && maze[i][j-1] == 1) solve(maze, answer, path + "L", i, j-1);
        if (j+1 < n  && maze[i][j+1] == 1) solve(maze, answer, path + "R", i, j+1);
        if (i-1 >= 0 && maze[i-1][j] == 1) solve(maze, answer, path + "U", i-1, j);

        maze[i][j] = 1;                                   // unmark (backtrack)
    }

    vector<string> ratInMaze(vector<vector<int>>& maze) {
        vector<string> answer;
        if (maze[0][0] == 0) return answer;               // empty vector, not {""}
        solve(maze, answer, "", 0, 0);
        return answer;
    }
};
```

---

## 🧠 Takeaways

1. **Output order = exploration order.** Decide it before you write the branches.
2. **"No answer" and "an empty answer" are different.** `[]` is not `[""]`.
3. **Know what is copied and what is shared.** Undo only the shared state (`maze`), never the copied state (`buffer`).
4. **Check the neighbour, not the cell you're standing on.**