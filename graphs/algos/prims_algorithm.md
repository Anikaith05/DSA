# 🌳 Minimum Spanning Tree using Prim's Algorithm

## 💡 Approach

We use **Prim's Algorithm** to find the Minimum Spanning Tree (MST).

An MST:

* Connects all vertices
* Contains no cycles
* Has minimum total edge weight
* Contains exactly `V - 1` edges

---

## 📊 Example

```text
        2
    0 ------- 1
    | \       |
   6|  \3     |5
    |   \     |
    2 ------- 3
        4
```

Possible MST:

```text
        2
    0 ------- 1

      \
       \3
        \
         3
        /
       /4
      2
```

Total weight:

```text
2 + 3 + 4 = 9
```

---

## ⚙️ How the Algorithm Works

### 1️⃣ Build an Adjacency List

Each edge is stored as:

```text
{neighbour, weight}
```

Since the graph is undirected:

```cpp
adj[u].push_back({v, weight});
adj[v].push_back({u, weight});
```

---

### 2️⃣ Start from Node `0`

```text
Visited: {0}

Push all edges from 0 into the Min-Heap
```

Example:

```text
PQ
↓
(1,2)  (3,3)  (2,6)
```

---

### 3️⃣ Pick the Minimum Weight Edge

```text
PQ
↓
(1,2)  ← Pick this
(3,3)
(2,6)
```

Add node `1` to the MST:

```text
Visited: {0,1}
Weight: 2
```

Then push edges from node `1`.

---

### 4️⃣ Repeat

Always:

```text
       Min Heap
          ↓
Pick minimum edge
          ↓
Is vertex visited?
     ↙         ↘
   Yes         No
    ↓           ↓
  Skip       Add to MST
                  ↓
          Push its neighbours
```

---

## 📝 Pseudocode / Algorithm Steps

1. Create an **adjacency list** from the given edges.
2. Create a `visited` array and mark all vertices as unvisited.
3. Create a **Min-Heap (Priority Queue)** that stores `{vertex, edgeWeight}`.
4. Start from vertex `0` and mark it as visited.
5. Push all neighbours of vertex `0` into the Min-Heap.
6. While the Min-Heap is not empty:

   * Remove the edge with the **minimum weight**.
   * If its destination vertex is already visited, skip it.
   * Otherwise:

     * Mark the vertex as visited.
     * Add the edge weight to the MST weight.
     * Push all edges leading to its unvisited neighbours into the Min-Heap.
7. When all vertices have been visited, return the total MST weight.

---

## 🧠 Priority Queue

The priority queue stores:

```text
{vertex, edgeWeight}
```

Example:

```cpp
{3, 5}
```

means:

```text
Vertex = 3
Weight = 5
```

The custom comparator creates a **Min-Heap based on edge weight**:

```cpp
class Compare{
public:
    bool operator()(pair<int,int> a, pair<int,int> b){
        return a.second > b.second;
    }
};
```

---

## 🔄 Complete Flow

```text
Start at 0
    ↓
Mark 0 visited
    ↓
Push neighbours into PQ
    ↓
Take minimum weight edge
    ↓
Already visited?
   ↙       ↘
 Yes       No
 ↓          ↓
Skip    Add weight
             ↓
      Mark vertex visited
             ↓
      Push its neighbours
             ↓
          Repeat
```

---

## ⏱️ Complexity

| Complexity | Value        |
| ---------- | ------------ |
| **Time**   | `O(E log V)` |
| **Space**  | `O(V + E)`   |

---

## 🔑 Key Idea

> Keep expanding the MST by always selecting the **minimum-weight edge leading to an unvisited vertex**.
