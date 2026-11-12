# Longest Happy Prefix

This repository contains an optimal C++ solution for finding the longest prefix of a string that is also a suffix (excluding the string itself).

## 💡 The Approach: KMP Algorithm (LPS Array)

The most efficient way to solve this problem is by using the **LPS (Longest Prefix Suffix)** array, which is the core preprocessing step of the famous Knuth-Morris-Pratt (KMP) string matching algorithm. 

The LPS array stores exactly what we are looking for: `lps[i]` holds the length of the longest proper prefix that is also a suffix for the substring ending at index `i`. 

Since we want this property for the *entire* string, we just need to build the LPS array for the given string and look at the very last value: `lps[n-1]`. This value tells us exactly how many characters from the start of the string make up our "happy prefix".

## 📝 Algorithm Steps (Pseudocode)

1. **Initialize** the length of the string `n`. If the string is empty, return `""`.
2. **Create the LPS array** of size `n`, initialized to all `0`s. 
3. **Set up two pointers:**
   * `j = 0`: Tracks the length of the current longest prefix suffix.
   * `i = 1`: Iterates through the string to check new characters.
4. **Loop through the string** (`while i < n`):
   * **Match Case:** If `s[i] == s[j]`, the prefix extends! 
     * Increment both `j` and `i`.
     * Set `lps[i]` to `j`.
   * **Mismatch with Fallback:** If `s[i] != s[j]` and `j > 0`, we can't extend the current prefix, but a shorter one might work. 
     * Fall back by setting `j = lps[j-1]`. Do *not* increment `i` yet (we need to check the current `i` against the new `j`).
   * **Total Mismatch:** If `s[i] != s[j]` and `j == 0`, no prefix matches this suffix.
     * Set `lps[i] = 0`.
     * Increment `i` to move on.
5. **Extract the Answer:** The value at `lps[n-1]` is the length of our target prefix. Return the substring from index `0` of that length.

---

## 🔍 Visual Dry Run

Let's trace the string **`s = "ababab"`**. 
We initialize an array `lps = [0, 0, 0, 0, 0, 0]`.
`i = 1`, `j = 0`.

**Step 1:**
```text
  0 1 2 3 4 5
s:a b a b a b
  j i
```
* `s[1]('b') != s[0]('a')` and `j == 0`.
* Total mismatch. `lps[1] = 0`.
* Move `i` to 2.

**Step 2:**
```text
  0 1 2 3 4 5
s:a b a b a b
  j   i
```
* `s[2]('a') == s[0]('a')`.
* Match! The prefix `"a"` matches the suffix `"a"`.
* Set `lps[2] = j + 1 = 1`. 
* Move `i` to 3, `j` to 1.

**Step 3:**
```text
  0 1 2 3 4 5
s:a b a b a b
    j   i
```
* `s[3]('b') == s[1]('b')`.
* Match! The prefix `"ab"` matches the suffix `"ab"`.
* Set `lps[3] = j + 1 = 2`.
* Move `i` to 4, `j` to 2.

**Step 4:**
```text
  0 1 2 3 4 5
s:a b a b a b
      j   i
```
* `s[4]('a') == s[2]('a')`.
* Match! The prefix `"aba"` matches the suffix `"aba"`.
* Set `lps[4] = j + 1 = 3`.
* Move `i` to 5, `j` to 3.

**Step 5:**
```text
  0 1 2 3 4 5
s:a b a b a b
        j   i
```
* `s[5]('b') == s[3]('b')`.
* Match! The prefix `"abab"` matches the suffix `"abab"`.
* Set `lps[5] = j + 1 = 4`.
* Move `i` to 6, `j` to 4.

**End of Loop.**
Final LPS Array: `[0, 0, 1, 2, 3, 4]`

**Result:**
The last value `lps[5]` is **4**. 
We take the substring from index 0 of length 4: `s.substr(0, 4)`.
**Returns: `"abab"`**

## ⏱️ Complexity
* **Time Complexity:** $O(N)$ where $N$ is the length of the string. Both `i` and `j` move forward through the string, and the `while` loop runs at most $2N$ times.
* **Space Complexity:** $O(N)$ for the `lps` array used to store the prefix-suffix lengths.