# Longest Palindromic Substring

This repository contains a C++ solution to the "Longest Palindromic Substring" problem. 

## Approach: Expand Around Center

A palindrome mirrors around its center. Therefore, if we pick a center, we can find the longest palindrome by expanding outwards (left and right) as long as the characters match.

There is one major caveat to this approach: the center of a palindrome can be a single character, or it can fall *between* two characters. 
* **Odd length palindromes:** e.g., `"aba"`. The center is a single character (`'b'`). Left and right pointers start at the same index.
* **Even length palindromes:** e.g., `"abba"`. The center is between two characters (`'b'` and `'b'`). Left and right pointers start at adjacent indices.

**Algorithm Steps:**
1. Iterate through every character in the string.
2. Treat the current character as the center of an **odd-length** palindrome and expand outwards. Update the maximum palindrome found so far.
3. Treat the current character and the next character as the center of an **even-length** palindrome and expand outwards. Update the maximum palindrome found so far.
4. Return the longest palindrome found.

---

## English Pseudocode

```text
Initialize max_len to the smallest possible integer.
Initialize max_str to an empty string.

FOR i from 0 to the end of the string:

    // 1. Check for ODD length palindromes
    Set left_pointer (j) to i
    Set right_pointer (k) to i
    
    WHILE left_pointer >= 0 AND right_pointer < string_length:
        IF character at left_pointer matches character at right_pointer:
            Calculate current_length as (right_pointer - left_pointer + 1)
            IF current_length is greater than max_len:
                Update max_len to current_length
                Update max_str to the substring from left_pointer to right_pointer
            
            Move left_pointer one step left (j--)
            Move right_pointer one step right (k++)
        ELSE:
            Stop expanding (break out of loop)

    // 2. Check for EVEN length palindromes
    IF there is a character after i (i + 1 < string_length):
        Set left_pointer (j) to i
        Set right_pointer (k) to i + 1
        
        WHILE left_pointer >= 0 AND right_pointer < string_length:
            IF character at left_pointer matches character at right_pointer:
                Calculate current_length as (right_pointer - left_pointer + 1)
                IF current_length is greater than max_len:
                    Update max_len to current_length
                    Update max_str to the substring from left_pointer to right_pointer
                
                Move left_pointer one step left (j--)
                Move right_pointer one step right (k++)
            ELSE:
                Stop expanding (break out of loop)

Return max_str
```

---

## Dry Run 

Let's trace the algorithm with the string **`s = "cbbd"`**. 
*This example covers the primary caveat: a purely odd-center algorithm would return `"c"`, failing to find the even-length palindrome `"bb"`.*

**Initialization:**
* `s = "cbbd"` (length `n = 4`)
* `max_len = -infinity`
* `max_str = ""`

### **Iteration 1: `i = 0` (character `'c'`)**

* **Odd Center Check:** `j = 0, k = 0`
  * `s[0] == s[0]` (`'c' == 'c'`).
  * Length is `1`. `1 > max_len`, so **`max_len = 1`**, **`max_str = "c"`**.
  * Expand: `j = -1, k = 1`. 
  * Loop breaks because `j < 0` (out of bounds).
* **Even Center Check:** `j = 0, k = 1`
  * `s[0] != s[1]` (`'c' != 'b'`).
  * Loop breaks immediately.

### **Iteration 2: `i = 1` (character `'b'`)**

* **Odd Center Check:** `j = 1, k = 1`
  * `s[1] == s[1]` (`'b' == 'b'`).
  * Length is `1`. Not greater than `max_len`, so no update.
  * Expand: `j = 0, k = 2`.
  * `s[0] != s[2]` (`'c' != 'b'`). Loop breaks.
* **Even Center Check:** `j = 1, k = 2`
  * `s[1] == s[2]` (`'b' == 'b'`).
  * Length is `2`. `2 > max_len`, so **`max_len = 2`**, **`max_str = "bb"`**.
  * Expand: `j = 0, k = 3`.
  * `s[0] != s[3]` (`'c' != 'd'`). Loop breaks.

### **Iteration 3: `i = 2` (character `'b'`)**

* **Odd Center Check:** `j = 2, k = 2`
  * `s[2] == s[2]` (`'b' == 'b'`).
  * Length is `1`. Not greater than `max_len`.
  * Expand: `j = 1, k = 3`.
  * `s[1] != s[3]` (`'b' != 'd'`). Loop breaks.
* **Even Center Check:** `j = 2, k = 3`
  * `s[2] != s[3]` (`'b' != 'd'`). Loop breaks.

### **Iteration 4: `i = 3` (character `'d'`)**

* **Odd Center Check:** `j = 3, k = 3`
  * `s[3] == s[3]` (`'d' == 'd'`).
  * Length is `1`. Not greater than `max_len`.
  * Expand: `j = 2, k = 4`.
  * Loop breaks because `k == 4` (out of bounds).
* **Even Center Check:** 
  * Skipped entirely because `i + 1` (which is `4`) is not less than `n`.

**Final Output:**
The loop finishes and returns `max_str`, which is **`"bb"`**.

### Other Edge Cases Covered:
* **Single character strings (`s = "a"`):** The loop runs for `i = 0`. The odd center check sets `max_str = "a"`. The even check is skipped (`i+1 < n` is false). Returns `"a"`.
* **String with no repeating palindromes (`s = "abc"`):** The odd check on the first character sets `max_len = 1` and `max_str = "a"`. Subsequent letters have a length of 1, which is not strictly *greater* than `max_len`, so `"a"` is correctly returned as a valid length-1 palindrome.