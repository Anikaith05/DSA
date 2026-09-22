# All Ancestors of a Node in a DAG

## 🧠 Approach

Use **Kahn's Topological Sort (BFS)** and propagate each node's ancestors to its children.

### Key Idea

If we have:

```text
0 → 1 → 3
    ↓
    2 → 3
```

When processing `1`:

```text
ancestors[1] = {0}
```

So for its child `3`:

```text
ancestors[3] += ancestors[1]
ancestors[3] += 1
```

Therefore:

```text
ancestors[3] = {0, 1}
```

---

## 🔄 Algorithm

### 1. Build the graph

For every edge:

```text
u → v
```

store:

```cpp
adj[u].push_back(v);
degree[v]++;
```

`degree[v]` represents the number of incoming edges.

### 2. Start BFS with source nodes

Nodes with:

```cpp
degree[i] == 0
```

have no ancestors, so put them into the queue.

### 3. Propagate ancestors

For every edge:

```text
vertex → node
```

the child inherits **all ancestors of `vertex`**.

```cpp
for (auto a : ancestors[vertex]) {
    if (find(ancestors[node].begin(),
             ancestors[node].end(),
             a) == ancestors[node].end()) {

        ancestors[node].push_back(a);
    }
}

ancestors[node].push_back(vertex);
```

### 🚨 Why the `find()` check?

The same ancestor can reach a node through **multiple paths**.

Example:

```text
       0
      / \
     1   2
      \ /
       3
```

When processing `1`:

```text
ancestors[3] = {0, 1}
```

When processing `2`, `0` is an ancestor of `2` as well:

```text
ancestors[2] = {0}
```

So blindly copying would give:

```text
ancestors[3] = {0, 1, 0, 2}
                         ↑
                      duplicate
```

We only want:

```text
ancestors[3] = {0, 1, 2}
```

Therefore:

```cpp
find(...) == ancestors[node].end()
```

means:

> **`a` is NOT already present → safe to add it.**

```text
        Is `a` already present?
              │
        ┌─────┴─────┐
       YES           NO
        │             │
      skip         add `a`
```

### 4. Mark the child as processed

After processing the edge:

```cpp
degree[node]--;
```

When:

```cpp
degree[node] == 0
```

all of its parents have been processed, so we can safely push `node` into the queue.

### 5. Sort the result

The problem requires ascending order:

```cpp
sort(ancestors[node].begin(),
     ancestors[node].end());
```

---

## 👀 Visual Flow

```text
        0
       / \
      ↓   ↓
      1   2
       \ /
        ↓
        3
```

Processing `0`:

```text
ancestors[0] = {}
```

Processing `1`:

```text
ancestors[1] = {0}
```

Processing `2`:

```text
ancestors[2] = {0}
```

Processing `3`:

```text
from 1 → {0} + 1
from 2 → {0} + 2

ancestors[3] = {0, 1, 2}
```

The `find()` check prevents `0` from being inserted twice.

---

## 💡 Why Topological Sort?

A node should only be processed **after all of its parents have been processed**.

Kahn's algorithm guarantees exactly that:

```text
All parents processed
        ↓
   indegree = 0
        ↓
    process node
        ↓
 propagate ancestors
```

Therefore, when we copy `ancestors[vertex]`, that list is already complete.

---

## ⏱️ Complexity

Let `n` = number of nodes and `E` = number of edges.

```text
Topological sort     → O(n + E)

Ancestor propagation → depends on number of ancestors

find()               → O(n) worst case

sorting              → O(A log A)
```

where `A` is the total number of ancestor entries.

For `n ≤ 1000`, this approach is practical.

---

## 🔑 Pattern to Remember

> **DAG + information from all predecessors → Topological Sort + Propagation**

```text
Topological Order
       ↓
Process parent
       ↓
Pass ancestors forward
       ↓
Child collects ancestors
```

### One-line memory trick

**"Process parents first, then pass their ancestors forward — while preventing duplicates."**
