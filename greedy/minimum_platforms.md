# Minimum Platforms

## Problem

Given the arrival and departure times of `n` trains, find the minimum number of platforms needed so that no train has to wait.

```
arr[] = [0900, 0940, 0950, 1100, 1500, 1800]
dep[] = [0910, 1200, 1120, 1130, 1900, 2000]
Output: 3
```

A train that arrives at the exact time another departs still needs its own platform, because the departing train is still on its platform at that moment.

## Key Idea

The number of platforms needed equals the **maximum number of trains in the station at the same time** (max overlap).

Only two kinds of events change that number:

- A train **arrives**: `count++`
- A train **departs**: `count--`

If we process all events in time order and track the largest value `count` reaches, that is the answer.

## Approach (Sort + Two Pointers)

1. Sort `arr` and `dep` separately.
   - Sorting them separately loses which departure belongs to which train, but that is fine. We only care how many trains are present at a given time, which is (arrivals so far) minus (departures so far).
2. Use two pointers:
   - `i` points to the next unprocessed arrival.
   - `j` points to the next unprocessed departure.
3. At each step, compare `arr[i]` with `dep[j]`. The smaller one is the next event in real time (this is the same as merging two sorted lists).
   - If `arr[i] <= dep[j]`: a train arrives, so `count++` and `i++`.
   - Otherwise: a train leaves, so `count--` and `j++`.
4. After each step, update `maxi = max(maxi, count)`.
5. Stop when all arrivals are processed (`i == n`). The remaining departures can only lower the count.

### Why `<=`

When an arrival and a departure share the same time, the arrival must be processed first. The departing train still occupies its platform at that moment, so both trains overlap.

## Dry Run

Sorted input:

```
arr = 900, 940, 950, 1100, 1500, 1800
dep = 910, 1120, 1130, 1200, 1900, 2000
```

| i | j | compare | event | count |
|---|---|---------|-------|-------|
| 0 | 0 | 900 vs 910 | arrival | 1 |
| 1 | 0 | 940 vs 910 | departure | 0 |
| 1 | 1 | 940 vs 1120 | arrival | 1 |
| 2 | 1 | 950 vs 1120 | arrival | 2 |
| 3 | 1 | 1100 vs 1120 | arrival | **3** |
| 4 | 1 | 1500 vs 1120 | departure | 2 |
| 4 | 2 | 1500 vs 1130 | departure | 1 |
| 4 | 3 | 1500 vs 1200 | departure | 0 |
| 4 | 4 | 1500 vs 1900 | arrival | 1 |
| 5 | 4 | 1800 vs 1900 | arrival | 2 |

Maximum `count` is **3**, so 3 platforms are needed.


## Complexity

- **Time:** O(n log n), dominated by sorting. The two-pointer pass is O(n).
- **Space:** O(1) extra (sorting is done in place).

## Why Greedy / Why It's Correct

- **Lower bound:** at the peak moment, that many trains are physically in the station, so at least that many platforms are required.
- **Sufficient:** whenever a train leaves, its platform can be reused by the next arrival, so the peak count is always enough.
- The "greedy" part is always handling the earliest upcoming event immediately and never reconsidering it.