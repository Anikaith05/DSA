# Sort a Stack Using Recursion

## Problem Statement
Given a stack of integers, sort it in descending order using recursion, such that the largest element is at the top and the smallest element is at the bottom.

**Example:**
- Input (top to bottom): `4, 1, 3, 2`
- Output (top to bottom): `4, 3, 2, 1`

## Approach
The solution uses recursion and a temporary stack (`st2`) to sort the elements.

1. **Base Case:** If the stack is empty, return.
2. **Remove the Top Element:** Store the top element in `x` and pop it.
3. **Recursive Call:** Call `sortStack(st)` to sort the remaining stack.
4. **Insert in the Correct Position:** Move elements greater than or equal to `x` into a temporary stack (`st2`).
5. Push `x` onto the original stack.
6. Restore the elements from `st2` to the original stack.

This ensures that the largest element ends up at the top.

## Real-Life Analogy: Stacking Plates
Imagine arranging plates in a kitchen. Each plate has a number representing its weight. The goal is to keep the heaviest plate at the top and the lightest at the bottom.

However, you can only remove or place plates at the top of the stack.

1. Remove the top plate and remember its weight.
2. Repeat until the stack is empty.
3. As recursive calls return, put each removed plate back in its correct position.
4. If other plates block its position, temporarily move them to another stack (`st2`).
5. Place the plate, then restore the temporarily moved plates.

Here, recursion removes and processes the plates one by one, while `st2` temporarily holds plates that need to be moved out of the way.

## Complexity Analysis

- **Time Complexity:** `O(N²)` in the worst case, because inserting each element may require moving multiple elements.
- **Auxiliary Space Complexity:** `O(N)` for the recursion call stack and temporary stack.

## Key Takeaway
Recursively sort the smaller stack first, then insert each removed element into its correct position. Temporarily move blocking elements aside and restore them afterward.