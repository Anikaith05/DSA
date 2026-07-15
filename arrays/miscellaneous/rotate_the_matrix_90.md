# 🔄 Rotate Image (LeetCode 48)

## 🎯 Idea

Rotate the matrix **layer by layer (ring by ring)**. For every element
on the **Top** edge, rotate four elements at once:

Top ← Left ← Bottom ← Right ← Top

------------------------------------------------------------------------

## 📍 Four Positions

For a top element `(i, j)`:

  Position    Coordinates
  ----------- ------------------
  🟦 Top-left      `(i, j)`
  🟩 Top-Right    `(j, n-1-i)`
  🟥 Bottom-right   `(n-1-i, n-1-j)`
  🟨 Bottom-Left     `(n-1-j, i)`

------------------------------------------------------------------------

## 🧠 Algorithm

1.  Traverse each layer from outer to inner.
2.  Traverse only the top edge of the current layer.
3.  Save the top element.
4.  Perform one 4-way cyclic swap.
5.  Repeat for every layer.

------------------------------------------------------------------------

## ⏱️ Complexity

-   **Time:** `O(n²)`
-   **Space:** `O(1)` (In-place)

------------------------------------------------------------------------
# ❌ Mistakes I Made

### 1. Wrong Left & Right Coordinates

I originally used the wrong indices for the **Left** and **Right** positions.

The mistake was that the calculated coordinates **did not actually lie on the left or right edges of the current layer**.

For a top element `(i, j)`:

```
Top    → (i, j)

Right  → must always be on the RIGHT edge
          (fixed column = n-1-i)

Bottom → must always be on the BOTTOM edge
          (fixed row = n-1-i)

Left   → must always be on the LEFT edge
          (fixed column = i)
```

### ✔️ Rule to Remember

- **Top & Bottom** → **Row is fixed**
- **Left & Right** → **Column is fixed**

If your **Right** coordinate doesn't have the **rightmost column** of the current layer, or your **Left** coordinate doesn't have the **leftmost column** of the current layer, your indices are wrong.

------------------------------------------------------------------------

### 2. Wrong Outer Loop

❌ Iterated until `i <= n/2`

✅ Correct: - Process only existing layers. - `i < n/2`

------------------------------------------------------------------------

### 3. Wrong Inner Loop

❌ Included the last element of the top row.

That rotates the corner twice.

✅ Traverse only until **before** the last column of the current layer(n-i-1).

------------------------------------------------------------------------

## 💡 Revision Tips

-   Think **Top, Right, Bottom, Left**, not formulas.
-   Right edge ⇒ column is fixed.
-   Left edge ⇒ column is fixed.
-   Top & Bottom ⇒ row is fixed.
-   One iteration = one 4-way swap.
-   One layer finishes before moving inward.

------------------------------------------------------------------------

## ⭐ Mental Picture

Clockwise movement of values:

**bottom-Left → Top-left → top-Right → Bottom-right → bottom-Left**
