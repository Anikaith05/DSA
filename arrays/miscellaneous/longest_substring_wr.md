# 🚀 Longest Substring Without Repeating Characters (Sliding Window)

## Pattern

**Dynamic Sliding Window + Hash Set**

---

## Idea

Maintain a window that always contains **unique characters**.

```text
left              right
 ↓                  ↓
a b c a b c b b

Window = s[left...right]
```

The window is represented by:

* `left` → start of the window
* `right` → end of the window
* `unordered_set<char>` → stores the current window state (characters inside the window)

---

## Algorithm

```text
Expand Window
      ↓
Duplicate?
      ↓
 No ─────────► Update Answer
      │
     Yes
      │
      ▼
Remove from Left
Until No Duplicate
```

---

## Dry Run

```text
s = "abcabcbb"

Window = "a"      ✔ ans = 1
Window = "ab"     ✔ ans = 2
Window = "abc"    ✔ ans = 3

Next character = 'a'

Window = "abca"   ❌ duplicate

Remove from left

"bca"             ✔

Continue...
```

---

## Why `while` instead of `if`?

```text
Window = abcdefgd

Duplicate = d

Remove a ❌
Remove b ❌
Remove c ❌
Remove d ✅
```

Sometimes removing one character isn't enough, so we keep shrinking until the window becomes valid.

---

## Window Invariant

After every iteration:

* ✅ Window contains **no duplicate characters**
* ✅ The set contains **exactly** the characters in the current window

---

## Common Mistakes

### ❌ Window Length

```cpp
right - left
```

✅ Correct:

```cpp
right - left + 1
```

because both `left` and `right` are part of the window.

---

### ❌ `left` & `right` Don't Store the Window

They only define the **boundaries**.

The actual window state is maintained by:

```cpp
unordered_set<char> st;
```

---

### ❌ Why Remove from the Left?

When a duplicate appears:

```text
abca
```

Don't remove the new `'a'`.

Instead:

```text
abca
 ↓
bca
```

Keep moving `left` until the duplicate is removed.

---

## Complexity

* **Time:** `O(n)`
* **Space:** `O(min(n, character set))`

---

## Generic Dynamic Sliding Window

```cpp
for (right = 0; right < n; right++) {

    add(arr[right]);

    while (window_is_invalid()) {
        remove(arr[left]);
        left++;
    }

    update_answer();
}
```

> **Remember:** **Expand → Check → Shrink → Update**
