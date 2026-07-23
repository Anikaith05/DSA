# 🌟 4Sum — Two Pointers + Sorting

> **Idea:** Fix the first **2 elements** and solve the remaining **2Sum** using the **Two Pointer** technique.

---

# 🧠 Intuition

Instead of checking all quadruplets (**O(N⁴)**),

- Fix `i`
- Fix `j`
- Search the remaining two numbers using two pointers.

```
i      j      l             m
↓      ↓      ↓             ↓
1  2  3  4  5  6  7  8  9
              →         ←
```

This reduces the complexity to **O(N³)**.

---

# 🚀 Algorithm

### 1️⃣ Sort the array

```cpp
sort(nums.begin(), nums.end());
```

Sorting allows us to

- Use two pointers
- Skip duplicates efficiently

---

### 2️⃣ Fix the first element

```cpp
for(int i=0;i<n-3;i++)
```

Skip duplicates

```cpp
if(i>0 && nums[i]==nums[i-1])
    continue;
```

---

### 3️⃣ Fix the second element

```cpp
for(int j=i+1;j<n-2;j++)
```

Skip duplicates **relative to `i`**

```cpp
if(j>i+1 && nums[j]==nums[j-1])
    continue;
```

> ❌ Wrong

```cpp
if(j>0 && nums[j]==nums[j-1])
```

This skips valid combinations when `i` changes.

---

### 4️⃣ Two Pointer Search

```
i      j      l          m
↓      ↓      ↓          ↓
-2  -1   0   1   2   3
          →         ←
```

Compute

```cpp
sum = nums[i]+nums[j]+nums[l]+nums[m]
```

---

If

```
sum == target
```

Store answer

```
l++
m--
```

---

If

```
sum < target
```

Need a larger sum

```
l++
```

---

If

```
sum > target
```

Need a smaller sum

```
m--
```

---

# 🔁 Skipping Duplicates

After finding a valid quadruplet

```cpp
l++;
m--;
```

Skip repeated values

```cpp
while(l<m && nums[l]==nums[l-1])
    l++;

while(l<m && nums[m]==nums[m+1])
    m--;
```

Notice

```
m + 1
```

NOT

```
m - 1
```

because `m` has already moved left.

---

# ⚠️ Overflow (Most Important)

LeetCode fails if you use

```cpp
nums[i]+nums[j]+nums[l]+nums[m]
```

Example

```
1000000000
+
1000000000
+
1000000000
+
1000000000
=
4000000000
```

An `int` cannot store this.

---

Always use

```cpp
long long sum =
1LL*nums[i]+nums[j]+nums[l]+nums[m];
```

The `1LL*` converts the whole expression into `long long`.

---

# 💡 Pointer Movement

```
sum < target

l →
```

```
sum > target

← m
```

```
sum == target

l →
← m
```

---

# 📊 Complexity

| Operation | Complexity |
|-----------|------------|
| Sorting | O(N log N) |
| Outer loop | O(N) |
| Inner loop | O(N) |
| Two Pointer | O(N) |

Overall

```
O(N³)
```

Space

```
O(1)
```

(excluding output)

---

# ✅ Things to Remember

✅ Sort first.

✅ Fix two elements.

✅ Remaining problem becomes 2Sum.

✅ Skip duplicate `i`.

✅ Skip duplicate `j` using

```cpp
j > i + 1
```

NOT

```cpp
j > 0
```

✅ Skip duplicate `l` and `m`.

✅ Compare `nums[m]` with `nums[m+1]`.

✅ Use `long long` for the sum to avoid overflow.

---

# 🧠 Pattern to Remember

```
2Sum
↓
Sort + Two Pointers

3Sum
↓
Fix 1 element
+
Two Pointers

4Sum
↓
Fix 2 elements
+
Two Pointers

KSum
↓
Fix (K-2) elements
+
Two Pointers
```

---

# 🎯 Interview Takeaway

Whenever you see

- 2Sum
- 3Sum
- 4Sum
- KSum

Think

```
Sort
        ↓
Fix elements
        ↓
Two Pointers
        ↓
Skip duplicates
        ↓
Watch for overflow
```