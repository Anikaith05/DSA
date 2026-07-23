# 🗳️ LeetCode 229 – Majority Element II

> **Boyer-Moore Voting Algorithm**  
> ⏱️ Time: **O(n)** | 💾 Space: **O(1)**

---

## 💡 Key Observation

An element appearing more than **⌊n/3⌋** times can have **at most 2** candidates.

**Why?**

```
> n/3 + > n/3 + > n/3 > n ❌
```

So, maintain only **2 candidates**.

---

## 🚦Algorithm

For every number:

```text
1️⃣ Already Candidate?
    → Increment count

2️⃣ Empty Slot?
    → Assign candidate

3️⃣ Otherwise
    → Decrement both counts
```

---

## 📌 Correct Order

```cpp
if(nums[i] == num1)
    count1++;

else if(nums[i] == num2)
    count2++;

else if(count1 == 0)
{
    num1 = nums[i];
    count1 = 1;
}

else if(count2 == 0)
{
    num2 = nums[i];
    count2 = 1;
}

else
{
    count1--;
    count2--;
}
```

> ⚠️ **Always Match → Fill → Cancel**

---

## ✅ Why Match First?

Suppose

```
num1 = 5
count1 = 3

num2 is empty

Current = 5
```

If you fill before matching:

```
num1 = 5
num2 = 5 ❌
```

Instead, increase `count1`.

---

## 🔄 Second Pass

The first pass gives **possible candidates only**.

Verify their frequencies.

```cpp
if(freq > n/3)
    answer.push_back(candidate);
```

---

## 📊 Complexity

| Time | Space |
|------|-------|
| O(n) | O(1) |

---

# 🌍 Generalization (n/k)

For elements occurring more than **n/k** times:

- Maintain **k−1 candidates**
- Maintain **k−1 counts**

Algorithm:

```text
Match
   ↓
Fill Empty Slot
   ↓
Decrement All Counts
   ↓
Verify
```

---

## 🧠 Memory Trick

```text
MATCH
  ↓
FILL
  ↓
CANCEL
  ↓
VERIFY
```

**Match → Fill → Cancel → Verify** ✅