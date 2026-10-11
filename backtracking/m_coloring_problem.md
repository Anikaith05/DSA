# Graph Coloring (M-Coloring Problem) – Backtracking Solution

Given an undirected graph with `v` vertices and a list of `edges`, decide whether the vertices can be colored using at most `m` colors so that **no two adjacent vertices share the same color**. Returns `true` if possible, otherwise `false`.

## Approach

The solution uses **backtracking** over vertices in order `0 … v-1`.

1. **Build an adjacency list** from the edge list. Each edge `[a, b]` is added in both directions since the graph is undirected.
2. **Keep a `color` array** of size `v`, initialised to `-1` (uncolored).
3. **Recurse vertex by vertex** (`isPossible`):
   - If `i == v`, every vertex has been colored validly, so return `true`.
   - Otherwise try every color `j` in `0 … m-1` for vertex `i`.
   - If the color is safe (`isSafe`), assign it, recurse on vertex `i+1`, then undo the assignment (`color[i] = -1`).
   - Return `true` if any color choice leads to a full valid coloring.
4. **Prune early**: a color is only tried if no neighbor of `i` already uses it, so invalid branches are cut off immediately instead of being explored.

### Why `isSafe` was pulled out

Originally the neighbor check lived inside the color loop of `isPossible`:

```cpp
for (int j = 0; j < m; j++) {
    bool ok = true;
    for (auto node : adj[i]) {
        if (color[node] == j) { ok = false; break; }
    }
    if (ok) { ... }
}
```

That mixes two responsibilities: *deciding whether a color is valid* and *driving the recursion*. Extracting it into

```cpp
bool isSafe(adj, color, i, j)   // can vertex i take color j?
```

gives:

- **Readability** – `isPossible` now reads like the algorithm: "for each color, if safe, place it, recurse, undo."
- **Single responsibility** – the safety rule (no neighbor shares color `j`) lives in one place and can be tested or changed independently.
- **Less nesting** – removes a nested loop and the temporary `ok` flag from the recursive function.
- **Reusability** – the same check works for any variant (e.g. printing the coloring, counting colorings).

## Edge Cases

| Case | Behavior |
|------|----------|
| `m == 0` | Returns `false` immediately; no vertex can be colored. |
| `m == 1` and `v > 1` | Returns `false` immediately. Valid **only if the graph has at least one edge** (see note below). |
| `i == v` (all vertices colored) | Base case, returns `true`. |
| Disconnected graph | Handled naturally, since every vertex `0 … v-1` is visited regardless of connectivity. |
| Complete graph (`K_v`) | Needs `m >= v`; the backtracking correctly fails otherwise. |
| Duplicate edges | Harmless; they only add redundant checks in `isSafe`. |
| Self-loop `[i, i]` | Ignored by the current check, because `color[i]` is still `-1` when vertex `i` is tested. A self-loop should make the graph uncolorable, so filter or reject these if the input can contain them. |
| Single vertex (`v == 1`) | Colorable with any `m >= 1`. |

> **Note on the `m == 1` shortcut:** `v > 1 && m == 1` returning `false` is correct under the usual constraints (at least one edge exists). For an edgeless graph with `v > 1`, one color is actually enough, so the shortcut would give a wrong answer. If edgeless inputs are possible, remove that condition and let the backtracking decide.

## Complexity

- **Time:** `O(m^v)` in the worst case, since each of the `v` vertices may try up to `m` colors. Each `isSafe` call costs `O(deg(i))`. Pruning makes it much faster in practice.
- **Space:** `O(v + E)` for the adjacency list, plus `O(v)` recursion depth. Note that `color` is currently **passed by value**, so each call copies it, adding `O(v)` work and memory per call.

## Possible Improvements

- Pass `color` **by reference** (`vector<int>&color`) in both `isSafe` and `isPossible`. The existing undo step (`color[i] = -1`) already makes this correct, and it avoids copying the array on every call.
- Return `true` immediately when a recursive call succeeds, instead of `curr = curr || ...`, so the loop stops trying further colors.
- Move the `m == 0` / `m == 1` checks into `graphColoring` so they run once instead of at every recursion level.
- Break symmetry (e.g. force vertex 0 to color 0) to cut duplicated work.

## Code Structure

```
isSafe(adj, color, i, j)                  -> checks neighbors of i for color j
isPossible(adj, v, m, i, color)           -> recursive backtracking
graphColoring(v, edges, m)                -> builds adjacency list, starts recursion
```