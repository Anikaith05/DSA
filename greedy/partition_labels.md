# Partition Labels

## 💡 Intuition

Think of each partition as a **box**.

A character cannot appear in two different boxes.

So, if a character inside our current box appears again later, we **must expand the box** until its last occurrence.

---

## 🧠 Approach

### 1. Store the last occurrence of every character

```cpp
for(int i=0;i<n;i++){
    mp[s[i]]=i;
}
```

Example:

```text
s = a b a b c b a c a d e f e g d e

a → 8
b → 5
c → 7
d → 13
e → 15
f → 11
g → 14
```

---

### 2. Start a partition

Start at index `L`.

The first character determines the initial boundary:

```text
R = last occurrence of s[L]
```

For example:

```text
a b a b c b a c a
↑               ↑
L               R
```

Since `a` last occurs at `8`:

```text
L = 0
R = 8
```

---

### 3. Expand the partition if necessary

Scan every character from `L` to `R`.

If:

```cpp
mp[s[j]] > R
```

then that character appears outside our current box.

So we expand:

```cpp
R = mp[s[j]];
```

Visual:

```text
Current:

[──────────]
L          R


Found a character whose last occurrence is here:

[────────────────────]
L                    new R
```

Keep doing this until **nothing inside the partition extends beyond `R`**.

---

### 4. Commit the partition

Once:

```text
last occurrence of every character ≤ R
```

we can safely cut:

```text
[ a b a b c b a c a ] | [ ... ]
  └──── partition ────┘
```

Then start the next partition at:

```cpp
L = R + 1;
```

---

## 🎯 Greedy Criterion

> **Close the partition at the earliest position where every character inside it has its last occurrence within the partition.**

We never need to extend further than necessary.

---

## 🔥 Pattern

```text
Find last occurrences
        ↓
Start partition
        ↓
Set R using first character
        ↓
Scan L → R
        ↓
Does any character extend beyond R?
       ↙        ↘
     YES         NO
      ↓           ↓
 Expand R      Close partition
      ↓           ↓
   Continue     Start next
```

---

## ⏱️ Complexity

* **Time:** `O(n)`
* **Space:** `O(k)` where `k` = number of distinct characters

For lowercase English letters, `k ≤ 26`, so auxiliary space is effectively `O(1)`.

---

## 🔑 Takeaway

The important idea is **not** just "find the last occurrence."

It's:

> **Use last occurrences to dynamically determine how far the current partition must extend, then greedily cut as soon as the partition becomes self-contained.**
