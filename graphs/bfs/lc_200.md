# 200. Number of Islands

## Problem

Given an `m x n` grid containing:

- `'1'` → land
- `'0'` → water

return the number of islands.

An island is a group of horizontally or vertically connected land cells.

---

## Core Idea

This is a **BFS on a grid** problem.

At first, it may seem like we need to convert the grid into an adjacency matrix/list before doing BFS.

**We don't.**

The grid itself already represents the graph.

For every cell, its possible neighbours are simply its:

```text
        UP
        ↑
        |
LEFT ← CELL → RIGHT
        |
        ↓
       DOWN
```

So instead of building an adjacency matrix, we generate the four neighbours of a cell using `dr` and `dc`.

---

## 1. `dr` and `dc`

We use:

```cpp
vector<int> dr = {-1, 0, 1, 0};
vector<int> dc = {0, -1, 0, 1};
```

`dr` = change in the **row**

`dc` = change in the **column**

Together they represent:

| `k` | `dr[k]` | `dc[k]` | Direction |
|---|---:|---:|---|
| 0 | -1 | 0 | Up |
| 1 | 0 | -1 | Left |
| 2 | 1 | 0 | Down |
| 3 | 0 | 1 | Right |

For a current cell `(i, j)`:

```cpp
int nr = i + dr[k];
int nc = j + dc[k];
```

This gives each of its four possible neighbours.

### Important

`dr` and `dc` have size **4**, not `m * n * 4`.

```text
Grid        → m × n cells
dr / dc     → 4 possible directions
```

The same four directions are reused for every cell.

---

## 2. How Do We Find Each Island?

We scan the entire grid.

```text
for every cell:
    if cell == '1':
        we found a new island
        run BFS from this cell
```

For example:

```text
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1
```

When we encounter the first `1`:

```text
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1
↑
start BFS
```

BFS visits the entire connected component:

```text
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1

████
██
```

After that island has been visited, the scan continues.

The next unvisited `1` starts another BFS, so the island count increases again.

---

## 3. We Don't Need a Separate `visited` Array

A useful trick in this problem is to use the grid itself as the visited array.

Whenever we visit land:

```cpp
grid[i][j] = '0';
```

This means:

```text
'1' → unvisited land
'0' → water OR already visited land
```

So the grid is doing two jobs:

```text
             GRID
              │
       ┌──────┴──────┐
       ↓             ↓
    original       visited
     state          state
```

This saves us from creating:

```cpp
vector<vector<int>> visited;
```

---

## 4. Why Mark as Visited When Pushing?

When we discover a neighbouring land cell:

```cpp
if (... && grid[nr][nc] == '1') {
    q.push({nr, nc});
    grid[nr][nc] = '0';
}
```

We immediately mark it as visited.

This is important because otherwise the same cell could be discovered multiple times before it gets popped from the queue.

The pattern is:

```text
DISCOVER
   ↓
push into queue
   ↓
mark visited
   ↓
later pop from queue
```

---

## 5. BFS Process Visually

Suppose:

```text
1 1 0
1 1 0
0 0 1
```

Start at `(0,0)`.

### Step 1

```text
1 1 0
1 1 0
0 0 1
↑
start
```

Push `(0,0)` and mark it visited:

```text
0 1 0
1 1 0
0 0 1
```

### Step 2

Pop `(0,0)`.

Check its four directions:

```text
      (-1,0)
         ↑
(-0,1) ← (0,0) → (0,1)
         ↓
       (1,0)
```

Valid land neighbours:

```text
(0,1)
(1,0)
```

Push them into the queue and mark them as visited.

### Step 3

BFS continues doing the same thing.

Eventually:

```text
0 0 0
0 0 0
0 0 1
```

The entire first island has been consumed.

Then the outer loop eventually reaches `(2,2)`:

```text
0 0 0
0 0 0
0 0 1
      ↑
   new island
```

So the count increases.

---

## 6. Why `count++` Happens Once Per BFS

The key observation is:

> Every time we start a BFS from an unvisited land cell, we have found one new island.

Therefore:

```cpp
if (grid[i][j] == '1') {
    bfs_traversal(grid, i, j, count);
}
```

and after BFS finishes:

```cpp
count++;
```

works because that BFS has completely explored exactly one island.

A slightly cleaner design is to increment before calling BFS:

```cpp
if (grid[i][j] == '1') {
    count++;
    bfs_traversal(grid, i, j);
}
```

Then BFS only has one responsibility:

> **Visit the entire island.**

---

## 7. Mental Model to Remember

For grid BFS problems, think:

```text
                 GRID
                   │
                   ↓
             Current cell
                   │
          ┌────────┼────────┐
          ↓        ↓        ↓
        Check 4 possible directions
                   │
                   ↓
          Is neighbour valid?
                   │
             ┌─────┴─────┐
             ↓           ↓
            YES           NO
             │
             ↓
        Add to queue
             │
             ↓
       Mark as visited
```

And for Number of Islands:

```text
Scan grid
   ↓
Find unvisited '1'
   ↓
count++
   ↓
BFS
   ↓
Visit entire connected island
   ↓
Continue scanning
   ↓
Find next unvisited '1'
```

### Most important takeaway

```text
Normal graph:
Node → adjacency list → neighbours

Grid graph:
Cell → dr/dc → neighbours
```

You **do not need to construct an adjacency matrix/list** for this type of grid problem.

---

## Complexity

Let:

```text
m = number of rows
n = number of columns
```

### Time

```text
O(m × n)
```

Every cell is visited at most once, and we check only 4 directions for each cell.

### Space

```text
O(m × n)
```

The BFS queue can contain up to `m × n` cells in the worst case.

No separate `visited` matrix is required because we modify the grid itself.
