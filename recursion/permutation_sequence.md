# Permutation Sequence (k-th Permutation)

Given `n` and `k`, return the `k`-th permutation (in lexicographic order) of the sequence `[1, 2, ..., n]` as a string, without generating all permutations.

## Key Idea

Permutations in lexicographic order are grouped into **blocks** by their first digit. For `n` numbers:

- There are `n!` permutations in total.
- Each choice of first digit owns a block of `(n-1)!` permutations.
- Inside a block, the same idea repeats for the remaining digits.

So instead of enumerating, we ask at each step: *which block does the k-th permutation fall into?*

Example for `n = 4` (block size = 3! = 6):

| First digit | Permutation indices (0-based) |
|-------------|-------------------------------|
| 1           | 0 – 5                         |
| 2           | 6 – 11                        |
| 3           | 12 – 17                       |
| 4           | 18 – 23                       |

## Approach

1. Convert `k` to 0-based: `left_over = k - 1`.
2. Keep a list `numbers = [1, 2, ..., n]` of digits still available.
3. Repeat until all `n` digits are picked:
   1. **Compute the block size:** `block_size = (numbers.size() - 1)!`
   2. **Pick the digit:** `pick = left_over / block_size`
      Integer division tells us how many full blocks come before ours, which is exactly the index of the digit to choose from `numbers`.
   3. Append `numbers[pick]` to the answer and **remove** it from `numbers`.
   4. **Update the remainder:** `left_over = left_over % block_size`
      This is our position *inside* the chosen block, which becomes the new `k` for the smaller problem of the remaining digits.

## Highlight: How the Number Is Picked Each Iteration

```cpp
int block_size = factorial(numbers.size() - 1);
int pick       = left_over / block_size;   // which block -> which digit
picked        += to_string(numbers[pick]);
numbers.erase(numbers.begin() + pick);
left_over      = left_over % block_size;   // offset within that block
```

- `left_over / block_size` → **selects the digit** (how many whole blocks we skip).
- `left_over % block_size` → **what remains** to be resolved among the remaining digits.

## Walkthrough: `n = 4, k = 9`

Start: `left_over = 8`, `numbers = [1, 2, 3, 4]`

| Step | numbers      | block_size | pick = left_over / block_size | digit | left_over = left_over % block_size |
|------|--------------|-----------|-------------------------------|-------|-------------------------------------|
| 1    | [1,2,3,4]    | 3! = 6    | 8 / 6 = 1                     | 2     | 8 % 6 = 2                           |
| 2    | [1,3,4]      | 2! = 2    | 2 / 2 = 1                     | 3     | 2 % 2 = 0                           |
| 3    | [1,4]        | 1! = 1    | 0 / 1 = 0                     | 1     | 0 % 1 = 0                           |
| 4    | [4]          | 0! = 1    | 0 / 1 = 0                     | 4     | 0                                   |

Result: **"2314"**

## Complexity

- **Time:** `O(n²)` — each of the `n` iterations does a vector `erase` (`O(n)`) and a factorial computation (`O(n)` recursive).
- **Space:** `O(n)` — for the `numbers` list and the result string.
```