# Permutations (Backtracking)

Given an array `nums` of distinct integers, return all possible permutations.

```
Input:  [1, 2, 3]
Output: [1,2,3] [1,3,2] [2,1,3] [2,3,1] [3,1,2] [3,2,1]
```

---

## Approach

Build each permutation one position at a time. At every position, try every number that has **not been used yet**, recurse to fill the next position, then undo the choice (backtrack) and try the next number.

- `buffer` holds the permutation being built.
- `visited[j]` records whether `nums[j]` is already in `buffer`.
- `i` is the number of positions filled so far. When `i == n`, `buffer` is a full permutation, so save it.

---

## How the solution evolved

### Attempt 1: skip only the previous index

```cpp
for (int j = 0; j < nums.size(); j++) {
    if (j == i - 1) continue;   // only blocks ONE index, tied to depth
    ...
}
```

The idea was "don't pick what I just picked." The problem is that the check is based on the **depth `i`**, not on what is actually in `buffer`. It blocks exactly one index and knows nothing about the others.

Trace for `nums = [1, 2, 3]`:

```
i=0  buffer = []          check: j == -1  → nothing blocked
 └─ pick nums[0]=1
i=1  buffer = [1]         check: j == 0   → blocks index 0 (fine here)
 └─ pick nums[1]=2
i=2  buffer = [1, 2]      check: j == 1   → blocks index 1 only
 └─ index 0 is NOT blocked → picks nums[0]=1 again

     buffer = [1, 2, 1]   ✗ duplicate 1, not a permutation
```

The code forgot that `1` was picked two levels ago.

```
              what it blocks            what it should block
              ──────────────            ────────────────────
 i=2          [ ] [ ] [X]   ← idx 1     [X] [X] [ ]   ← idx 0 and 1
              idx: 0   1   2            idx: 0   1   2
```

### Attempt 2: a `visited` array

Instead of guessing from the depth, keep an exact record of which indices are taken.

```cpp
if (visited[j] == 1) continue;  // skip anything already in buffer
buffer.push_back(nums[j]);
visited[j] = 1;                 // mark as used
calc(...);                      // go deeper
buffer.pop_back();              // undo
visited[j] = 0;                 // unmark so other branches can use it
```

The key change:

| | Attempt 1 | Attempt 2 |
|---|---|---|
| What it remembers | nothing (just depth `i`) | exactly which indices are used |
| Indices blocked per level | 1 | all of those already in `buffer` |
| Can produce duplicates | yes | no |

---

## Visual walkthrough (`nums = [1, 2, 3]`)

`visited` is shown as `[T/F, T/F, T/F]` for indices 0, 1, 2.

```
                          buffer=[]   visited=[F,F,F]
              ┌───────────────┼────────────────┐
           pick 1           pick 2           pick 3
        [1] [T,F,F]      [2] [F,T,F]      [3] [F,F,T]
         ┌───┴───┐        ┌───┴───┐        ┌───┴───┐
      pick 2   pick 3  pick 1   pick 3  pick 1   pick 2
     [1,2]    [1,3]    [2,1]    [2,3]    [3,1]    [3,2]
       │        │        │        │        │        │
    pick 3   pick 2   pick 3   pick 1   pick 2   pick 1
    [1,2,3]  [1,3,2]  [2,1,3]  [2,3,1]  [3,1,2]  [3,2,1]
       ✓        ✓        ✓        ✓        ✓        ✓
```

Each level has fewer choices than the one above, because the used indices are skipped:

```
level 0: 3 choices
level 1: 2 choices
level 2: 1 choice
         ───────
total:   3 × 2 × 1 = 6 permutations
```

### One branch in detail (the backtracking step)

```
pick 1   → visited=[T,F,F]  buffer=[1]
  pick 2 → visited=[T,T,F]  buffer=[1,2]
    pick 3 → visited=[T,T,T]  buffer=[1,2,3]   ← i == n, save it
    undo 3 → visited=[T,T,F]  buffer=[1,2]
  undo 2 → visited=[T,F,F]  buffer=[1]
  pick 3 → visited=[T,F,T]  buffer=[1,3]       ← next branch can now use 2
    pick 2 → visited=[T,T,T]  buffer=[1,3,2]  ← i == n, save it
```

The undo step is what lets index `2` be reused in a different branch.

---

## Full code

```cpp
class Solution {
public:
    void calc(vector<vector<int>>& answer, vector<int>& nums, int i,
              vector<int> buffer, vector<int> visited) {
        if (i == nums.size()) {
            answer.push_back(buffer);
            return;
        }

        for (int j = 0; j < nums.size(); j++) {
            if (visited[j] == 1) continue;
            buffer.push_back(nums[j]);
            visited[j] = 1;
            calc(answer, nums, i + 1, buffer, visited);
            buffer.pop_back();
            visited[j] = 0;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> answer;
        int n = nums.size();
        vector<int> buffer;
        vector<int> visited(n, 0);
        calc(answer, nums, 0, buffer, visited);
        return answer;
    }
};
```

---

## Complexity

- **Time:** O(n × n!). There are n! permutations, and each one costs O(n) to copy into `answer`.
- **Space:** O(n) for the recursion depth, `buffer` and `visited`, not counting the output.

## Notes

- `buffer` and `visited` are passed **by value**, so each call gets its own copy. This is why the code is correct, and it also means the `pop_back()` / `visited[j] = 0` undo lines are technically redundant. They are the right habit, though. If you switch to pass by reference (`vector<int>& buffer, vector<int>& visited`), the undo lines become essential, and it avoids copying on every call, which is faster.
- This works because the elements are distinct. With duplicates in `nums` you would need to sort and add a check to avoid repeated permutations (see Permutations II).