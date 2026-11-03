# Custom Doubly Linked List (`MyLinkedList`)

An efficient C++ implementation of a 0-indexed **Doubly Linked List** maintaining explicit `head` and `tail` pointers alongside a `tail_index` tracker for $O(1)$ boundary access and strict $O(N)$ operations.

---

## 🏗️ Architecture & Node Structure

Each node contains a data payload (`val`) and two bidirectional pointers (`prev`, `next`).

```
         +--------------+         +--------------+         +--------------+
nullptr <| prev  val  next |<=======>| prev  val  next |<=======>| prev  val  next |> nullptr
         |   [ Node 0 ] |         |   [ Node 1 ] |         |   [ Node 2 ] |
         +--------------+         +--------------+         +--------------+
                ^                                                 ^
                |                                                 |
             head                                               tail
```

| Property | Type | Description |
| :--- | :--- | :--- |
| `head` | `Node*` | Points to index `0` (or `nullptr` if empty) |
| `tail` | `Node*` | Points to index `tail_index` (or `nullptr` if empty) |
| `tail_index` | `int` | Tracks the index of the last node (`-1` when empty) |

---

## ⚡ Key Operations & Complexity

| Method | Time Complexity | Space Complexity | Details |
| :--- | :--- | :--- | :--- |
| `get(index)` | $O(N)$ | $O(1)$ | Direct $O(1)$ lookup for index `0` and `tail_index`. |
| `addAtHead(val)` | $O(1)$ | $O(1)$ | Inserts at front; updates `head` and handles empty state. |
| `addAtTail(val)` | $O(1)$ | $O(1)$ | Appends at end; updates `tail` and handles empty state. |
| `addAtIndex(index, val)` | $O(N)$ | $O(1)$ | Inserts before `index`. Delegates to head/tail or re-wires pointers. |
| `deleteAtIndex(index)` | $O(N)$ | $O(1)$ | Removes node at `index`; handles deletion at boundaries. |

---

## 🚨 Critical Edge Cases & Visual Fixes

### 1. Middle Insertion Pointer Wiring (`addAtIndex`)
When inserting node `curr` (`N`) before `temp` (`B`), we must update references without losing access to `temp->prev` (`A`).

```
Before Insertion:
  +-------+                  +-------+
  |   A   | <--------------> |   B   | (temp)
  +-------+                  +-------+

Step-by-step Link Updates:
  1. curr->next = temp            (N points forward to B)
  2. temp->prev->next = curr      (A points forward to N)
  3. curr->prev = temp->prev      (N points backward to A)
  4. temp->prev = curr            (B points backward to N)

After Insertion:
  +-------+      +-------+      +-------+
  |   A   | <--> | N(curr)| <-->|   B   | (temp)
  +-------+      +-------+      +-------+
```

### 2. Valid Insertion Boundary Check
* **Issue:** Checking `if (index > tail_index)` prevents appending a node at the exact end of the list (`index == tail_index + 1`).
* **Fix:** Use `if (index > tail_index + 1)` as the upper bound guard before allocating memory or modifying state.

```text
 List: [ Node 0 ] <-> [ Node 1 ]   (tail_index = 1, Length = 2)

 - addAtIndex(2, val) -> VALID (Appends at tail)
 - addAtIndex(3, val) -> INVALID (index > tail_index + 1, returns early)
```

### 3. State Preservation Before Bounds Return
* **Issue:** Running `tail_index++` or `tail_index--` prior to verifying input validity permanently corrupts list size tracking if the operation exits early.
* **Fix:** Perform all boundary checks **before** modifying `tail_index`.

```cpp
// ❌ WRONG: Size corrupted on early return
tail_index++;
if (index > tail_index) return;

// ✅ CORRECT: Validate boundaries first
if (index > tail_index + 1) return;
tail_index++;
```

### 4. Boundary Deletion & Memory Management
When deleting index `0` on a single-node list or inserting at index `0` on an empty list, explicitly verify `head` pointers before accessing member variables and delete deallocated memory.

```text
Deleting Index 0 (Single Element List):
  [ Head / Tail ] ---> [ Node 0 ] ---> nullptr
  
  1. Detach head and tail: head = nullptr, tail = nullptr
  2. Decrement size: tail_index = -1
  3. Free memory: delete targetNode
```

---