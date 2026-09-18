# Course Schedule II

## Problem

Given `numCourses` courses and a list of prerequisites, return an ordering of courses such that all prerequisites are completed before their dependent courses.

If it is impossible to finish all courses because of a cycle, return an empty vector.

---

## Approach

This problem can be solved using **Topological Sort with BFS (Kahn's Algorithm)**.

### Key Idea

For every prerequisite pair:

```text
[course, prerequisite]
```

the prerequisite must come before the course:

```text
prerequisite → course
```

We build:

* An **adjacency list** to store the directed edges.
* An **indegree array** to store how many prerequisites each course still has.

### Step 1: Build the Graph

For every prerequisite `[a, b]`:

```text
b → a
```

So:

* Add `a` to `adj[b]`
* Increment `indegree[a]`

For example:

```text
prerequisites = [[1,0], [2,0], [3,1]]
```

The graph becomes:

```text
0 → 1 → 3
↓
2
```

Indegrees:

```text
course:   0  1  2  3
indegree: 0  1  1  1
```

---

## Step 2: Add Courses With Indegree 0

A course with `indegree = 0` has no remaining prerequisites, so it can be taken immediately.

Add all such courses to a queue.

These courses are also added to the result.

---

## Step 3: BFS / Topological Sort

While the queue is not empty:

1. Remove a course from the queue.
2. Visit all courses that depend on it.
3. Decrease their indegree.
4. If a course's indegree becomes `0`, add it to the queue and result.

This means:

```text
Prerequisite completed
        ↓
Decrease dependent's indegree
        ↓
Indegree becomes 0
        ↓
Course is now available
```

---

## Step 4: Detect a Cycle

After BFS finishes, check the number of courses added to `res`.

### If:

```text
res.size() == numCourses
```

then every course was processed, so a valid ordering exists.

### Otherwise:

Some courses still have prerequisites that could never be satisfied.

This means the graph contains a **cycle**, so returning an ordering is impossible.

Example:

```text
0 → 1 → 2
    ↑     ↓
    └─────┘
```

Courses involved in the cycle never reach indegree `0`.

Therefore:

```cpp
return {};
```

---

## Example

### Input

```text
numCourses = 4
prerequisites = [[1,0], [2,0], [3,1], [3,2]]
```

Graph:

```text
    0
   / \
  1   2
   \ /
    3
```

A possible processing order is:

```text
0 → 1 → 2 → 3
```

Another valid order could be:

```text
0 → 2 → 1 → 3
```

The exact ordering can differ because multiple courses may have indegree `0` at the same time.

---

## Complexity

Let:

* `V` = number of courses
* `E` = number of prerequisites

### Time Complexity

```text
O(V + E)
```

Each course is added to and removed from the queue at most once, and every edge is processed once.

### Space Complexity

```text
O(V + E)
```

The adjacency list stores all edges, while the indegree array, queue, and result use `O(V)` space.

---

## Pattern

This is the **Kahn's Algorithm / BFS Topological Sort** pattern:

```text
Build indegree
      ↓
Find indegree-0 vertices
      ↓
Push them into queue
      ↓
Process vertex
      ↓
Decrease neighbors' indegree
      ↓
New indegree-0 vertex?
      ↓
Push into queue
      ↓
Count processed vertices
      ↓
Count == V → valid topological ordering
Count < V  → cycle exists
```

### Important Insight

> **Topological sorting is possible only for a Directed Acyclic Graph (DAG).**

So in Course Schedule II, the problem is essentially:

**"Find a topological ordering of the course dependency graph, or detect that a cycle makes it impossible."**
