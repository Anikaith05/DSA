# 🚀 Bellman-Ford Algorithm

## 🎯 Goal

Find the **shortest distance from a source node to every other node** in a weighted graph.

✅ Handles negative edge weights
✅ Detects negative weight cycles
❌ Slower than Dijkstra's algorithm

---

# 💡 Core Idea

Bellman-Ford repeatedly tries to improve the shortest distances by checking **every edge**.

Imagine an edge:

```text
u ──── wt ────▶ v
```

If going through `u` gives us a shorter path to `v`:

```text
distance[u] + wt < distance[v]
```

Then update:

```text
distance[v] = distance[u] + wt
```

This process is called **Edge Relaxation**.

---

# 🔄 Step 1: Initialize Distances

Initially, we don't know how to reach most nodes.

```text
Source = 0

Node:       0      1      2      3

Distance:   0      ∞      ∞      ∞
            ↑
         Source
```

* Source distance = `0`
* Every other node = `∞`

---

# 🔁 Step 2: Relax Every Edge

Consider:

```text
0 ──4──▶ 1 ──3──▶ 2
│
└──10──────────▶ 2
```

Initially:

```text
0 = 0
1 = ∞
2 = ∞
```

### Check `0 → 1`

```text
0 + 4 < ∞  ✅
```

Update:

```text
0 = 0
1 = 4
2 = ∞
```

### Check `1 → 2`

```text
4 + 3 < ∞  ✅
```

Update:

```text
2 = 7
```

### Check `0 → 2`

```text
0 + 10 < 7  ❌
```

No update.

Final:

```text
0 = 0
1 = 4
2 = 7
```

---

# 🔄 Step 3: Repeat V-1 Times

We relax **all edges repeatedly**.

```text
Iteration 1
   ↓
Check every edge

Iteration 2
   ↓
Check every edge

Iteration 3
   ↓
Check every edge

...
   ↓

V - 1 iterations
```

## 🤔 Why V-1?

The longest possible **simple path** in a graph with `V` vertices contains at most:

```text
V - 1 edges
```

Example:

```text
0 ──▶ 1 ──▶ 2 ──▶ 3

Vertices = 4
Edges in longest simple path = 3

= V - 1
```

Therefore, after `V-1` iterations, all shortest paths should be found.

---

# ⚠️ Step 4: Detect Negative Cycles

After completing `V-1` iterations, check every edge **one more time**.

### If no distance changes:

```text
No Negative Cycle ✅
```

### If a distance can still decrease:

```text
Negative Cycle Exists ❌
```

Example:

```text
      -3
   ┌──────▶
   │       │
   ▲       ▼
   1 ◀──── 2
       1
```

Going around the cycle keeps reducing the total distance:

```text
1 → 2 → 1

Cost = -3 + 1 = -2
```

Each time we go around:

```text
Distance = smaller
Distance = smaller
Distance = smaller
...
```

So there is **no valid shortest path**.

---

# 🧠 Complete Flow

```text
        START
          │
          ▼
 Initialize distances
 Source = 0
 Others = ∞
          │
          ▼
 Relax all edges
          │
          ▼
 Repeat V - 1 times
          │
          ▼
 Check all edges once more
          │
     ┌────┴────┐
     ▼         ▼
  Update?     No Update
     │           │
     ▼           ▼
Negative      Return
Cycle ❌      Distances ✅
```

---

# ⏱️ Complexity

| Complexity | Value      |
| ---------- | ---------- |
| ⏱️ Time    | `O(V × E)` |
| 💾 Space   | `O(V)`     |

Where:

* `V` = Number of vertices
* `E` = Number of edges

---

# 🔑 Key Takeaway

```text
Relax every edge
        ↓
Repeat V - 1 times
        ↓
One more relaxation check
        ↓
Update possible?
   ↙          ↘
 YES          NO
  ↓            ↓
Negative      Shortest
Cycle ❌      Paths ✅
```

**Bellman-Ford is especially useful when a graph can contain negative edge weights.**
