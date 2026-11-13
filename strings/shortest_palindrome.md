# Shortest Palindrome

This repository contains an optimized C++ solution for finding the shortest palindrome by adding characters to the front of a given string.

## Approach: KMP Algorithm (Longest Prefix Suffix)

The problem asks us to find the shortest palindrome by prepending characters to a string `s`. 
To do this minimally, we need to find the **longest palindromic prefix** of `s`. Once we find it, the remaining suffix of `s` (which is not part of this palindromic prefix) just needs to be reversed and added to the front.

Instead of checking all prefixes manually (which takes $O(N^2)$ time), we can cleverly use the **LPS (Longest Prefix Suffix)** array from the KMP string-matching algorithm to do this in $O(N)$ time.

**The Clever Trick:**
1. Create a new string: `combined = s + '#' + reverse(s)`.
2. The `#` acts as a strict boundary separator. It ensures that our prefix and suffix don't overlap in a way that exceeds the length of the original string.
3. If we calculate the LPS array for this `combined` string, the last value in the array will tell us the exact length of the longest prefix of `s` that is also a suffix of `reverse(s)`. 
4. A prefix of `s` that matches a suffix of `reverse(s)` is, by definition, a palindrome!

## English Pseudocode

1. **Base Case:** Check if `s` is already a palindrome. If it is, return `s` immediately.
2. **Reverse the String:** Create a reversed copy of `s` and store it in `rev_s`.
3. **Concatenate:** Create a new string `lps_str` formatted as `s + '#' + rev_s`.
4. **Compute LPS:**
   * Initialize an array `lps` of the same size as `lps_str`, filled with `0`.
   * Use two pointers, `i` (starts at 1) and `j` (starts at 0).
   * Iterate through `lps_str`:
     * If characters at `i` and `j` match, increment both and set `lps[i]` to `j`.
     * If they don't match, fallback `j` to `lps[j-1]` until there's a match or `j` becomes 0.
5. **Find Max Palindromic Prefix:** The last element of the `lps` array (`lps[n-1]`) holds the length of the longest palindromic prefix of `s`.
6. **Construct Result:** 
   * Extract the remaining characters of `s` (the suffix that isn't part of the palindromic prefix).
   * Reverse this suffix.
   * Prepend it to the original string `s` and return the result.

---

## Dry Run

Let's do a dry run with an example that highlights **why the `#` separator is absolutely necessary** (a major edge case).

**Example String:** `s = "aaba"`

**Step 1: Check Palindrome**
Is "aaba" a palindrome? No.

**Step 2 & 3: Setup Strings**
* `s` = `"aaba"`
* `rev_s` = `"abaa"`
* `lps_str` = `"aaba#abaa"`

*(Caveat note: If we didn't use `#`, `lps_str` would be `"aabaabaa"`. The LPS of the last character would be 5 ("aabaa"), which is longer than the original string! The `#` forces the LPS to stop at the boundary.)*

**Step 4: Compute LPS Array for `"aaba#abaa"`**

Let's build the `lps` array of size 9.
* `lps[0] = 0` (Always 0 for the first char)
* `i = 1, j = 0`: `s[1]`('a') == `s[0]`('a') $\rightarrow$ match. `lps[1] = 1`, `j = 1`.
* `i = 2, j = 1`: `s[2]`('b') != `s[1]`('a') $\rightarrow$ mismatch. Fallback `j` to `lps[0]` = 0. `s[2]`('b') != `s[0]`('a'). `lps[2] = 0`.
* `i = 3, j = 0`: `s[3]`('a') == `s[0]`('a') $\rightarrow$ match. `lps[3] = 1`, `j = 1`.
* `i = 4, j = 1`: `s[4]`('#') != `s[1]`('a') $\rightarrow$ mismatch. Fallback `j` to 0. `lps[4] = 0`. *(The separator works!)*
* `i = 5, j = 0`: `s[5]`('a') == `s[0]`('a') $\rightarrow$ match. `lps[5] = 1`, `j = 1`.
* `i = 6, j = 1`: `s[6]`('b') != `s[1]`('a') $\rightarrow$ mismatch. Fallback `j` to 0. `lps[6] = 0`.
* `i = 7, j = 0`: `s[7]`('a') == `s[0]`('a') $\rightarrow$ match. `lps[7] = 1`, `j = 1`.
* `i = 8, j = 1`: `s[8]`('a') == `s[1]`('a') $\rightarrow$ match. `lps[8] = 2`, `j = 2`.

Final `lps` array: `[0, 1, 0, 1, 0, 1, 0, 1, 2]`

**Step 5: Find Max Palindromic Prefix**
* The last value in the array is `lps[8] = 2`.
* This means the longest palindromic prefix of `"aaba"` is length `2` (which is `"aa"`).

**Step 6: Construct the Final Answer**
* `max_len = 2`.
* Non-palindromic suffix of `s`: `s.substr(2)` $\rightarrow$ `"ba"`.
* Reverse the suffix $\rightarrow$ `"ab"`.
* Prepend to original `s`: `"ab"` + `"aaba"` $\rightarrow$ **`"abaaba"`**.

The algorithm correctly identifies the shortest palindrome in $O(N)$ time!