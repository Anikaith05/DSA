# Undirected Graph Cycle Detection using DFS

## Approach

We use **DFS + Parent Tracking** to detect whether an undirected graph contains a cycle.

### Core Idea

While performing DFS:

```text
If neighbour is already visited
AND
neighbour is NOT the parent of the current vertex

        ↓

    CYCLE EXISTS
```

The parent check is necessary because an undirected edge exists in both directions.

---

## Example — No Cycle

```text
      0
      |
      1
     / \
    2   3
```

DFS:

```text
0 → 1 → 2
    |
    └──→ 3
```

When we are at `1`, we see `0`.

```text
0 is already visited
0 is the parent of 1
```

Therefore, this is **not a cycle**.

---

## Example — Cycle

```text
      0
     / \
    1---2
```

DFS:

```text
0 → 1 → 2
    ↑   |
    └───┘
```

When DFS reaches `2`, it finds `0` already visited.

But:

```text
0 != parent[2]
```

Therefore, a **cycle exists**.

---

## Pseudocode

### DFS

```text
DFS(vertex):

    mark vertex as visited

    for every neighbour of vertex:

        if neighbour == vertex:
            cycle found
            return

        if neighbour is visited
           AND neighbour != parent[vertex]:

            cycle found
            return

        if neighbour is not visited:

            parent[neighbour] = vertex

            DFS(neighbour)
```

### Complete Algorithm

```text
isCycle(V, edges):

    build adjacency list

    create visited array

    cycle = false

    for every vertex:

        if vertex is not visited:

            parent[vertex] = -1

            DFS(vertex)

    return cycle
```

---

## Why Do We Need the Parent?

Consider:

```text
0 ---- 1
```

DFS goes:

```text
0 → 1
```

Since the graph is undirected, `1` also sees `0`:

```text
1 → 0
```

But this does **not** mean there is a cycle.

`0` is simply the parent of `1`.

Therefore:

```text
Visited + Parent
        ↓
    Normal Edge

Visited + NOT Parent
        ↓
      Cycle
```

---

## Disconnected Graph

The graph may contain multiple components:

```text
0 --- 1       2 --- 3
                \
                 4
```

Therefore, DFS must be started from **every unvisited vertex**.

```text
for every vertex:

    if vertex is not visited:

        start DFS
```

This ensures that every connected component is checked.

---

## Complexity

### Time Complexity

```text
O(V + E)
```

Every vertex and edge is processed at most a constant number of times.

### Space Complexity

```text
O(V + E)
```

* `O(V)` for the visited/parent information and DFS recursion.
* `O(V + E)` for the adjacency list.

Where:

* `V` = number of vertices
* `E` = number of edges
