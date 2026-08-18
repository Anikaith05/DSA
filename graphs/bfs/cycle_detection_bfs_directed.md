# Kahn's Algorithm — Directed Graph Cycle Detection

## Problem

Given a **directed graph** with `V` vertices and a list of directed edges, determine whether the graph contains a cycle.

---

## Approach

We use **Kahn's Algorithm**, which is a BFS-based approach to **topological sorting**.

### Key Idea

For every node, calculate its **indegree**:

> `indegree[node]` = number of edges coming into that node.

Any node with:

```cpp
indegree[node] == 0
```

has no dependency, so it can be processed first.

We put **all indegree-0 nodes** into a queue.

Then:

1. Pop a node from the queue.
2. Count it as processed.
3. Visit all its outgoing neighbours.
4. Remove the current node's edge from each neighbour by decreasing its indegree.
5. If a neighbour's indegree becomes `0`, push it into the queue.
6. Continue until the queue is empty.

Finally:

```cpp
count == V
```

means every node was processed, so there is **no cycle**.

```cpp
count < V
```

means some nodes could never reach indegree `0`, which means they are part of a cycle.

Therefore:

```cpp
return count != V;
```


## Example

Consider:

```text
0 → 1
1 → 2
2 → 3
```

Indegrees:

```text
0 : 0
1 : 1
2 : 1
3 : 1
```

Initially:

```text
Queue: [0]
```

Process `0`:

```text
indegree[1] = 0
Queue: [1]
```

Process `1`:

```text
indegree[2] = 0
Queue: [2]
```

Process `2`:

```text
indegree[3] = 0
Queue: [3]
```

Process `3`.

Therefore:

```text
count = 4
V = 4
```

So:

```cpp
count == V
```

No cycle exists.

---

## Cyclic Example

```text
0 → 1
1 → 2
2 → 0
```

Indegrees:

```text
0 : 1
1 : 1
2 : 1
```

There is **no node with indegree 0**.

Therefore:

```text
Queue: []
count: 0
```

Since:

```text
count < V
```

the graph contains a cycle.

---

## Why `count != V` Detects a Cycle

Imagine:

```text
A → B → C
↑       ↓
└───────┘
```

Every node in the cycle has at least one incoming edge from another node in the cycle.

Therefore, none of them can become:

```text
indegree == 0
```

Kahn's algorithm cannot process them.

So:

```text
number of processed nodes < V
```

which proves that a cycle exists.

---

## Important Mistake to Avoid

Do **not** do this:

```cpp
for(int i = 0; i < V; i++){
    queue<int> q;
    q.push(i);
}
```

Kahn's algorithm does **not** perform a separate BFS from every vertex.

Instead:

```cpp
queue<int> q;

for(int i = 0; i < V; i++){
    if(indegree[i] == 0){
        q.push(i);
    }
}
```

There is **one queue and one BFS**.

All initially independent nodes are placed into the queue together.

---

## Relationship with Topological Sort

Kahn's algorithm was originally useful here because it performs a **topological-sort-style process**.

For a DAG:

```text
count == V
```

and a valid topological ordering can be produced.

For a graph containing a cycle:

```text
count < V
```

and a complete topological ordering is impossible.

Therefore:

```text
Directed Graph
      ↓
Kahn's Algorithm
      ↓
Can we process all V nodes?
      ↓
 ┌───────────────┐
 │               │
Yes             No
 │               │
DAG          Cycle exists
```

---

## Complexity

Let:

* `V` = number of vertices
* `E` = number of edges

### Time Complexity

```text
O(V + E)
```

Every vertex is pushed/popped from the queue at most once, and every edge is processed once.

### Space Complexity

```text
O(V + E)
```

because of:

* adjacency list → `O(V + E)`
* indegree array → `O(V)`
* queue → `O(V)`

---

## Pattern to Remember

For **Kahn's Algorithm / Directed Cycle Detection**:

```text
1. Build adjacency list
2. Calculate indegree
3. Push ALL indegree-0 nodes
4. BFS
5. Decrease neighbour indegrees
6. Push neighbour when indegree becomes 0
7. Count processed nodes
8. count != V → cycle
```

### Core intuition

> **A DAG can eventually reduce every node's indegree to 0. A cycle cannot.**
