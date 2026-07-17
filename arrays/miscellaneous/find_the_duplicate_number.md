# 🔍 LeetCode 287 — Find the Duplicate Number

<div align="center">

![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange)
![Technique](https://img.shields.io/badge/Technique-Floyd's%20Cycle%20Detection-blue)
![Time](https://img.shields.io/badge/Time-O(n)-brightgreen)
![Space](https://img.shields.io/badge/Space-O(1)-red)

</div>

---

# 💡 Key Observation

Instead of thinking of the array as an array...

👉 Think of it as a **Linked List**.

Every **index** is a node.

Every **value** is the next node.

```
Index : 0   1   2   3   4
Value : 1   3   4   2   2
```

becomes

```
0 → 1 → 3 → 2 → 4
          ↑     │
          └─────┘
```

🎯 The duplicate number creates a **cycle**.

---

# ❓Why is there always a cycle?

We have:

- ✅ n + 1 nodes
- ✅ Values only from **1...n**
- ✅ Every node points to exactly one next node

Since there are more nodes than possible destinations,

**two nodes must eventually point to the same place.**

Once paths merge, they can never separate.

Eventually they loop forever.

```
      A
       \
        \
         C → D → E
        ↑       │
        └───────┘
```

This is exactly what Floyd's algorithm needs.

---

# 🐢🐇 Floyd's Cycle Detection

The algorithm has **2 phases**.

---

# Phase ① — Find an Intersection

Use two pointers.

🐢 Slow

- Moves **1 step**

🐇 Fast

- Moves **2 steps**

```
slow = 1 step

fast = 2 steps
```

Eventually...

```
🐢
 ↓
A → B → C → D
      ↑     │
      └─────┘
          ↑
         🐇
```

They meet somewhere **inside the cycle**.

⚠️ This is **NOT necessarily the duplicate.**

It only proves that a cycle exists.

---

# Phase ② — Find the Entrance

After the meeting:

Move one pointer back to the beginning.

```
Head

↓

0 → 1 → 3 → 2 → 4
          ↑     │
          └─────┘

            ↑
          Slow
```

Now move **both pointers one step at a time.**

```
Head → one step

Slow → one step
```

Eventually...

```
          🎯
          2
```

They meet at the **start of the cycle**.

The start of the cycle is the **duplicate number.**

---

# 🧠 Why does this work?

When slow and fast meet,

the mathematics of Floyd's algorithm guarantees:

```
Distance(Start → Cycle Entrance)

=

Distance(Meeting Point → Cycle Entrance)
```

Therefore,

moving both pointers one step at a time makes them arrive at the entrance together.

---

# 🚩 Interview Pattern

Whenever you see these clues together...

✅ n + 1 elements

✅ Values in **[1, n]**

✅ Exactly one duplicate

✅ Cannot modify the array

✅ O(1) extra space

Your brain should immediately think:

> 💡 "Can I treat this array as a linked list?"

If yes...

➡️ Floyd's Cycle Detection is probably the intended solution.

---

# 📈 Complexity

| Operation | Complexity |
|-----------|------------|
| Time | 🟢 O(n) |
| Space | 🔵 O(1) |

---

# 🎯 Revision Checklist

- [ ] Array can be viewed as a linked list
- [ ] Index = Node
- [ ] Value = Next Pointer
- [ ] Duplicate creates the cycle
- [ ] Phase 1 → Find an intersection
- [ ] Phase 2 → Find the cycle entrance
- [ ] Cycle entrance = Duplicate number
- [ ] Time → O(n)
- [ ] Space → O(1)

---

# ⭐ One-Line Memory Trick

> **Index = Node → Value = Next → Duplicate = Cycle → Floyd finds the Cycle Entrance = Answer**

---

<div align="center">

## 🚀 Think Graphs, Not Arrays.

</div>