# Dijkstra — Quick Notes

## Idea

Find the shortest distance from `src` to every node in a **weighted graph with no negative edges**.

### Core process

```text
distance[src] = 0
push {src, 0} into PQ

while PQ is not empty:

    pop node with smallest distance

    if this entry is stale:
        continue

    for every neighbor:

        newDist = currentDist + edgeWeight

        if newDist < distance[neighbor]:
            distance[neighbor] = newDist
            push {neighbor, newDist} into PQ
```

---

## What does the PQ store?

```text
{node, total distance from source}
```

NOT:

```text
{node, edge weight}
```

Example:

```text
2 → 1 = 3
1 → 0 = 1

distance to 0 = 3 + 1 = 4

PQ → {0,4}
```

---

## Why the custom comparator?

`priority_queue` is normally a **max-heap**.

Dijkstra needs the **smallest distance first**.

```cpp
class Compare {
public:
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.second > b.second;
    }
};
```

```text
<  → max-heap
>  → min-heap
```

---

## Why no `visited[]`?

A node can enter the PQ multiple times.

Example:

```text
{0,6}  ← old
{0,4}  ← better
```

When `{0,6}` comes out:

```cpp
if(currentDist > distance[node])
    continue;
```

It's stale, so ignore it.

---

## Key idea

```text
Find shorter path
       ↓
Update distance[]
       ↓
Push new {node, distance}
       ↓
Process smallest distance next
```

### Complexity

```text
Time:  O(E log V)
Space: O(V + E)
```
