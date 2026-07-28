# Count Subarrays with Given XOR – Visual Intuition

## The Idea

Instead of calculating the XOR of every subarray, we use **Prefix XOR**.

Define

```cpp
prefixXor[i] = arr[0] ^ arr[1] ^ ... ^ arr[i];
```

Just like prefix sums, prefix XOR lets us compute the XOR of any subarray in O(1).

---

# Step 1: Derive the Formula

Suppose we want the XOR of the subarray from `l` to `r`.

```
arr[l] ^ arr[l+1] ^ ... ^ arr[r]
```

Using prefix XOR,

```
= prefixXor[r] ^ prefixXor[l-1]
```

because everything before `l` appears twice and cancels out.

If this XOR must equal `k`,

```
prefixXor[r] ^ prefixXor[l-1] = k
```

XOR both sides with `prefixXor[r]`.

```
prefixXor[l-1] = prefixXor[r] ^ k
```

This is the only equation we actually need.

---

# Step 2: What does the HashMap store?

While processing index `i`, we already know

```
currentPrefix = prefixXor[i]
```

We need to know

```
How many previous prefix XORs are equal to

currentPrefix ^ k ?
```

The map stores **all previous prefix XORs**.

```
Key   -> Prefix XOR
Value -> All occurrences of that Prefix XOR
```

---

# Step 3: Why do we insert AFTER searching?

Suppose

```
k = 0
```

and

```
currentPrefix = 6
```

If we insert first,

```
Map

6 -> current index
```

Then we search

```
currentPrefix ^ k

6 ^ 0

= 6
```

The map now contains the current prefix XOR.

We accidentally count

```
currentPrefix ^ currentPrefix = 0
```

which corresponds to an impossible subarray.

Therefore the order must always be

```
Search
↓

Count answer
↓

Insert current Prefix XOR
```

---

# Step 4: Why do we initialize

```cpp
mp[0].push_back(-1);
```

Imagine

```
arr = [4,2]
k = 6
```

Prefix XOR

```
Index          -1      0      1
--------------------------------
Prefix XOR      0      4      6
```

Notice the imaginary prefix XOR before the array begins.

At

```
i = 1

currentPrefix = 6
```

We compute

```
needed = 6 ^ 6

= 0
```

We need a previous prefix XOR of 0.

Where is it?

```
Index = -1
```

That represents the empty prefix before the array.

Without storing this,

```
[4,2]
```

would never be counted.

The `-1` itself is never used.

It simply represents

```
"There exists one prefix XOR equal to 0 before the array starts."
```

Most optimized solutions simply write

```cpp
unordered_map<int,int> mp;
mp[0] = 1;
```

because only the frequency matters.

---

# Complete Visualization

```
Array

        4      2      2      6      4

        ↓      ↓      ↓      ↓      ↓

Prefix XOR

        4      6      4      2      6


Imaginary Prefix

Index

      -1      0      1      2      3      4

Prefix XOR

       0      4      6      4      2      6
```

Suppose

```
k = 6
```

At

```
i = 4

currentPrefix = 6
```

Need

```
6 ^ 6

= 0
```

The map already contains

```
0

↓

Index -1
```

Therefore

```
Subarray

0 ... 4
```

is counted.

---

At

```
i = 2

currentPrefix = 4
```

Need

```
4 ^ 6

= 2
```

Have we seen prefix XOR = 2?

No.

Continue.

---

At

```
i = 3

currentPrefix = 2
```

Need

```
2 ^ 6

= 4
```

The map contains two previous occurrences of Prefix XOR = 4.

```
Index 0

Index 2
```

Therefore there are **two** different subarrays ending at index 3 whose XOR is 6.

---

# Algorithm

```
Compute Prefix XOR

↓

Initialize

Prefix XOR 0 has occurred once

↓

For every index

    needed = currentPrefix ^ k

    Answer += frequency(needed)

    frequency(currentPrefix)++
```

---

# Time Complexity

```
Building Prefix XOR      O(n)

HashMap lookup           O(1)

HashMap insertion        O(1)

Overall                  O(n)
```

---

# Space Complexity

```
Prefix XOR Array     O(n)

HashMap              O(n)

Overall              O(n)
```

---

# Important Takeaways

### Prefix XOR Formula

```
Subarray XOR

=

prefixXor[r] ^ prefixXor[l-1]
```

---

### Rearranged Equation

```
prefixXor[l-1]

=

prefixXor[r] ^ k
```

---

### Why initialize `mp[0]`?

To count every subarray that starts at index **0**.

---

### Why search before inserting?

To avoid counting the current prefix XOR as a previous prefix XOR.

---

### Difference from Longest Subarray Sum = K

**Longest Subarray Sum**

```
Map stores

First occurrence (index)

Even if current index matches,

i - i = 0

Harmless.
```

**Count Subarrays XOR**

```
Map stores

Frequency

If current prefix is inserted first,

it gets counted,

giving one extra subarray.

Wrong answer.
```

This difference is the reason the insertion order matters in the XOR counting problem but not in the longest subarray sum problem.
