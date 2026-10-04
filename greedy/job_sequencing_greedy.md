# Job Sequencing Problem (Sorting + Min-Heap)

## Problem

Each job takes **1 unit of time**, has a **deadline** and a **profit**.
A job earns its profit only if it finishes **on or before its deadline**.
Pick jobs to **maximize total profit**. Return `{jobs_done, total_profit}`.

```
deadline = {2, 1, 2, 1, 1}
profit   = {100, 19, 27, 25, 15}
output   = {2, 127}
```

---

## Idea in One Line

> Sort by deadline, keep a **min-heap of chosen profits**. If there is no free slot, kick out the cheapest chosen job, but only if the new one is more profitable.

---

## Why a Min-Heap?

```
 heap size  = number of jobs chosen = slots already used
 heap top   = the LEAST profitable chosen job = easiest to drop
```

---

## Algorithm

```
1. Pair up  (deadline, profit)
2. Sort pairs by deadline (ascending)
3. For each job:

        deadline > pq.size() ?
              |
      +-------+--------+
     YES               NO  (slots full)
      |                 |
   push profit     profit > pq.top() ?
                        |
                 +------+------+
                YES           NO
                 |             |
          pop top, push     skip job
          new profit
4. Drain the heap: count jobs, sum profits
```

---

## Why `deadline > pq.size()` Means "Free Slot"?

If the heap has `k` jobs, they occupy slots `1..k`.
The next free slot is `k + 1`, and it works only if `k + 1 <= deadline`:

```
k + 1 <= deadline   <=>   deadline > k   <=>   deadline > pq.size()
```

```
Slots:     | 1 | 2 | 3 | 4 |
Heap (k=2):| X | X |   |   |
                     ^
                     next free slot = 3
Job with deadline 2 -> 2 > 2 false -> no room, must replace
Job with deadline 3 -> 3 > 2 true  -> push
```

---

## Why Sorting by Deadline Makes Swapping Safe

Jobs are processed in increasing deadline order, so every chosen job has a deadline **<=** the current job's deadline.
Removing any chosen job frees a slot that the current job can legally use. So dropping the **lowest-profit** job is always the best swap.

---

## Dry Run

Sorted by deadline: `(1,15) (1,19) (1,25) (2,27) (2,100)`

| Job       | `deadline > size`? | Action                      | Heap (profits) |
|-----------|--------------------|-----------------------------|----------------|
| (1, 15)   | 1 > 0 yes          | push                        | {15}           |
| (1, 19)   | 1 > 1 no, 19 > 15  | replace 15 with 19          | {19}           |
| (1, 25)   | 1 > 1 no, 25 > 19  | replace 19 with 25          | {25}           |
| (2, 27)   | 2 > 1 yes          | push                        | {25, 27}       |
| (2, 100)  | 2 > 2 no, 100 > 25 | replace 25 with 100         | {27, 100}      |

Result: **2 jobs, profit 27 + 100 = 127**

---

## Code

```cpp
struct item { int deadline; int profit; };

struct Compare {                       // sort by deadline (asc)
    bool operator()(const item& a, const item& b) {
        return a.deadline < b.deadline;
    }
};
struct Compare1 {                      // min-heap on profit
    bool operator()(const item& a, const item& b) {
        return a.profit > b.profit;
    }
};

class Solution {
  public:
    vector<int> jobSequencing(vector<int>& deadline, vector<int>& profit) {
        vector<item> items;
        int n = deadline.size();
        for (int i = 0; i < n; i++)
            items.push_back({deadline[i], profit[i]});

        sort(items.begin(), items.end(), Compare());

        priority_queue<item, vector<item>, Compare1> pq;

        for (int i = 0; i < n; i++) {
            if (items[i].deadline > pq.size())          // free slot
                pq.push(items[i]);
            else if (items[i].profit > pq.top().profit) { // replace cheapest
                pq.pop();
                pq.push(items[i]);
            }
        }

        int sum = 0, c = 0;
        while (!pq.empty()) {
            sum += pq.top().profit;
            c++;
            pq.pop();
        }
        return {c, sum};
    }
};
```

---

## Complexity

| | Cost | Reason |
|---|---|---|
| Time  | `O(n log n)` | sort + `n` heap operations |
| Space | `O(n)`       | items array + heap |

## Takeaways

- Heap **size** = slots used. Heap **top** = weakest chosen job.
- Sorting by deadline guarantees any swap keeps the schedule valid.
- Only count and total profit are needed, so exact slot positions are never stored.