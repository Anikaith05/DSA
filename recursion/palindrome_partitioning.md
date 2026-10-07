# 131. Palindrome Partitioning

Given a string `s`, split it so that every piece is a palindrome, and return all possible splits.

```
Input:  s = "aab"
Output: [["a","a","b"],["aa","b"]]
```

## Approach: backtracking ("cut or don't cut")

At every position we decide where the next piece of the string ends. We try every possible ending, keep only the pieces that are palindromes, and recurse on whatever is left of the string. When nothing is left, the pieces collected so far form one valid partition.

The solution has three parts:

| Part | Role |
|------|------|
| `isPalindrome(string s)` | Checks a piece with two pointers (`i` from the left, `j` from the right) moving inward. |
| `calc(answer, start, str, buffer)` | The recursive backtracking function. |
| `partition(string s)` | Creates `answer` and `buffer`, then calls `calc` from `start = 0`. |

## The two indices: `start` and `end`

- `start` is where the current piece begins. It is the recursion parameter, so each call "owns" the part of the string from `start` onward.
- `end` is the loop variable. It decides where the piece stops, so the piece is `str[start..end]`.

```cpp
for (int end = start; end < str.size(); end++) {
    string sub = str.substr(start, end - start + 1);
    ...
}
```

`substr(pos, len)` takes a length, not an end index, so the length is `end - start + 1`.

For `"aab"` with `start = 0`:

| `end` | `sub` | Palindrome? |
|-------|-------|-------------|
| 0 | `"a"` | yes, recurse |
| 1 | `"aa"` | yes, recurse |
| 2 | `"aab"` | no, skip |

When a piece is accepted, the rest of the string is handled by `calc(..., end + 1, ...)`. The next piece begins right after the cut, which is why a piece ending at `end` leads to a child call with `start = end + 1`.

## How the recursion tree is created

Every call to `calc` is a node. Every iteration of its `for` loop that passes the palindrome check is an edge to a child node. The loop is what makes the tree branch: one call tries several values of `end`, and each valid one spawns a child.

```
                         start=0, buffer=[]
              /                |                 \
        "a" (end=0)       "aa" (end=1)        "aab" (end=2)
       start=1, [a]       start=2, [aa]        not a palindrome,
        /        \              |              no child
  "a" (end=1)  "ab" (end=2)  "b" (end=2)
  start=2,     not a         start=3, [aa,b]
  [a,a]        palindrome,   start == size
     |         no child      -> SAVE [aa,b]
  "b" (end=2)
  start=3, [a,a,b]
  start == size
  -> SAVE [a,a,b]
```

- Branches stop in two ways:
  - **Dead end:** the piece is not a palindrome, so the loop skips it and no child is created.
  - **Success:** `start == str.size()`, so nothing is left to cut and the buffer is saved.
- Leaves that reach the end of the string are the answers. Here that gives `[a,a,b]` and `[aa,b]`.

## How push and pop work

`buffer` holds the pieces chosen on the path from the root to the current node.

```cpp
buffer.push_back(sub);              // 1. choose: cut here and keep this piece
calc(answer, end + 1, str, buffer); // 2. explore: partition the rest of the string
buffer.pop_back();                  // 3. un-choose: remove it so the next `end` starts clean
```

- `push_back` adds the piece to the partition being built.
- The recursive call explores everything that can follow that choice.
- `pop_back` undoes the choice. Without it, the piece would still be in `buffer` when the loop moves to the next `end`, and later partitions would contain pieces from earlier branches.

When the base case `start == str.size()` is hit, `answer.push_back(buffer)` stores a copy of the buffer, so later pushes and pops do not change the saved result.

### Trace for `"aab"`

```
calc(start=0, [])
  end=0 "a"   ok   push  -> [a]
    calc(start=1, [a])
      end=1 "a"  ok   push -> [a,a]
        calc(start=2, [a,a])
          end=2 "b" ok  push -> [a,a,b]
            calc(start=3)  start == size -> SAVE [a,a,b]
          pop -> [a,a]
        return
      pop -> [a]
      end=2 "ab" no   skip
    return
  pop -> []
  end=1 "aa"  ok   push  -> [aa]
    calc(start=2, [aa])
      end=2 "b" ok  push -> [aa,b]
        calc(start=3)  start == size -> SAVE [aa,b]
      pop -> [aa]
    return
  pop -> []
  end=2 "aab" no   skip
```

## Complexity

- **Time:** O(n * 2^n). A string of length `n` has up to `2^(n-1)` ways to place cuts, and each partition costs O(n) to check and copy.
- **Space:** O(n) for the recursion depth and `buffer`, not counting the output.

## Possible improvements

- Pass `str` and `buffer` by reference to avoid copying them on every call. The `push_back` / `pop_back` pair is still needed, because the loop in one call reuses the same `buffer` across iterations.
- Check palindromes with indices (`isPalindrome(s, start, end)`) instead of building a substring first, and only build the string when pushing it.
- Precompute a table `dp[i][j]` for "is `s[i..j]` a palindrome?" so each check becomes O(1).