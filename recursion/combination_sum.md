# 39. Combination Sum (LeetCode)

## Problem

Given an array of **distinct** integers `candidates` and an integer `target`, return all unique combinations of `candidates` whose chosen numbers sum to `target`. The same number may be used an unlimited number of times. Two combinations are different if the frequency of at least one number differs.

**Constraints**

- `1 <= candidates.length <= 30`
- `2 <= candidates[i] <= 40`
- All elements are distinct
- `1 <= target <= 40`
- The number of unique combinations is guaranteed to be less than 150

**Examples**

| Input | Output |
|---|---|
| `candidates = [2,3,6,7], target = 7` | `[[2,2,3],[7]]` |
| `candidates = [2,3,5], target = 8` | `[[2,2,2,2],[2,3,3],[3,5]]` |
| `candidates = [2], target = 1` | `[]` |

---

## Approach: Recursion + Backtracking

We need every valid combination, not just a count, so we build the combination one element at a time and record it when the remaining target reaches 0.

### Core idea

At each recursive call we ask: **"What is the next element I add to the buffer?"**

A `for` loop tries every possible answer:

```cpp
for (int j = i; j < candidates.size(); j++) {
    buffer.push_back(candidates[j]);
    calc_combinations(candidates, answer, target - candidates[j], j, buffer);
    buffer.pop_back();
}
```

- `buffer` holds the numbers chosen so far.
- `target` is the remaining amount still to be made.
- `i` is the smallest index we are allowed to pick from.

### Why the recursive call passes `j`

```cpp
calc_combinations(..., target - candidates[j], j, buffer);
```

Passing `j` does two jobs at once:

1. **Reuse is allowed.** The next call starts its loop at `j`, so `candidates[j]` can be picked again.
2. **No going backwards.** The next call can never pick an index below `j`, so each combination is only ever built in one order. `[2,3,3]` is generated, but `[3,2,3]` and `[3,3,2]` never are.

| Second argument | Same element reusable? | Earlier elements allowed? | Result |
|---|---|---|---|
| `j` | yes | no | combinations with repetition (this problem) |
| `j + 1` | no | no | each element at most once (Combination Sum II style) |
| `0` | yes | yes | ordered sequences, duplicates of the same set |

### Where the "skip this element" case lives

There is no separate recursive call for skipping an element. It is built into the loop: moving from `j` to `j + 1` means `candidates[j]` is skipped. Every iteration commits to one element, and elements that are skipped are the ones whose iterations the loop moves past.

### Base cases

| Condition | Action |
|---|---|
| `target == 0` | A valid combination is found, save it |
| `target < 0` | Overshot, stop this branch |
| `i >= candidates.size()` | No candidates left, stop this branch |

### Backtracking

After the recursive call returns, `buffer.pop_back()` removes the element just tried so the next loop iteration starts from the same state. In this code `buffer` is passed **by value**, so every call already works on its own copy and the `pop_back` only restores the current call's local copy. It is harmless and keeps the push/pop pattern clear.

---

## Dry run

`candidates = [2,3]`, `target = 6`

```
solve(i=0, t=6, [])
├─ j=0: push 2 → solve(i=0, t=4, [2])
│   ├─ j=0: push 2 → solve(i=0, t=2, [2,2])
│   │   ├─ j=0: push 2 → solve(i=0, t=0, [2,2,2]) → SAVE
│   │   └─ j=1: push 3 → solve(i=1, t=-1, ...)    → target < 0, return
│   └─ j=1: push 3 → solve(i=1, t=1, [2,3])
│       ├─ j=1: push 3 → solve(i=1, t=-2, ...)    → target < 0, return
│       (loop ends)
└─ j=1: push 3 → solve(i=1, t=3, [3])
    └─ j=1: push 3 → solve(i=1, t=0, [3,3]) → SAVE
```

Result: `[[2,2,2],[3,3]]`

---

## Notes on this specific solution

### The `sort` and `set` are not needed

```cpp
sort(buffer.begin(), buffer.end());               // in the base case
set<vector<int>> st(answer.begin(), answer.end()); // in combinationSum
```

These guard against duplicate combinations, but the index rule (`j` is passed down and the loop starts at `i`) already guarantees every combination is generated exactly once. So:

- The `sort` in the base case does nothing useful, because buffers are already built in index order.
- The `set` removes nothing, and it costs extra time and memory (every answer gets copied into a `set` and then again into `ans`).

They are safe to keep, but they can be deleted and the answer stays the same.

### The `target < 0` check

It is correct, but it lets a call happen and then rejects it. Checking before recursing avoids the wasted call:

```cpp
if (candidates[j] > target) continue;
```

### Possible optimizations

1. **Pass `buffer` by reference** (`vector<int>& buffer`) so there is no vector copy on every call. The `push_back`/`pop_back` then really do the backtracking. Copy only when saving an answer.
2. **Sort `candidates` once** at the start, then use `break` instead of `continue` when `candidates[j] > target`, since every later candidate is also too large.
3. **Remove the `sort` and `set`** as explained above.

### Optimized version

```cpp
class Solution {
public:
    vector<vector<int>> result;

    void solve(vector<int>& c, int target, int i, vector<int>& path) {
        if (target == 0) { result.push_back(path); return; }
        for (int j = i; j < c.size(); j++) {
            if (c[j] > target) break;   // valid because c is sorted
            path.push_back(c[j]);
            solve(c, target - c[j], j, path);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> path;
        solve(candidates, target, 0, path);
        return result;
    }
};
```

---

## Complexity

Let `n` be the number of candidates, `T` the target, and `m` the smallest candidate.

- **Time:** the recursion depth is at most `T / m`, and each node can branch up to `n` ways, so the search tree is bounded by roughly `O(n^(T/m))`. In practice it is far smaller because of the target pruning, and the input limits keep it small.
- **Space:** `O(T / m)` for the recursion stack and the buffer, not counting the output. This submission uses more because the buffer is copied on every call and the `set` stores all answers a second time.