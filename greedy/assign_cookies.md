# Assign Cookies — Greedy Approach

## Approach

We want to **maximize the number of content children**.

* `g[i]` = minimum cookie size required by child `i`
* `s[j]` = size of cookie `j`

### Greedy Idea

Sort both arrays in increasing order.

Then use two pointers:

* `i` → current child
* `j` → current cookie

For each cookie:

1. If `s[j] >= g[i]`, the cookie can satisfy the child.

   * Assign it.
   * Move both pointers.
   * Increment the count.
2. Otherwise, the cookie is too small for the current child.

   * Discard the cookie.
   * Move only `j`.

### Why Greedy Works

We always consider the **smallest available cookie** for the **least demanding child**.

* If the cookie can satisfy the child, assigning it is safe because using a larger cookie would waste a potentially useful resource.
* If it cannot satisfy the child, it cannot satisfy any more demanding child either, so we discard it.

### Complexity

* Sorting: `O(n log n + m log m)`
* Two-pointer traversal: `O(n + m)`
* **Overall:** `O(n log n + m log m)`
* **Space:** `O(1)` extra space (excluding sorting implementation)

### Pattern

**Greedy + Sorting + Two Pointers**

> Sort → compare the smallest remaining options → take the feasible choice → discard infeasible choices.
