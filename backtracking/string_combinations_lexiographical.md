# Generate All Permutations of All Lengths Using Backtracking

## 📌 Problem

Given a string `str`, generate all possible **non-empty permutations of all possible lengths** using **backtracking**.

For example:

```text
Input: str = "ABC"
```

Output:

```text
A
AB
ABC
AC
ACB
B
BA
BAC
BC
BCA
C
CA
CAB
CB
CBA
```

For:

```text
Input: str = "ED"
```

Output:

```text
D
DE
E
ED
```

---

# 🧠 Key Idea

At every step, we can choose **any character that has not already been used**.

After choosing a character:

1. Add it to the current sequence.
2. Print the current sequence.
3. Recursively try adding another unused character.
4. Remove the character before trying another choice.

This follows the classic backtracking pattern:

```text
Choose
   ↓
Print current answer
   ↓
Explore recursively
   ↓
Unchoose (Backtrack)
```

---

# 🌳 Example Recursion Tree

For:

```text
ABC
```

The recursion tree is:

```text
                     ""
              /       |       \
             A        B        C
           /   \    /   \    /   \
          AB   AC  BA   BC  CA   CB
          |    |   |    |   |    |
         ABC  ACB BAC  BCA CAB  CBA
```

We print every non-empty node in this tree:

```text
A
AB
ABC
AC
ACB
B
BA
BAC
BC
BCA
C
CA
CAB
CB
CBA
```

---

# 🔑 Role of `visited`

```cpp
visited[i]
```

tells us whether `str[i]` is already being used in the current permutation.

```text
visited[i] = 0 → Available to choose

visited[i] = 1 → Already used
```

For example:

```text
Current = AB
```

Characters `A` and `B` are marked as visited, so only `C` can be chosen next.

# ⏱️ Time Complexity

For a string of length `N`, we generate permutations of lengths:

```text
1, 2, 3, ..., N
```

The total number of generated sequences is:

```text
P(N,1) + P(N,2) + ... + P(N,N)
```

where:

```text
P(N,k) = N! / (N-k)!
```

The overall complexity is approximately:

```text
O(N × N!)
```

---

# 💾 Space Complexity

We use:

* `visited` → `O(N)`
* `curr` → `O(N)`
* Recursion stack → `O(N)`

Therefore:

```text
Auxiliary Space = O(N)
```

excluding the output.

---

# 🎯 Pattern to Remember

## Generate all possible partial permutations

```text
for every unused choice:

    choose

    process current answer

    recurse

    unchoose
```

This is a fundamental **backtracking pattern** used when:

* Order matters
* Elements cannot be reused
* We need to explore all possible choices
* We need answers of different lengths
