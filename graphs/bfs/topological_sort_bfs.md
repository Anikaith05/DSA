# 🔀 Topological Sort using BFS — Kahn's Algorithm

## 🧠 Idea

Topological sorting gives an ordering of vertices in a **DAG (Directed Acyclic Graph)** such that:

```text
For every edge u → v

u comes before v
```

Kahn's Algorithm uses **BFS + Indegree**.

> A vertex with `indegree = 0` has no remaining dependencies, so it is safe to process.

---

## ⚙️ Algorithm

1. Build the adjacency list.
2. Calculate the indegree of every vertex.
3. Put every vertex with `indegree = 0` into a queue.
4. While the queue is not empty:

   * Remove a vertex.
   * Add it to the topological ordering.
   * Visit all its neighbours.
   * Decrease their indegree.
   * If a neighbour's indegree becomes `0`, add it to the queue.
5. Return the ordering.

---

## 📝 Pseudocode

```text
Kahn's Algorithm:

create adjacency list
create indegree array

for every edge u → v:
    add v to adj[u]
    indegree[v]++

create queue

for every vertex v:
    if indegree[v] == 0:
        push v into queue

while queue is not empty:

    v = pop from queue
    add v to answer

    for every neighbour node of v:

        indegree[node]--

        if indegree[node] == 0:
            push node into queue

return answer
```

---

## 📌 Example

```text
        0
       / \
      ↓   ↓
      3   2
      ↓  ↙
      1
      ↓
      4

5 ─────→ 1
 \──────→ 4
```

Initial indegrees:

```text
Vertex:    0  1  2  3  4  5
Indegree:  0  3  0  2  2  0
```

Therefore:

```text
indegree = 0
     ↓
   0, 2, 5
     ↓
   Queue
┌───┬───┬───┐
│ 0 │ 2 │ 5 │
└───┴───┴───┘
```

---

## 🔄 How BFS Progresses

Suppose we process `2`.

```text
2 → 3
2 → 1
```

Decrease their indegrees:

```text
indegree[3]--
indegree[1]--
```

If:

```text
indegree[3] == 0
```

then:

```text
3 → Queue
```

The same process continues.

```text
┌───────────────┐
│ indegree = 0  │
└───────┬───────┘
        ↓
      Queue
        ↓
   Process node
        ↓
 Decrease neighbours'
    indegrees
        ↓
   indegree == 0?
      /     \
    YES      NO
     ↓        ↓
  Queue     Ignore
```


## ⏱️ Complexity

```text
Time  : O(V + E)
Space : O(V + E)
```

---

## ⭐ Remember

```text
Calculate Indegree
        ↓
Indegree 0 → Queue
        ↓
      BFS
        ↓
Process vertex
        ↓
Decrease neighbour indegree
        ↓
Indegree becomes 0?
        ↓
      Queue
```

> **Kahn's Algorithm = BFS + Indegree.**

The indegree tells us **which vertices are ready to be processed**.
