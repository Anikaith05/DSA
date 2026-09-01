# 🌳 Kruskal's Algorithm - Minimum Spanning Tree

## 💡 Approach

We use **Kruskal's Algorithm** along with **Disjoint Set Union (DSU)** to find the **Minimum Spanning Tree (MST)** of a weighted graph.

An MST:

* ✅ Connects all vertices
* ✅ Contains no cycles
* ✅ Has exactly `V - 1` edges
* ✅ Has the minimum possible total edge weight

---

## 📊 Example

```text
          2
     0 -------- 1
     | \        |
   6 |  \ 3     | 5
     |   \      |
     2 -------- 3
          4
```

### Edges sorted by weight:

```text
(0,1,2)
(0,3,3)
(2,3,4)
(1,3,5)
(0,2,6)
```

Kruskal's algorithm processes edges from the **smallest weight to the largest**.

---

## 🔄 How It Works

```text
Take smallest edge
        ↓
Are the vertices in different components?
       ↙          ↘
     YES           NO
      ↓             ↓
 Add edge       Skip edge
      ↓             ↓
 Union sets     (Would form cycle)
```

---

## 🧠 Role of DSU

Initially, every vertex belongs to its own set:

```text
0    1    2    3
```

After adding edge `(0,1)`:

```text
0 ─── 1      2      3
```

After adding edge `(0,3)`:

```text
    1
    |
0 ─── 3      2
```

DSU helps us check:

> ❓ Will adding this edge create a cycle?

If:

```cpp
find(u) == find(v)
```

Both vertices already belong to the same component, so adding the edge would create a **cycle**.

Otherwise:

```cpp
find(u) != find(v)
```

We safely add the edge to the MST.

---

# 📝 Pseudocode (Steps in English)

### Step 1

Put all edges into a **min-priority queue**, sorted by their weight.

### Step 2

Initialize DSU such that every vertex is its own parent.

```text
parent[i] = i
```

### Step 3

Take the edge with the minimum weight from the priority queue.

### Step 4

Find the ultimate parents of both vertices.

### Step 5

If both vertices belong to different components:

* Add the edge weight to the MST weight.
* Union the two components.

### Step 6

If both vertices already belong to the same component:

* Skip the edge because it would form a cycle.

### Step 7

Repeat until all edges are processed.

---

## ⚙️ Core Logic

```cpp
if(find(u, parent) != find(v, parent)) {
    mst_wt += wt;
    unioni(u, v, parent);
}
```

This ensures that:

```text
Only edges that DON'T create cycles
are added to the MST.
```

---

## ⏱️ Time Complexity

### Priority Queue Operations

For `E` edges:

```text
O(E log E)
```

### DSU Operations

Approximately:

```text
O(E)
```

without path compression/rank optimizations, the theoretical worst case can be higher.

### Overall

```text
O(E log E)
```

---

## 📦 Space Complexity

```text
O(V + E)
```

* `O(V)` → Parent array
* `O(E)` → Priority queue

---

## 🚀 Summary

```text
Sort edges by weight
        ↓
Pick smallest edge
        ↓
Check if it forms a cycle
        ↓
NO  → Add to MST
YES → Skip
        ↓
Repeat
```

**Kruskal's Algorithm = Greedy edge selection + DSU for cycle detection.**
