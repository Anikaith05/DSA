# Top K Frequent Elements — C++

## 💡 Approach

Use a **frequency map + min-heap of size `k`**.

```text
nums
  │
  ▼
Count frequencies ──► freq[num] = count
  │
  ▼
Push each distinct number into a min-heap
  │
  ├── heap size > k? ──► Pop the least frequent number
  │
  ▼
Remaining heap elements = k most frequent numbers
```

### Example

For `nums = [1,1,1,2,2,3]`, `k = 2`:

| Number | Frequency |
|---:|---:|
| 1 | 3 |
| 2 | 2 |
| 3 | 1 |

The heap keeps the two most frequent values: `1` and `2`.

> The output order is not guaranteed; any order of the top `k` elements is acceptable.

## 🔧 The custom comparator

```cpp
struct Compare {
    unordered_map<int, int>& freq;

    Compare(unordered_map<int, int>& f) : freq(f) {}

    bool operator()(const int& a, const int& b) {
        return freq[a] > freq[b];
    }
};
```

- `unordered_map<int, int>& freq;` — stores a **reference** to the frequency map, not a copy.
- `Compare(unordered_map<int, int>& f) : freq(f) {}` — constructor; connects `freq` to the map passed in as `f`.
- `operator()(a, b)` — lets an object of `Compare` be called like a function.
- `freq[a] > freq[b]` — puts the **lower-frequency** value at the top, creating a min-heap by frequency.

### Passing the map to the heap

```cpp
Compare comp(freq);
priority_queue<int, vector<int>, Compare> pq(comp);
```

```text
freq map ──► comp (Compare object) ──► pq (priority queue)
                  │
                  └── holds a reference to freq
```

1. `Compare comp(freq);` creates the comparator and gives it access to `freq`.
2. `pq(comp);` passes that comparator object to the priority queue.
3. The heap calls the comparator whenever it needs to order values.

## ⏱️ Complexity

Let `n` be the number of input elements and `m` the number of distinct elements.

- **Time:** `O(n + m log k + k log k)` average; commonly stated as **`O(n log k)`** when `k ≥ 2`.
- **Space:** `O(m + k)`, which is **`O(n)`** in the worst case.

## ⚠️ Small detail

The comparator holds a reference, so `freq` must remain alive while the priority queue uses it. In this solution, `freq` is declared before `comp` and `pq`, so its lifetime is long enough.
