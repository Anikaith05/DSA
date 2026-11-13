# Shortest Palindrome

This repository contains an optimized C++ solution for finding the shortest palindrome by adding characters to the front of a given string.

## Approach: KMP Algorithm (Longest Prefix Suffix)

The problem asks us to find the shortest palindrome by prepending characters to a string `s`. 
To do this minimally, we need to find the **longest palindromic prefix** of `s`. Once we find it, the remaining suffix of `s` (which is not part of this palindromic prefix) just needs to be reversed and added to the front.

Instead of checking all prefixes manually (which takes $O(N^2)$ time), we can cleverly use the **LPS (Longest Prefix Suffix)** array from the KMP string-matching algorithm to do this in $O(N)$ time.

**The Clever Trick:**
1. Create a new string: `combined = s + '#' + reverse(s)`.
2. If we calculate the LPS array for this `combined` string, the last value in the array will tell us the exact length of the longest prefix of `s` that is also a suffix of `reverse(s)`. 
3. A prefix of `s` that matches a suffix of `reverse(s)` is, by definition, a palindrome!

### Why do we need the `#` separator?
The `#` acts as a strict boundary separator. It ensures that the LPS calculation does not "bleed over" and match a prefix that is longer than the original string itself. 

**What happens without it?**
Imagine the string `s = "aaaa"`.
*   `rev_s` is also `"aaaa"`.
*   If we just combined them without `#`: `combined = "aaaaaaaa"`. 
*   The LPS of the last character would be `7` (meaning a prefix of length 7 matches a suffix of length 7). But our original string is only `4` characters long! 

**What happens with it?**
By adding a character that is guaranteed *not* to be in the input string (like `#`), we force the LPS matching to stop at the boundary.
*   `combined = "aaaa#aaaa"`.
*   The `#` breaks the continuous match, ensuring the LPS array maxes out at the exact length of the original string. The LPS of the last character will correctly be `4`.

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

Let's do a dry run with an example.

**Example String:** `s = "aaba"`

**Step 1: Check Palindrome**
Is "aaba" a palindrome? No.

**Step 2 & 3: Setup Strings**
* `s` = `"aaba"`
* `rev_s` = `"abaa"`
* `lps_str` = `"aaba#abaa"`

**Step 4: Compute LPS Array for `"aaba#abaa"`**

Let's build the `lps` array of size 9.
* `lps[0] = 0` (Always 0 for the first char)
* `i = 1, j = 0`: `s[1]`('a') == `s[0]`('a') $\rightarrow$ match. `lps[1] = 1`, `j = 1`.
* `i = 2, j = 1`: `s[2]`('b') != `s[1]`('a') $\rightarrow$ mismatch. Fallback `j` to `lps[0]` = 0. `s[2]`('b') != `s[0]`('a'). `lps[2] = 0`.
* `i = 3, j = 0`: `s[3]`('a') == `s[0]`('a') $\rightarrow$ match. `lps[3] = 1`, `j = 1`.
* `i = 4, j = 1`: `s[4]`('#') != `s[1]`('a') $\rightarrow$ mismatch. Fallback `j` to 0. `lps[4] = 0`. *(The separator works, resetting the count!)*
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