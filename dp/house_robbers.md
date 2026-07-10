# 🏠 House Robber — DP Approach

## 💡 Idea

At each house, you have two choices:

* **Rob it** → then you must skip the previous house.
* **Skip it** → keep the maximum money collected so far.

So for every house `i`:

```txt
dp[i] = max(
    dp[i - 2] + nums[i],   // Rob current house
    dp[i - 1]              // Skip current house
)
```

---

## 🧠 DP Meaning

```txt
dp[i] = maximum money that can be robbed from house 0 to house i
```

### Base Cases

```txt
dp[0] = nums[0]

dp[1] = max(nums[0], nums[1])
```

For the second house, choose the richer of the first two houses since they are adjacent.

---

## 🔄 Example

```txt
nums = [1, 2, 3, 1]
```

| House | Rob Current | Skip Current | Best |
| ----- | ----------: | -----------: | ---: |
| `0`   |         `1` |            — |  `1` |
| `1`   |         `2` |          `1` |  `2` |
| `2`   | `1 + 3 = 4` |          `2` |  `4` |
| `3`   | `2 + 1 = 3` |          `4` |  `4` |

Answer: `4`

---

## ⏱️ Complexity

| Type  | Complexity |
| ----- | ---------: |
| Time  |     `O(n)` |
| Space |     `O(n)` |

> This can be optimized to `O(1)` space because each step only needs the previous two answers.
