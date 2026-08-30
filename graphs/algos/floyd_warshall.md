# Floyd–Warshall Algorithm

## Problem

Given a weighted graph represented using an adjacency matrix `dist`, find the shortest distance between **every pair of vertices**.

The graph may contain **negative edge weights**, but it should not contain a negative cycle.

---

## Approach

Floyd–Warshall is an **All-Pairs Shortest Path** algorithm.

For every pair of nodes:

```text
i → j
```

we check whether going through an intermediate node `k` gives a shorter path:

```text
i → k → j
```

The transition is:

```text
dist[i][j] = min(
    dist[i][j],
    dist[i][k] + dist[k][j]
)
```

### Meaning

* `i` → Source node
* `j` → Destination node
* `k` → Intermediate node

The outer loop iterates through every node and allows that node to be used as an intermediate node.

---

## Algorithm

```text
for every intermediate node k:
    for every source node i:
        for every destination node j:

            if i → k does not exist OR k → j does not exist:
                continue

            dist[i][j] =
                min(dist[i][j],
                    dist[i][k] + dist[k][j])
```


## Why Check for `1e8`?

Here, `1e8` represents infinity (`INF`).

If:

```text
dist[i][k] = INF
```

there is no path from:

```text
i → k
```

Similarly, if:

```text
dist[k][j] = INF
```

there is no path from:

```text
k → j
```

Therefore, we cannot form:

```text
i → k → j
```

So we skip that case:

```cpp
if (dist[i][k] == 1e8 || dist[k][j] == 1e8)
    continue;
```

---

## Example

Suppose:

```text
0 → 1 = 4
1 → 2 = 3
0 → 2 = 10
```

Initially:

```text
dist[0][2] = 10
```

When `k = 1`, we check:

```text
0 → 1 → 2

4 + 3 = 7
```

Since:

```text
7 < 10
```

we update:

```text
dist[0][2] = 7
```

---

## Time Complexity

There are three nested loops:

```text
O(V³)
```

where `V` is the number of vertices.

---

## Space Complexity

The algorithm modifies the given distance matrix in-place:

```text
O(1) extra space
```

The input matrix itself requires:

```text
O(V²)
```

space.

---

## Key Points

* Finds shortest paths between **all pairs of vertices**.
* Uses every vertex as a possible intermediate node.
* Supports **negative edge weights**.
* Does **not** work properly when a reachable negative cycle makes shortest paths undefined.
* `k` must be the **outermost loop**.
* Transition:

```cpp
dist[i][j] = min(
    dist[i][j],
    dist[i][k] + dist[k][j]
);
```

## Core Idea

> For every pair `(i, j)`, check whether using node `k` in between creates a shorter path.

```text
Current path:

i ─────────→ j


Possible better path:

i ───→ k ───→ j
```
