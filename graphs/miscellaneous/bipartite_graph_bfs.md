# Bipartite Graph — BFS Coloring

## Problem

Given an undirected graph, determine whether it is **bipartite**.

A graph is bipartite if we can divide all vertices into **two groups** such that no two adjacent vertices belong to the same group.

Another way to think about it:

> We should be able to color every node using two colors so that adjacent nodes always have different colors.
---

## Approach

We use **BFS + 2-coloring**.

### Color Representation

We maintain a `color` array:

```cpp
vector<int> color(v, 0);
```

Each value represents:

* `0` → Node is uncolored
* `1` → Node has color 1
* `2` → Node has color 2

---

## Algorithm

### 1. Handle every connected component

The graph may contain multiple disconnected components.

Therefore, we loop through every vertex:

```cpp
for(int i = 0; i < v; i++){
    if(color[i] == 0){
        ...
    }
}
```

If a node is uncolored, it means we have found a new connected component.

We start BFS from that node.

---

### 2. Give the starting node a color

```cpp
q.push(i);
color[i] = 1;
```

The starting node gets color `1`.

---

### 3. Perform BFS

While the queue is not empty:

```cpp
int vertex = q.front();
q.pop();
```

We examine all neighbors of the current vertex:

```cpp
for(auto node : graph[vertex]){
```

---

### 4. Check for a conflict

If the neighbor already has the **same color** as the current vertex:

```cpp
if(color[node] == color[vertex]){
    return false;
}
```

Then the graph cannot be bipartite.

For example:

```text
1 ---- 2
|      |
+------+
```

If both endpoints of an edge have the same color, the bipartite condition is violated.

---

### 5. Color uncolored neighbors

If the neighbor has not been colored yet:

```cpp
else if(color[node] == 0){
    q.push(node);

    if(color[vertex] == 1)
        color[node] = 2;

    if(color[vertex] == 2)
        color[node] = 1;
}
```

We always assign the **opposite color** to the neighbor.

So:

```text
Current Node     Neighbor
    1      --->      2
    2      --->      1
```

This guarantees that every edge we process connects nodes of different colors.

---

## Why Does This Work?

Suppose we start with:

```text
A = 1
```

Every neighbor of `A` must have color `2`.

Then every neighbor of those nodes must have color `1`.

This continues throughout the connected component.

If we eventually encounter an edge where:

```text
color[u] == color[v]
```

then two adjacent vertices require the same color.

Therefore, the graph is **not bipartite**.

If we finish BFS for every connected component without finding such a conflict, the graph is bipartite.

---

## Example

Consider:

```text
0 ---- 1
|      |
|      |
3 ---- 2
```

Start with:

```text
color[0] = 1
```

Then:

```text
color[1] = 2
color[3] = 2
```

From node `1`:

```text
color[2] = 1
```

From node `3`, node `2` is already color `1`, which is different from `3`'s color `2`.

So there is no conflict.

Therefore:

```text
Graph is Bipartite
```

---

## Disconnected Graphs

We cannot simply start BFS from node `0`.

The graph may look like:

```text
0 ---- 1        2 ---- 3
```

There are two separate connected components.

Therefore, we use:

```cpp
for(int i = 0; i < v; i++)
```

and start BFS whenever:

```cpp
color[i] == 0
```

This ensures **every connected component is checked**.

---

## Complexity

Let:

* `V` = number of vertices
* `E` = number of edges

### Time Complexity

```text
O(V + E)
```

Every vertex is processed once, and every edge is examined while traversing the adjacency list.

### Space Complexity

```text
O(V)
```

The `color` array and BFS queue require at most `O(V)` additional space.

---

## Key Pattern to Remember

The important pattern is:

```text
BFS
 ↓
Color starting node
 ↓
For every neighbor:
    ├── uncolored → give opposite color + push
    └── already colored
            ↓
       same color?
        ├── YES → false
        └── NO  → continue
```

### Core Idea

> **Bipartite graph = graph that can be 2-colored such that every edge connects different colors.**

For an undirected graph, **BFS/DFS + 2-coloring** is the standard approach.
