# Topological Sort using DFS

## Problem

Given a **Directed Acyclic Graph (DAG)** with `V` vertices and a list of directed edges, return a **topological ordering** of the vertices.

A topological ordering is a linear ordering of vertices such that for every directed edge:

```text
u → v
```

`u` appears before `v` in the ordering.

---

## Approach

We use **Depth First Search (DFS)**.

The key idea is:

> A vertex is added to the ordering **after all of its adjacent vertices have been completely visited**.

This is called **postorder traversal**.

### Steps

1. Build an adjacency list from the given edges.
2. Maintain a `visited` array to avoid processing the same vertex multiple times.
3. Run DFS from every unvisited vertex.
4. During DFS:

   * Mark the current vertex as visited.
   * Visit all its unvisited neighbours.
   * After all neighbours are processed, add the current vertex to `order`.
5. Reverse `order` to obtain the topological ordering.

---

## Why do we reverse the order?

Consider:

```text
0 → 1 → 2
```

DFS starts from `0`:

```text
0
 ↓
1
 ↓
2
```

Vertex `2` finishes first:

```text
order = [2]
```

Then `1`:

```text
order = [2, 1]
```

Then `0`:

```text
order = [2, 1, 0]
```

This is the **reverse topological order**.

Therefore, we reverse it:

```text
[2, 1, 0]
      ↓ reverse
[0, 1, 2]
```

So the final result satisfies:

```text
0 → 1 → 2
```


## Example

### Input

```text
V = 6

Edges:
5 → 0
5 → 2
4 → 0
4 → 1
2 → 3
3 → 1
```

One possible topological ordering is:

```text
5 4 2 3 1 0
```

Another valid ordering may also exist because topological ordering is **not necessarily unique**.

---

## Complexity

Let:

* `V` = number of vertices
* `E` = number of edges

### Time Complexity

```text
O(V + E)
```

Each vertex is visited once and each edge is explored once.

### Space Complexity

```text
O(V + E)
```

The adjacency list requires `O(V + E)` space.

The `visited`, `order`, and recursion stack require `O(V)` additional space.

---

## Key Insight

The most important part of DFS-based topological sorting is:

```cpp
order.push_back(vertex);
```

**after** processing all neighbours.

So remember:

```text
DFS
 ↓
Visit neighbours first
 ↓
Add vertex after DFS
 ↓
Reverse the resulting order
 ↓
Topological Sort
```

### Pattern to Remember

```cpp
dfs(node):
    visited[node] = true

    for neighbour:
        if not visited:
            dfs(neighbour)

    order.push_back(node)
```

Then:

```cpp
reverse(order.begin(), order.end());
```

This is essentially **DFS postorder + reverse**.
