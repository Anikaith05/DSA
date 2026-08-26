# 133. Clone Graph

## Problem

Given a reference to a node in a **connected undirected graph**, return a **deep copy** of the graph.

Each node contains:
- `val` — the node's value
- `neighbors` — a list of pointers to neighboring nodes

The graph may contain cycles, so simply recursively copying every neighbor would create an infinite loop.

---

## Core Idea

The key difficulty is:

> When we encounter an original node, how do we make sure we create **exactly one clone** of it?

We use an `unordered_map`:

```cpp
unordered_map<Node*, Node*> mp;
```

The mapping is:

```text
original node  →  cloned node
```

For example:

```text
1 → 1'
2 → 2'
3 → 3'
```

Once an original node is in the map, we know its clone already exists.

---

## Approach Used

This solution uses **BFS + HashMap** and separates the process into two phases.

### Phase 1 — Create all cloned nodes

Start from the given node.

```cpp
Node* new_node = new Node(node->val);
mp[node] = new_node;
```

Then perform BFS over the original graph.

For every neighbor:

```cpp
if(mp.find(nodei) == mp.end())
```

If the neighbor has not been cloned yet:

1. Create its clone.
2. Store the mapping.
3. Push the original neighbor into the queue.

This guarantees that every original node gets exactly one clone.

---

### Phase 2 — Connect the cloned nodes

After all nodes have been cloned, iterate through the map.

For every original node:

```cpp
Node* orig = node.first;
Node* clone = node.second;
```

Look at every original neighbor:

```cpp
for(auto nodei : orig->neighbors)
```

and connect the corresponding cloned neighbor:

```cpp
clone->neighbors.push_back(mp[nodei]);
```

So if:

```text
1 → 2
```

then we create:

```text
1' → 2'
```

The important point is that we use the map to find the correct clone.

---

## Why Do We Need the HashMap?

Consider a cycle:

```text
1 — 2
|   |
4 — 3
```

While traversing:

```text
1 → 2 → 3 → 4 → 1
```

When we reach `1` again, we **must not create another copy of node 1**.

The map tells us:

```cpp
mp.find(1) != mp.end()
```

Therefore:

> Node 1 has already been cloned, so don't create it again.

This is what prevents infinite traversal and duplicate nodes.

---

## Example

Input:

```text
1: [2,4]
2: [1,3]
3: [2,4]
4: [1,3]
```

### Phase 1

Create:

```text
1 → 1'
2 → 2'
3 → 3'
4 → 4'
```

### Phase 2

Copy the edges:

```text
1: [2,4]  →  1': [2',4']
2: [1,3]  →  2': [1',3']
3: [2,4]  →  3': [2',4']
4: [1,3]  →  4': [1',3']
```

The result is a completely separate graph.


## Complexity

Let `V` be the number of nodes and `E` the number of edges.

### Time

BFS visits every node and edge:

```text
O(V + E)
```

The second phase also processes every node and edge:

```text
O(V + E)
```

Overall:

```text
O(V + E)
```

### Space

The hash map stores one clone for every node:

```text
O(V)
```

The BFS queue can contain up to `O(V)` nodes.

Therefore:

```text
O(V)
```

auxiliary space.

---

## Pattern to Remember

This problem teaches an important **Graph Copy / Clone** pattern:

```text
Original Graph
      ↓
HashMap
original → clone
      ↓
Traverse original graph
      ↓
Create each clone once
      ↓
Connect clones using the map
```

The general template is:

```cpp
if(node not cloned) {
    create clone;
    store mapping;
}

for(each neighbor) {
    if(neighbor not cloned) {
        clone neighbor;
    }

    connect clone → cloned neighbor;
}
```

### The most important invariant

> **Every original node has exactly one corresponding clone in the map.**

Once you understand that invariant, the entire problem becomes much easier.

---

## Interview Takeaway

If asked to explain the solution in an interview:

> "I use BFS to traverse the original graph and an unordered map to maintain a mapping from each original node to its cloned node. Whenever I encounter an unvisited node, I create its clone and store it in the map. After all nodes are cloned, I iterate through the original nodes and recreate their edges using the mapped clone references. The map is essential because the graph can contain cycles, and it ensures that each node is cloned exactly once."

**Pattern:** Graph Traversal + HashMap + Deep Copy
