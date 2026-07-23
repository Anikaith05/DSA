# 🔗 Longest Consecutive Sequence (LeetCode 128)

## 🚀 Approach
Instead of sorting (`O(n log n)`), use an **unordered_set** for **O(1)** average lookups.

The trick is to **only start counting from the beginning of a sequence**.

A number `x` is the start of a sequence **only if `x - 1` is not present**.

---

## 💡 Algorithm

1. Insert all elements into an `unordered_set`.
2. Iterate through every element in the set.
3. If `x - 1` is **not** in the set:
   - `x` is the start of a new sequence.
   - Keep checking `x + 1`, `x + 2`, ... until the sequence ends.
   - Count its length.
4. Update the maximum length.

---

## 🔍 Dry Run

### Input

```text
[100, 4, 200, 1, 3, 2]
```

### HashSet

```text
{100, 4, 200, 1, 3, 2}
```

### Traversal

```text
100
└── 99 doesn't exist ✅
    Length = 1

4
└── 3 exists ❌
    Skip

200
└── 199 doesn't exist ✅
    Length = 1

1
└── 0 doesn't exist ✅
    1 → 2 → 3 → 4
    Length = 4

3
└── 2 exists ❌
    Skip

2
└── 1 exists ❌
    Skip
```

**Answer = 4**

---

## ❌ Initial Mistake (TLE)

I started expanding from **every element**.

Example:

```text
1 2 3 4 5
```

Work done:

```text
From 1 → 1 check
From 2 → 2 checks
From 3 → 3 checks
From 4 → 4 checks
From 5 → 5 checks
```

Total work:

```text
1 + 2 + 3 + 4 + 5 = O(n²)
```

This causes **Time Limit Exceeded**.

---

## ✅ Optimization

Only start from numbers that **don't have a predecessor**.

```cpp
if (st.find(x - 1) == st.end())
```

Then expand only in the forward direction.

```cpp
while (st.find(curr + 1) != st.end()) {
    curr++;
    len++;
}
```

Now every sequence is traversed **exactly once**.

---

## ⏱️ Complexity

| Operation | Complexity |
|-----------|------------|
| Build HashSet | **O(n)** |
| Iterate through set | **O(n)** |
| Total expansion | **O(n)** |

### Overall Complexity

- **Time:** `O(n)`
- **Space:** `O(n)`

---

## ⭐ Key Takeaways

- ❌ Don't sort (`O(n log n)`).
- ✅ Use `unordered_set` for constant-time lookups.
- ✅ Start counting **only** when `x - 1` doesn't exist.
- ✅ Expand only in the forward direction.
- ✅ Each element is visited at most once.

---

## 💻 Solution

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st(nums.begin(), nums.end());

        int maxLen = 0;

        for (int x : st) {
            if (st.find(x - 1) == st.end()) {
                int curr = x;
                int len = 1;

                while (st.find(curr + 1) != st.end()) {
                    curr++;
                    len++;
                }

                maxLen = max(maxLen, len);
            }
        }

        return maxLen;
    }
};
```

## 🧠 Pattern

> **Hash Set → Find Start (`x-1` absent) → Expand Forward (`x+1`) → Update Answer**