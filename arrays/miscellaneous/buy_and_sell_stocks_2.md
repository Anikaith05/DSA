# Best Time to Buy and Sell Stock II

## Problem

You are given an array `prices` where:

* `prices[i]` = price of the stock on day `i`
* You can buy and sell the stock multiple times.
* You can hold at most **one stock at a time**.
* The goal is to maximize total profit.

---

## Approach

The main idea is:

> **Whenever the stock price goes up from one day to the next, we capture that profit.**

Think of a stock going through a valley → rising → peak.

For example:

```text
Prices:
      1     5     7
      ↓     ↑     ↑
     Buy         Sell
```

We want to:

1. **Buy when the price starts rising** (after a fall/low point).
2. **Hold the stock while the price keeps increasing.**
3. **Sell when we reach the peak**, before the price starts falling.
4. Repeat this process for the next rise.

For example:

```text
Prices = [7, 1, 5, 3, 6, 4]

          Buy → Sell
             1 → 5
             
                   Buy → Sell
                      3 → 6
```

Profit:

```text
(5 - 1) + (6 - 3)
= 4 + 3
= 7
```

---

## The Key Observation

We don't actually need to explicitly find the valley and the peak.

Suppose the prices are:

```text
1 → 2 → 3 → 4 → 5
```

Buying at `1` and selling at `5` gives:

```text
5 - 1 = 4
```

But we can also think of it as:

```text
(2 - 1) + (3 - 2) + (4 - 3) + (5 - 4)

= 1 + 1 + 1 + 1

= 4
```

So:

> **The total profit from one continuous increasing sequence is exactly the sum of all positive consecutive differences.**

That's exactly what the code does.

---

## How the Code Works

```cpp
int profit = 0;

for(int i = 1; i < n; i++){
    if(prices[i] > prices[i-1]){
        profit += prices[i] - prices[i-1];
    }
}
```

For every pair of consecutive days:

```text
prices[i-1] → prices[i]
```

### If the price increased:

```cpp
prices[i] > prices[i-1]
```

We add:

```cpp
prices[i] - prices[i-1]
```

This means we are capturing the profit from that upward movement.

### If the price decreased:

```text
prices[i] < prices[i-1]
```

We do nothing.

The fall tells us that the previous upward trend has ended, so conceptually we would have sold before that fall.

---

## Dry Run

Consider:

```text
prices = [7, 1, 5, 3, 6, 4]
```

| Day | Price |     Change | Action         | Profit |
| --- | ----: | ---------: | -------------- | -----: |
| 0   |     7 |          - | —              |      0 |
| 1   |     1 | 1 - 7 = -6 | Ignore         |      0 |
| 2   |     5 | 5 - 1 = +4 | Capture profit |      4 |
| 3   |     3 | 3 - 5 = -2 | Ignore         |      4 |
| 4   |     6 | 6 - 3 = +3 | Capture profit |      7 |
| 5   |     4 | 4 - 6 = -2 | Ignore         |      7 |

Final answer:

```text
7
```

---

## Important Intuition

You can visualize the process like this:

```text
Price

7  ●
   |
5  |       ● ← Sell
   |      /
3  |     ● ← Buy
   |    / \
1  | ● /   \
   +----------------
     0 1 2 3 4 5
```

We don't literally store:

```text
buy = 1
sell = 5
```

Instead, we capture:

```text
1 → 5

= (5 - 1)

= (2 - 1) + (3 - 2) + (4 - 3) + (5 - 4)
```

So the code automatically captures the entire upward movement.

---

## Why We Ignore Falling Prices

Consider:

```text
5 → 3
```

There is no profit to be made from this movement.

Therefore:

```cpp
if(prices[i] > prices[i-1])
```

ensures that only profitable upward movements are added.

---

## Complexity

### Time Complexity

```text
O(n)
```

We traverse the array exactly once.

### Space Complexity

```text
O(1)
```

We only use the `profit` variable and a few other variables.

---


## One-Line Summary

> **Add every positive price difference — this is equivalent to buying at the beginning of every rising segment and selling at its peak.**
