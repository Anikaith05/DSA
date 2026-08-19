# Bipartite Graph — DFS Approach

## 1. Problem

Given an **undirected graph**, determine whether it is **bipartite**.

A graph is bipartite if we can divide all its vertices into **two groups** such that no two vertices connected by an edge belong to the same group.

Another way to think about it:

> We should be able to color every vertex using only **2 colors**, such that every pair of adjacent vertices has different colors.

---

## 2. Core Idea

We use **DFS + 2-coloring**.

We maintain a `color` array:

```cpp
vector<int> color(v, 0);
```

Each value has a meaning:

```text
0 → Uncolored
1 → Color 1
2 → Color 2
```

When we visit a vertex:

* If it has color `1`, all its neighbors must have color `2`.
* If it has color `2`, all its neighbors must have color `1`.

If we ever find an edge connecting two vertices having the **same color**, the graph is **not bipartite**.

---

## 3. Why Do We Need DFS?

Suppose we start at vertex `0`.

We assign:

```text
color[0] = 1
```

Then we visit all its neighbors and assign them color `2`.

Then we visit their neighbors and assign them color `1`.

This continues throughout the connected component.

For example:

```text
0 ---- 1
|      |
|      |
3 ---- 2
```

Coloring can proceed as:

```text
0 → 1
1 → 2
2 → 1
3 → 2
```

Every edge connects vertices of different colors, so the graph is bipartite.

---

## 4. DFS Function

The DFS function is:

```cpp
void dfs_traversal(
    vector<vector<int>>& graph,
    int vertex,
    vector<int>& color,
    bool &flag
)
```

It takes:

* `graph` → adjacency list
* `vertex` → current vertex
* `color` → stores the color of every vertex
* `flag` → tells us whether the graph is still potentially bipartite

---

## 5. Checking Every Neighbor

Inside DFS:

```cpp
for(auto node : graph[vertex])
```

We examine every neighbor of the current vertex.

There are three important cases.

### Case 1: Neighbor has the same color

```cpp
if(color[node] == color[vertex]){
    flag = false;
    return;
}
```

This means we found:

```text
1 ---- 1
```

or

```text
2 ---- 2
```

which violates the bipartite condition.

Therefore:

```cpp
flag = false;
```

and we stop this DFS.

---

### Case 2: Neighbor is uncolored

```cpp
else if(color[node] == 0)
```

We haven't visited this neighbor yet.

So we assign it the opposite color.

```cpp
if(color[vertex] == 1)
    color[node] = 2;

if(color[vertex] == 2)
    color[node] = 1;
```

Then recursively explore it:

```cpp
dfs_traversal(graph, node, color, flag);
```

This is the actual **2-coloring process**.

---

### Case 3: Neighbor is already colored differently

If:

```text
color[node] != color[vertex]
```

and the neighbor is already colored, everything is fine.

We simply continue checking the remaining neighbors.

---

## 6. Why Do We Need the Outer Loop?

A graph can contain multiple **disconnected components**.

For example:

```text
Component 1:

0 ---- 1


Component 2:

2 ---- 3
```

Starting DFS from `0` will never reach `2`.

Therefore we do:

```cpp
for(int i = 0; i < v; i++){
    if(color[i] == 0){
        color[i] = 1;
        dfs_traversal(graph, i, color, flag);
    }
}
```

Whenever we find an uncolored vertex, it represents a new disconnected component.

We start another DFS from it.

---

## 7. Complete Flow

The entire algorithm can be understood as:

```text
Create color array
        ↓
Initially every vertex = 0
        ↓
For every vertex
        ↓
Is it uncolored?
   ↓ Yes
Give it color 1
        ↓
Start DFS
        ↓
Check every neighbor
        ↓
Is neighbor uncolored?
   ↓ Yes
Give opposite color
        ↓
Continue DFS
        ↓
Is neighbor same color?
   ↓ Yes
Graph is NOT bipartite
        ↓
Otherwise continue
        ↓
Check all components
        ↓
No conflict found
        ↓
Graph IS bipartite
```

---

## 8. Why the Algorithm Works

The key invariant is:

> Whenever we color a vertex, we always give it the opposite color from the vertex through which we reached it.

Therefore every newly explored edge connects different colors.

The only possible problem is when we encounter a vertex that has **already been colored**.

If it has the same color as the current vertex:

```text
current = 1
neighbor = 1
```

then the graph cannot be divided into two valid groups.

Hence the graph is not bipartite.

---

## 9. Example

Consider:

```text
0 ---- 1
|      |
|      |
3 ---- 2
```

Start:

```text
color = [0, 0, 0, 0]
```

Start DFS at `0`:

```text
color[0] = 1
```

Visit `1`:

```text
color[1] = 2
```

Visit `2`:

```text
color[2] = 1
```

Visit `3`:

```text
color[3] = 2
```

Final:

```text
color = [1, 2, 1, 2]
```

Every edge connects different colors.

Therefore:

```text
Bipartite → true
```

---

## 10. Example of a Non-Bipartite Graph

Consider a triangle:

```text
      0
     / \
    1---2
```

Start:

```text
color[0] = 1
```

Then:

```text
color[1] = 2
color[2] = 2
```

Now we check the edge:

```text
1 ---- 2
```

Both have color `2`.

Therefore:

```cpp
if(color[node] == color[vertex])
```

becomes true.

So:

```text
flag = false
```

and the graph is not bipartite.

This is why **odd cycles cannot be bipartite**.

---

## 11. Why `color[node] == 0` Is Important

This condition:

```cpp
else if(color[node] == 0)
```

prevents us from repeatedly running DFS on an already visited vertex.

It also allows us to distinguish between:

```text
Unvisited vertex → color it
Already visited vertex → check whether its color causes a conflict
```

This is essentially the role that a `visited` array would normally play.

Here, the `color` array performs both jobs:

```text
color = 0 → not visited
color = 1 → visited + color 1
color = 2 → visited + color 2
```

---

## 12. Complexity

Let:

* `V` = number of vertices
* `E` = number of edges

Every vertex is colored at most once.

Every edge is examined at most twice in an undirected adjacency list.

Therefore:

### Time Complexity

```text
O(V + E)
```

### Space Complexity

```text
O(V)
```

The `O(V)` space comes from:

* `color` array
* DFS recursion stack

---

## 13. Important Pattern to Remember

For **Bipartite Graph using DFS**, remember this template:

```text
1. Create color array initialized to 0
2. For every uncolored vertex:
      color it 1
      DFS
3. During DFS:
      For every neighbor:
          If uncolored:
              give opposite color
              DFS
          Else if same color:
              return false
4. If no conflict:
      return true
```

The entire problem essentially boils down to one question:

> **Can I 2-color the graph without ever having an edge between two vertices of the same color?**

If yes → **Bipartite**
If no → **Not Bipartite**
