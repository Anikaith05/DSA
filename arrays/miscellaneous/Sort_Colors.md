# LeetCode 75 - Sort Colors (Dutch National Flag Algorithm)

## Idea

Maintain **four regions** during traversal:

``` text
[0 ... low-1]      -> all 0s ✅
[low ... mid-1]    -> all 1s ✅
[mid ... high]     -> Unknown ❓
[high+1 ... n-1]   -> all 2s ✅
```

The goal is to shrink the **unknown region** until nothing remains.

## Visual Invariant (from notes)

![Dutch National Flag
Invariant](a4d852e6-56cc-4668-8ccd-a6cf306a06ad.png)

Equivalent representation:

``` text
0          low-1 low          mid-1 mid             high high+1        n-1
|------------| |---------------| |-------------------| |----------------|
    0s               1s                UNKNOWN              2s
```

## Pointers

-   `low` → next position for a `0`
-   `mid` → current element being processed
-   `high` → next position for a `2`

## Cases

### nums\[mid\] == 0

Swap `nums[mid]` and `nums[low]`.

Reason: - Left side before `low` already contains only `0`s. - After
swapping, the `0` is in its correct region. - The element moved to `mid`
is guaranteed to be `1` (or the same element when `low == mid`), so both
pointers can move.

    swap(mid, low)
    low++
    mid++

------------------------------------------------------------------------

### nums\[mid\] == 1

Already belongs in the middle.

    mid++

------------------------------------------------------------------------

### nums\[mid\] == 2

Swap with `high`.

Do **NOT** increment `mid`.

Reason: The element coming from `high` is **unknown**, so it must be
examined again.

    swap(mid, high)
    high--

## Why `mid <= high`?

The unknown region is `[mid ... high]`.

Once `mid > high`, the unknown region disappears, meaning the array is
sorted.

## Complexity

-   Time: **O(n)**
-   Space: **O(1)**

## Code

``` cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int start = 0, mid = 0, high = nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[mid], nums[start]);
                start++;
                mid++;
            }
            else if (nums[mid] == 1) {
                mid++;
            }
            else {
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }
};
```

## Revision Checklist

-   [ ] Memorize the four regions.
-   [ ] Remember that `mid` scans the unknown region.
-   [ ] Increment both `low` and `mid` after placing a `0`.
-   [ ] Increment only `mid` for a `1`.
-   [ ] Do **not** increment `mid` after swapping with `high`.
-   [ ] Loop until `mid > high`.
