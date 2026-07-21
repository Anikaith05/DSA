# 🗳️ 169. Majority Element (Moore's Voting Algorithm)

<p align="center">
  <img src="https://img.shields.io/badge/Time-O(n)-brightgreen">
  <img src="https://img.shields.io/badge/Space-O(1)-blue">
  <img src="https://img.shields.io/badge/Difficulty-Easy-success">
</p>

---

# 🎯 Key Idea

> ## ⭐ **Since the majority element appears more than all other elements combined, it will always have some votes left at the end.**

The algorithm **cancels out one occurrence of the majority element with one occurrence of any other element**.

Eventually, only the majority element survives.

---

# 🧠 Intuition

Think of it as an election.

- ✅ Same element → **+1 Vote**
- ❌ Different element → **-1 Vote**
- 🔄 Votes become **0** → Choose a **new candidate**

---

# 📊 Visual Example

### Input

```text
[2, 2, 1, 1, 1, 2, 2]
```

| Number | Candidate | Votes |
|:------:|:---------:|:-----:|
|2|2|1|
|2|2|2|
|1|2|1|
|1|2|0 🔄|
|1|1|1|
|2|1|0 🔄|
|2|2|1|

### ✅ Answer = 2

---

# ⚔️ Vote Cancellation

```text
2 2 2 2
1 1 1

Cancel one-by-one

2 ❌ 1
2 ❌ 1
2 ❌ 1

Remaining

2 ✅
```

No matter how the cancellations happen, the majority element **cannot disappear**.

---

# 🔄 Algorithm Flow

```text
Start

count = 0

        │
        ▼
count == 0 ?
        │
      Yes
        │
candidate = current element
        │
        ▼
Is current == candidate ?
      │          │
     Yes        No
      │          │
   count++    count--
      │
      ▼
Continue
```

---

# 📌 Dry Run

| Step | Element | Candidate | Count |
|:---:|:------:|:---------:|:----:|
|1|2|2|1|
|2|2|2|2|
|3|1|2|1|
|4|1|2|0|
|5|1|1|1|
|6|2|1|0|
|7|2|2|1|

Final Candidate → **2**

---

# ✅ Why It Works

The count is **NOT the frequency** of the candidate.

It represents the **net votes remaining after all cancellations**.

Because the majority element occurs **more than ⌊n/2⌋ times**, it always survives the cancellation process.

---

# ⏱️ Complexity

| Operation | Complexity |
|-----------|-----------:|
| Time | **O(n)** |
| Space | **O(1)** |

---

# 💡 Remember

✅ Count reaches **0** → Pick a new candidate.

✅ Same element → Increase votes.

✅ Different element → Cancel one vote.

⭐ **The majority element always survives because it appears more times than every other element combined.**