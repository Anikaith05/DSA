# Top K Sum Pairs — Max-Heap + Visited Set

## Problem

Given two arrays `a` and `b`, find the `k` largest sums formed by choosing one element from each array.

For every pair of indices `(i, j)`, the sum is:

```cpp
a[i] + b[j]
```

## Approach

### 1. Sort both arrays in descending order

```cpp
sort(a.begin(), a.end(), Compare());
sort(b.begin(), b.end(), Compare());
```

The custom comparator `a > b` sorts each array from largest to smallest. Therefore, the largest possible pair sum is at `(0, 0)`.

### 2. Use a max-heap to process the largest available sum

```cpp
priority_queue<vector<int>> pq;
pq.push({a[0] + b[0], 0, 0});
```

Each heap entry stores:

```text
{sum, i, j}
```

A `priority_queue` of vectors compares them lexicographically. This means it prioritizes the largest `sum`; if sums tie, it uses the indices as tie-breakers.

After popping `(i, j)`, consider these neighbors:

- `(i + 1, j)`
- `(i, j + 1)`

Because the arrays are sorted in descending order, moving right/down in index terms (increasing an index) leads to elements that are no larger. These neighbors are candidates for later sums.

**Important:** Push both valid neighbors. Choosing only one by comparing them can skip a pair that should be considered.

### 3. Use a `set<pair<int,int>>` to track visited index pairs

```cpp
set<pair<int,int>> visited;
visited.insert({0, 0});
```

A pair can be reached by different paths. For example, `(1, 1)` can be reached from `(1, 0)` or `(0, 1)`. Without tracking visited pairs, the same pair may be inserted into the heap more than once, producing duplicate processing.

Before pushing a neighbor, check whether its index pair is already in `visited`. If it is not, push it and mark it visited immediately.

```cpp
if (i + 1 < n && visited.find({i + 1, j}) == visited.end()) {
    pq.push({a[i + 1] + b[j], i + 1, j});
    visited.insert({i + 1, j});
}
```

Apply the same idea to `(i, j + 1)`.

#### Why use a set instead of `vector<vector<int>>`?

The original approach used:

```cpp
vector<vector<int>> visited(n, vector<int>(n, 0));
```

This initializes storage for all `n * n` possible pairs, even though we only need to explore enough pairs to find the top `k` sums.

- **2D vector:** `O(n²)` space and `O(n²)` initialization time; checking a pair is `O(1)`.
- **Ordered set:** stores only encountered pairs; each lookup/insertion is `O(log m)`, where `m` is the number of visited pairs.

The set avoids the large upfront `O(n²)` allocation. Its trade-off is slower lookup than a vector, but it is often a better fit when only a small number of pairs are explored.

### 4. Why the outer `while` condition is `!pq.empty() && sorted.size() < k`

```cpp
while (!pq.empty() && sorted.size() < k) {
    // ...
}
```

The two checks serve different purposes:

- `!pq.empty()` ensures there is a candidate to pop. Calling `pq.top()` on an empty heap is invalid.
- `sorted.size() < k` ensures we stop once we have collected `k` answers.

Each iteration pops exactly one maximum candidate and appends its sum to `sorted`. So the number of answers collected—not the current heap size—is the right stopping condition.

**Why not `while (pq.size() > k)`?** The heap contains pending candidates, not answers already collected. Its size may be less than or equal to `k` while we still need more answers, so that condition can prevent any pop and cause the loop to make no progress.

## Mistakes encountered and lessons

1. **Wrong comparator type:** `greater<int>` cannot compare `vector<int>` heap entries. The current code uses the default `priority_queue<vector<int>>`, which is a max-heap and prioritizes the first element (`sum`) lexicographically.
2. **Popping only when `pq.size() > k`:** heap size is not the number of answers. Pop once per iteration while fewer than `k` answers have been collected.
3. **Generating only one neighbor:** comparing `(i + 1, j)` with `(i, j + 1)` and pushing only one can miss valid combinations. Consider both neighbors.
4. **Not marking pairs visited:** without marking a pair when it is pushed, it can be inserted multiple times through different paths.
5. **Out-of-bounds access:** check `i + 1 < n` and `j + 1 < n` before accessing the next element.
6. **Starting at the wrong corner:** with descending sorting, start at `(0, 0)`. If sorting ascending instead, the largest pair would be at `(n - 1, n - 1)` and the traversal direction would need to change.
7. **Empty arrays / invalid `k`:** accessing `a[0]` or `b[0]` requires both arrays to be non-empty. A robust implementation should also handle `k <= 0` and ensure `k` does not exceed the number of possible pairs.

## Complexity

Let `m` be the number of distinct pairs explored before collecting `k` sums. Typically, `m` is proportional to `k` because each popped pair introduces at most two neighbors.

- Sorting: `O(n log n)` for each array, assuming both arrays have length `n`.
- Heap and set processing: `O(m log m)` overall, with at most `m` pairs stored/visited.
- Extra space: `O(m)` for the heap and visited set, plus `O(k)` for the result.

The 2D visited matrix would instead require `O(n²)` extra space, regardless of how small `k` is.

## Key takeaway

The max-heap always chooses the largest currently available sum. The visited set prevents the same index pair from entering the heap repeatedly. The loop stops based on the number of sums collected, not the number of candidates waiting in the heap.
