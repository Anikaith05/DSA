# 🛡️ 802. Find Eventual Safe States

## 🧠 Core Idea

A node is **safe** if eventually every path from it reaches a terminal node.

Instead of trying to detect cycles from every node, we **work backwards from terminal nodes**.

### 🔄 Reverse the Graph

Original:

```text
0 → 1 → 2 → 5
    ↓
    3 → 0   🔄 cycle
4 → 5
5       terminal
6       terminal
```

Reverse edges:

```text
5 → 2
5 → 4
6 → -
2 → 0
1 → 0
3 → 1
0 → 3
```

Now we can start from the nodes that are **already known to be safe**.

---

## 🔑 Key Trick: Indegree = Number of Unsafe Dependencies

For every node:

```text
degree[i] = number of outgoing edges from i
```

A node with:

```text
degree[i] == 0
```

is a **terminal node** → definitely safe.

Then, when a safe node is removed, we remove its incoming edges in the reversed graph.

If another node's degree becomes `0`, **all of its outgoing paths now lead to safe nodes**, so it is also safe.

---

## 📊 Example

```text
Original graph:

2 → 5
4 → 5
5 → terminal
6 → terminal
```

Start:

```text
degree[5] = 0
degree[6] = 0

Queue:
[5, 6]
```

Process `5`:

```text
2 → 5
4 → 5

degree[2]--
degree[4]--

→ both become 0
```

Queue:

```text
[6, 2, 4]
```

So:

```text
Safe nodes = {2, 4, 5, 6}
```

---

## 🔄 Why Reverse the Edges?

Original edge:

```text
u → v
```

We store:

```text
v → u
```

So when `v` becomes safe, we can easily find all nodes that depended on `v`.

```cpp
adj[node].push_back(i);
degree[i]++;
```

Meaning:

```text
i → node

becomes

node → i
```

---

## 🧩 Algorithm

```text
1. Build reversed graph
2. degree[i] = number of outgoing edges of i
3. Put all degree-0 nodes into queue
4. BFS:
      take a safe node
      add it to answer

      for every predecessor:
          decrease its degree

          if degree becomes 0:
              push it into queue

5. Sort answer
6. Return answer
```


## 🎯 Pattern to Remember

> **Terminal nodes → Reverse Graph → Kahn's BFS**

Think:

```text
Safe nodes
    ↑
remove edges backwards
    ↑
terminal nodes
```

### 🧠 Recognition Trick

If you see:

* Directed graph
* Need nodes that **eventually reach terminal nodes**
* Cycles are unsafe
* Need to find all nodes that **don't lead to a cycle**

Think:

```text
        REVERSE GRAPH
              ↓
       TOPOLOGICAL SORT
              ↓
         KAHN'S BFS
```

---

## ⏱️ Complexity

Let `V = number of nodes` and `E = number of edges`.

```text
Build graph:     O(V + E)
BFS:             O(V + E)
Sorting:         O(V log V)

Total:           O(V + E + V log V)

Space:           O(V + E)
```
