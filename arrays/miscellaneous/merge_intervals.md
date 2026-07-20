# 🔥 LeetCode 56 — Merge Intervals

<div align="center">

![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange)
![Pattern](https://img.shields.io/badge/Pattern-Sorting%20%2B%20Greedy-blue)
![Time](https://img.shields.io/badge/Time-O(n%20log%20n)-brightgreen)
![Space](https://img.shields.io/badge/Space-O(n)-yellow)

</div>

---

# 🧠 Core Idea

> **Sort all intervals by their starting point.**  
> Then process them from left ➜ right, maintaining a list of merged intervals.

Since the intervals are sorted, the current interval can only overlap with the **last merged interval**.

---

# 📊 Example

### Before Sorting

| Intervals |
|-----------|
| `[1,3]` |
| `[2,6]` |
| `[8,10]` |
| `[8,9]` |
| `[9,11]` |
| `[15,18]` |
| `[2,4]` |
| `[16,17]` |

⬇️

### After Sorting

| Order |
|-------|
| `[1,3]` |
| `[2,4]` |
| `[2,6]` |
| `[8,9]` |
| `[8,10]` |
| `[9,11]` |
| `[15,18]` |
| `[16,17]` |

---

# 🚶 Dry Run

| Current Interval | Last Merged | Action | Answer |
|------------------|-------------|--------|--------|
| `[1,3]` | — | Add | `[1,3]` |
| `[2,4]` | `[1,3]` | Merge | `[1,4]` |
| `[2,6]` | `[1,4]` | Merge | `[1,6]` |
| `[8,9]` | `[1,6]` | Add | `[1,6] , [8,9]` |
| `[8,10]` | `[8,9]` | Merge | `[8,10]` |
| `[9,11]` | `[8,10]` | Merge | `[8,11]` |
| `[15,18]` | `[8,11]` | Add | `[15,18]` |
| `[16,17]` | `[15,18]` | Merge | `[15,18]` |

---

# ✅ Final Answer

| Merged Intervals |
|------------------|
| `[1,6]` |
| `[8,11]` |
| `[15,18]` |

---

# 🎯 Overlap Rule

| Condition | Meaning |
|-----------|---------|
| `current.start <= lastMerged.end` | ✅ Overlap → Merge |
| `current.start > lastMerged.end` | ❌ No Overlap → Add New Interval |

---

# 📌 Algorithm

| Step | Action |
|------|--------|
| 1️⃣ | Sort intervals by start time |
| 2️⃣ | Create an empty answer list |
| 3️⃣ | Traverse each interval |
| 4️⃣ | If answer is empty → Add interval |
| 5️⃣ | Else check overlap with last merged interval in the answer_list |
| 6️⃣ | If overlap → Extend the ending point, create the new merged interval and push it onto the answer_list |
| 7️⃣ | Else → Push as a new interval |

---

# ❌ Common Mistakes

| Mistake | Why It's Wrong |
|----------|----------------|
| Forgetting to sort | Merge logic fails |
| Comparing with every previous interval | Unnecessary; only compare with the last merged interval |
| Using `<` instead of `<=` | Adjacent intervals won't merge correctly |
| Creating a new interval during overlap | Results in duplicate ranges |

---

# ⚡ Complexity

| Operation | Complexity |
|-----------|------------|
| Sorting | **O(n log n)** |
| Single Traversal | **O(n)** |
| Total | **O(n log n)** |
| Extra Space | **O(n)** (Output Array) |

---

# 🧩 Pattern Recognition

If a problem mentions...

| Keyword | Think |
|----------|-------|
| Intervals | 📌 Sort First |
| Meeting Rooms | 📌 Merge / Compare |
| Time Ranges | 📌 Greedy |
| Scheduling | 📌 Last Processed Interval |
| Overlapping Segments | 📌 Sorting + Greedy |

---

# 📝 Interview Summary

| Question | Answer |
|----------|--------|
| Why sort first? | So overlapping intervals become adjacent. |
| Why compare only with the last merged interval? | Previous overlaps are already merged into it. |
| Is this optimal? | ✅ Yes. Sorting is unavoidable, giving **O(n log n)** overall. |
| Main Pattern | **Sorting + Greedy** |

---

# 🚀 One-Line Revision

> **Sort ➜ Compare with the last merged interval ➜ Merge if overlapping ➜ Otherwise start a new interval.**