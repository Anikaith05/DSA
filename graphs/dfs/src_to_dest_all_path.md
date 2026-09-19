# 797. All Paths From Source to Target

## 🧠 Approach

Use **DFS + Backtracking** to explore every possible path from node `0` to node `n-1`.

The graph is guaranteed to be a **DAG**, so no `visited` array is needed.

### 🔍 Idea

Maintain a `path` (`ans`) containing the nodes in the **current path**.

```text
        0
       / \
      1   2
      |   |
      3   3
```

DFS explores:

```text
0 → 1 → 3
      ✓ save [0,1,3]

0 → 2 → 3
      ✓ save [0,2,3]
```

### 🔄 Backtracking

The important pattern is:

```text
1. Add node to path
2. Explore its neighbors
3. Remove node from path
```

```cpp
ans.push_back(vertex);

for (auto node : graph[vertex]) {
    dfs(node, graph, ans, result, n);
}

ans.pop_back();
```

The `pop_back()` **undoes the current choice** so the next branch can be explored with a clean path.

### 🎯 Base Case

When we reach `n-1`:

```cpp
if (vertex == n-1) {
    result.push_back(ans);
}
```

We copy the current path into `result`.

There is **no `return` needed** here because we want the final `ans.pop_back()` to execute and backtrack normally.

### 💡 Pattern

```text
DFS + Backtracking

        choose
          ↓
     add node
          ↓
      DFS deeper
          ↓
    explore all
     branches
          ↓
     remove node
       (undo)
```

### ⏱️ Complexity

Let `P` = number of valid paths and `L` = maximum path length.

* **Time:** `O(P × L)`
* **Space:** `O(L)` recursion/path space, excluding the output.
