# 40. Combination Sum II

Given a collection of candidate numbers (`candidates`) and a target number (`target`), find all **unique** combinations where the numbers sum to `target`. Each number may be used **at most once**, and the solution set must not contain duplicate combinations.

**Constraints:** `1 <= candidates.length <= 100`, `1 <= candidates[i] <= 50`, `1 <= target <= 30`

## Approach

Sort + backtracking (DFS).

1. **Sort** `candidates` so equal values sit next to each other.
2. Run a recursive search that builds a `buffer` one element at a time.
3. When `target == 0`, the current `buffer` is a valid combination, so record it.
4. When `target < 0` or there are no elements left, stop exploring that branch.
5. Each element is used at most once because the recursive call moves forward to index `j` and the next loop starts at `j + 1`.

## Starting from `i = -1`

In this solution, the parameter `i` means **the index of the last element picked**, not the next one to try.

| Concept | Value |
|---|---|
| `i` means | index of the last used element |
| Loop starts at | `j = i + 1` (the next unused element) |
| Recursive call passes | `j` (the element just picked) |
| Initial call | `i = -1` (nothing picked yet) |

Starting at `-1` makes the first loop begin at `j = 0`, the very first element. If you started with `i = 0`, the loop would begin at index 1 and the element at index 0 would never be a first pick.

## Duplicate handling

The key line is:

```cpp
if (j > i + 1 && candidates[j] == candidates[j-1]) continue;
```

Read it as: *"If I am not the first choice at this level, and I have the same value as the element just before me, skip me."*

- **Why sorting matters:** the check only compares with `candidates[j-1]`, which works only if equal values are adjacent.
- **Why `j > i + 1`:** the first choice at a level is `j = i + 1`. It must be allowed even when it equals `candidates[j-1]`, because that earlier element was picked by a parent level. This is how `[1,1,6]` gets built: the second `1` is the first choice at a deeper level.
- **What it prevents:** starting two sibling branches with the same value. Both would explore identical sub-trees and produce the same combinations.

**Rule of thumb:** at the same level, never start two branches with the same value, but the same value may appear again at a deeper level.

### Mini example: `[1, 1, 2]`, target 3

```
calc(i=-1, rem=3)
├── j=0, val 1: first choice, allowed
│     calc(i=0, rem=2)
│     ├── j=1, val 1: first choice at this level, allowed
│     │     calc(i=1, rem=1)  -> dead end
│     └── j=2, val 2: allowed
│           calc(i=2, rem=0)  -> record [1,2]
│
├── j=1, val 1: j > i+1 and equals candidates[0], SKIP
│
└── j=2, val 2: allowed
      calc(i=2, rem=1)        -> dead end
```

Result: `[[1,2]]`. Without the skip, `[1,2]` would be produced twice.

## The `(int)candidates.size()` cast

```cpp
if (target < 0 || i >= (int)candidates.size()) return;
```

`candidates.size()` returns an **unsigned** type (`size_t`). Comparing a signed `int` with an unsigned value converts the `int` to unsigned first.

Because the initial call uses `i = -1`, without the cast this happens:

```
(unsigned)(-1) = 18446744073709551615
18446744073709551615 >= candidates.size()  ->  true
```

The function would return immediately, before the loop ever runs, and the answer would be an empty `[]`. Casting `size()` to `int` makes it a normal signed comparison, so `-1 >= n` is false as intended.

## Complexity

- **Time:** O(2^n * n) worst case. Each element is either picked or not, and copying a found combination costs up to O(n). In practice it is much smaller, since the skip rule avoids duplicate branches and the depth is bounded by `target`.
- **Space:** O(n) for the recursion stack and buffer, excluding the output.

## Possible improvements

- Pass `buffer` by reference (`vector<int>&`) to avoid copying it on every call. Then the `pop_back()` is what restores state.
- Add `if (candidates[j] > target) break;` to prune, since the array is sorted and every later element is also too large.
- The `sort(buffer...)` on a found combination is unnecessary, since the input is already sorted and the buffer is built in order.