# 📈 Best Time to Buy and Sell Stock (LC 121)

## ✅ Pattern

| Pattern | Yes / No |
|---------|----------|
| Greedy | ✅ |
| Single Pass | ✅ |
| Running Minimum | ✅ |
| Two Pointers | ❌ |
| Sliding Window | ❌ |
| Dynamic Programming | ❌ |

---

## 💡 Core Idea

Keep track of the **minimum price seen so far**.

For every price:

```
profit = currentPrice - minPrice
```

Update the maximum profit.

---

## 🧠 Greedy Insight

Buying at a lower price is **always** better than buying at a higher price.

So whenever a smaller price appears:

```
minPrice = currentPrice
```

This local decision always leads to the global optimum.

---

## ⚙️ Algorithm

1. Initialize
   - `minPrice = INT_MAX`
   - `maxProfit = 0`
2. Traverse the array once.
3. Update `minPrice`.
4. Compute current profit.
5. Update `maxProfit`.

---

## ❌ Mistakes I Made

| Mistake | Fix |
|----------|-----|
| Used O(n²) by checking every future price | Maintain minimum price while traversing |
| Used `INT_MIN` for future maximum | Unnecessary with greedy approach |
| Thought it was Two Pointers | It's Greedy |
| Thought it was Sliding Window | No window is maintained |
| Returned negative profit | Initialize `maxProfit = 0` |

---

## ⏱ Complexity

| Time | Space |
|------|-------|
| **O(n)** | **O(1)** |

---

## 📝 Revision Keywords

- Greedy
- Running Minimum
- One Pass
- Buy Low → Sell High
- Maximum Profit