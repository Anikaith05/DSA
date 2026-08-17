# Undirected Graph Cycle Detection — BFS

## Approach

We detect a cycle in an **undirected graph** using **BFS + Parent Tracking**.

The key idea is:

> If we encounter a vertex that is already visited and it is **not the parent of the current vertex**, then a cycle exists.

### Why do we need the parent?

In an undirected graph, every edge exists in both directions.

For example:

```text
0 ----- 1
```

The adjacency list contains:

```text
0 → 1
1 → 0
```

When we are at `1`, we will see `0` as an already-visited vertex.

But this **is not a cycle** — `0` is simply the parent of `1`.

Therefore, we ignore:

```text
visited neighbor == parent[current]
```

and declare a cycle when:

```text
visited neighbor != parent[current]
```

---

## Algorithm

1. Build an adjacency list from the edges.
2. Create a `visited` array.
3. Iterate through every vertex.

   * This handles **disconnected graphs**.
4. For every unvisited vertex:

   * Start a BFS.
   * Set its parent to `-1`.
5. During BFS:

   * If the neighbor is unvisited:

     * Mark it visited.
     * Set its parent to the current vertex.
     * Add it to the queue.
   * If the neighbor is already visited:

     * If it is **not the parent**, a cycle exists.
6. If BFS finishes without finding a cycle, continue with the next unvisited component.
7. If no cycle is found, return `false`.

---

## Pseudocode

```text
create adjacency list

create visited array initialized to false

for every vertex i:
    if i is not visited:

        create BFS queue
        create parent information

        mark i as visited
        parent[i] = -1
        push i into queue

        while queue is not empty:

            current = front of queue
            remove current

            for every neighbor of current:

                if neighbor is unvisited:
                    mark neighbor as visited
                    parent[neighbor] = current
                    push neighbor into queue

                else if neighbor is not the parent of current:
                    return true

return false
```

---

## Example

Consider:

```text
    0
   / \
  1---2
```

BFS starts at `0`.

```text
0 → 1
0 → 2
```

Then while processing `1`:

```text
1 → 0
```

`0` is the parent, so we **ignore** it.

But `1` also sees:

```text
1 → 2
```

`2` is already visited and is **not** the parent of `1`.

Therefore:

```text
Cycle exists
```

---

## Complexity

### Time Complexity

Building the adjacency list:

```text
O(E)
```

BFS traversal:

```text
O(V + E)
```

For an undirected graph, every edge appears twice in the adjacency list:

```text
O(V + 2E) = O(V + E)
```

Therefore:

```text
Time: O(V + E)
```

### Space Complexity

```text
Adjacency list → O(V + E)
Visited        → O(V)
Parent         → O(V)
Queue          → O(V)
```

Overall:

```text
Space: O(V + E)
```

---

## Key Takeaway

For **undirected graph cycle detection using BFS**:

```text
Unvisited neighbor
        ↓
     Visit it
        ↓
 Set its parent


Visited neighbor
        ↓
 Is it the parent?
    ↙          ↘
  YES           NO
   ↓             ↓
 Ignore        CYCLE
```

The **parent check is the core idea** that distinguishes a normal undirected edge from an actual cycle.

### Core Condition

```cpp
if (!visited[neighbor]) {
    // Visit neighbor
}
else if (neighbor != parent[current]) {
    // Cycle found
}
```
