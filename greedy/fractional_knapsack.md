# 🎒 Fractional Knapsack — Greedy Approach

> Maximize the total value that can be carried when **items can be divided into fractions**.

---

## 💡 Core Idea

The greedy choice is:

**Pick the item with the highest `value / weight` first.**

```text
        Value
Ratio = ───────
        Weight

Higher ratio → Better item to take
```

### 🔄 Example

```text
Item       Value    Weight    Value/Weight
───────────────────────────────────────────
A           60       10          6.0  ⭐
B          100       20          5.0
C          120       30          4.0
```

Capacity = `50`

```text
Take A → 10 kg → ₹60
Take B → 20 kg → ₹100
Take C → 20/30 of C → ₹80
────────────────────────────
Total   = 50 kg → ₹240
```

---

## 🧠 Algorithm

```text
1. Create (value, weight) pairs
            ↓
2. Calculate value/weight ratio
            ↓
3. Sort items by ratio ↓
            ↓
4. Take complete items while possible
            ↓
5. If remaining capacity < weight
   → take the required fraction
            ↓
6. Return total value
```

---

## 🛠️ Key Code

### Custom Comparator

```cpp
class Compare {
public:
    bool operator()(const item& a, const item& b) {
        return ((1.00 * a.val) / a.wt) >
               ((1.00 * b.val) / b.wt);
    }
};
```

This sorts items by:

```text
value/weight ↓
```

### Taking Items

```cpp
if(items[i].wt < capacity) {
    value += items[i].val;
    capacity -= items[i].wt;
}
else {
    value += (1.00 * capacity / items[i].wt)
             * items[i].val;
    break;
}
```

---

## ⏱️ Complexity

| Operation   |     Complexity |
| ----------- | -------------: |
| Build items |         `O(n)` |
| Sort        |   `O(n log n)` |
| Traverse    |         `O(n)` |
| **Total**   | **O(n log n)** |
| Extra Space |       **O(n)** |

---

## ⚠️ Important

### Why Greedy works?

Because fractions are allowed.

```text
0.5 × item
0.25 × item
0.75 × item
```

So we can always take the item giving the **maximum value per unit weight**.

> ❌ This greedy strategy does **not** generally work for **0/1 Knapsack**, where an item must be taken completely or not at all.

---

## 📌 Pattern to Remember

```text
FRACTIONAL KNAPSACK

Fraction allowed?
      ↓
    YES
      ↓
value / weight
      ↓
Sort descending
      ↓
Take as much as possible
```

**Pattern:** `Greedy + Sorting + Ratio`
