# LRU Cache – Doubly Linked List + Hash Map

## 1. Problem Overview

Design a data structure that follows the **Least Recently Used (LRU)** eviction policy.

An LRU Cache supports two operations:

- `get(key)`: Returns the value associated with the key. Returns `-1` if the key doesn't exist.
- `put(key, value)`: Inserts a new key-value pair or updates an existing key.

When the cache reaches its maximum capacity, inserting a new element requires removing the **Least Recently Used (LRU)** element.

### What does LRU mean?

The element that hasn't been accessed for the longest time gets removed first.

For example, consider a cache with capacity = 3.

```text
Insert: 10, 20, 30

MRU                         LRU
 ↓                           ↓
[30] <-> [20] <-> [10]
```

Now execute:

```cpp
get(10);
```

Since 10 was accessed, it becomes the Most Recently Used (MRU) element.

```text
MRU                         LRU
 ↓                           ↓
[10] <-> [30] <-> [20]
```

Now insert 40:

```cpp
put(40, 400);
```

The cache is full, so 20 gets evicted.

```text
MRU                         LRU
 ↓                           ↓
[40] <-> [10] <-> [30]
```

**Key observation:** Every successful `get()` and every `put()` involving an existing key makes that element the MRU element.

---

## 2. Approach: Hash Map + Doubly Linked List

Using only a linked list would require O(N) time to search for a key.

Using only a hash map would make it difficult to efficiently identify and remove the least recently used element.

Therefore, we combine both data structures.

### A. Hash Map – O(1) Lookup

```cpp
unordered_map<int, Node*> mp;
```

The hash map stores:

```text
Key  →  Address of corresponding Node
```

Example:

```text
mp
--------------------------------
10  →  Address of Node(10, 100)
20  →  Address of Node(20, 200)
30  →  Address of Node(30, 300)
```

This allows us to directly access any node without traversing the linked list.

### B. Doubly Linked List – O(1) Reordering

We maintain a doubly linked list containing all cache elements.

```text
HEAD                                  TAIL
 ↓                                      ↓
[30] <-> [20] <-> [10] <-> [40]
 MRU                                LRU
```

- HEAD always points to the MRU element.
- TAIL always points to the LRU element.
- Every node contains `prev` and `next` pointers.

Why a doubly linked list?

Because we need to remove a node from anywhere in the list in O(1) time.

With a singly linked list, we would need to find its previous node first.

### Combined Architecture

```text
             HASH MAP
       ┌──────────────────┐
       │ 10 → Node(10)    │
       │ 20 → Node(20)    │
       │ 30 → Node(30)    │
       └──────────────────┘
          │       │
          │       │
          ▼       ▼

HEAD                                  TAIL
 ↓                                      ↓
[30] <-> [20] <-> [10]
 MRU                                LRU
```

The hash map provides direct access, while the linked list maintains the usage order.

**Together, they allow both operations to run in O(1) average time.**

---

## 3. Node Structure

```cpp
struct Node {
    int key;
    int val;
    Node* prev;
    Node* next;

    Node(int k, int v) {
        key = k;
        val = v;
        prev = nullptr;
        next = nullptr;
    }
};
```

Each node contains four components:

| Member | Purpose |
|---|---|
| `key` | Stores the key |
| `val` | Stores the corresponding value |
| `prev` | Points to the previous node |
| `next` | Points to the next node |

**Important implementation detail: Why store the key inside the node?**

When evicting the tail node, we need to remove its corresponding entry from the hash map.

```cpp
mp.erase(oldTail->key);
```

Without storing the key in the node, we would not be able to directly identify which hash map entry needs to be deleted.

---

## 4. Important Class Variables

```cpp
unordered_map<int, Node*> mp;

int cap;
int curr_cap;

Node* head;
Node* tail;
```

| Variable | Responsibility |
|---|---|
| `mp` | Maps keys to node addresses |
| `cap` | Maximum cache capacity |
| `curr_cap` | Current number of elements |
| `head` | Most Recently Used node |
| `tail` | Least Recently Used node |

### Core invariant

At all times:

```text
head->prev == nullptr
tail->next == nullptr
```

And for every pair of adjacent nodes:

```text
A->next == B
B->prev == A
```

The hash map must also contain exactly the nodes present in the linked list.

---

## 5. Implementation of GET()

```cpp
int get(int key) {
    if (mp.find(key) == mp.end())
        return -1;

    Node* curr = mp[key];

    if (curr == head) {
        return curr->val;
    }

    if (curr == tail) {
        tail = curr->prev;
        tail->next = nullptr;
    }
    else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    curr->prev = nullptr;
    curr->next = head;
    head->prev = curr;
    head = curr;

    return curr->val;
}
```

### Step 1: Check whether the key exists

```cpp
if (mp.find(key) == mp.end())
    return -1;
```

If the key doesn't exist, return `-1`.

Otherwise, retrieve its node directly:

```cpp
Node* curr = mp[key];
```

### Step 2: Check whether the node is already HEAD

```cpp
if (curr == head) {
    return curr->val;
}
```

If the node is already MRU, no pointer manipulation is necessary.

### Step 3: Detach the node

This is one of the most implementation-heavy parts.

There are two possibilities.

**Case A: The node is TAIL**

```cpp
if (curr == tail) {
    tail = curr->prev;
    tail->next = nullptr;
}
```

Example:

Before:

```text
HEAD                  TAIL
 ↓                      ↓
[30] <-> [20] <-> [10]
```

Suppose we access 10.

First move the tail pointer:

```cpp
tail = curr->prev;
```

Then disconnect the old tail:

```cpp
tail->next = nullptr;
```

Result:

```text
HEAD       TAIL
 ↓           ↓
[30] <-> [20]       [10]
```

**Case B: The node is somewhere in the middle**

```cpp
else {
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
}
```

Example:

Before:

```text
[30] <-> [20] <-> [10]
           ↑
          curr
```

We execute:

```cpp
curr->prev->next = curr->next;
curr->next->prev = curr->prev;
```

Result:

```text
[30] <----------> [10]

       [20]
```

The node is now detached from the list.

### Step 4: Insert the node at HEAD

```cpp
curr->prev = nullptr;
curr->next = head;

head->prev = curr;
head = curr;
```

This is the second major pointer manipulation.

Before:

```text
HEAD
 ↓
[30] <-> [20]
```

After inserting 10 at HEAD:

```text
HEAD
 ↓
[10] <-> [30] <-> [20]
```

The accessed node becomes MRU.

**Why do we update these four pointers?**

1. `curr->prev = nullptr`: The new head has no previous node.
2. `curr->next = head`: The new head points to the old head.
3. `head->prev = curr`: The old head points backward to the new head.
4. `head = curr`: Update the actual head pointer.

Finally:

```cpp
return curr->val;
```

---

## 6. Implementation of PUT()

The `put()` operation has two major scenarios:

1. The key does not exist.
2. The key already exists.

### Case A: Capacity is zero

```cpp
if (cap == 0) return;
```

A cache with zero capacity cannot store any elements.

### Case B: Key does not exist

```cpp
if (mp.find(key) == mp.end()) {
    Node* curr = new Node(key, value);
```

Create a new node.

#### B1. Empty cache

```cpp
if (head == nullptr) {
    head = curr;
    tail = curr;
    mp[key] = curr;
    curr_cap++;
    return;
}
```

When inserting the first element, both HEAD and TAIL point to the same node.

```text
HEAD, TAIL
     ↓
   [10]
```

#### B2. Cache is full – EVICTION

```cpp
if (curr_cap == cap) {
    Node* oldTail = tail;
    mp.erase(oldTail->key);
```

This is another extremely important implementation detail.

Before deleting the node, we must remove its entry from the hash map.

```cpp
mp.erase(oldTail->key);
```

Otherwise, the hash map would contain a dangling pointer.

Now handle two possibilities.

**When there is only one node:**

```cpp
if (head == tail) {
    head = nullptr;
    tail = nullptr;
}
```

**When there are multiple nodes:**

```cpp
else {
    tail = tail->prev;
    tail->next = nullptr;
}
```

Finally:

```cpp
delete oldTail;
```

We have now removed the LRU element.

Visual representation:

Before eviction:

```text
HEAD                  TAIL
 ↓                      ↓
[30] <-> [20] <-> [10]
```

After eviction:

```text
HEAD       TAIL
 ↓           ↓
[30] <-> [20]
```

The node containing 10 is deleted.

**Important:** `delete` releases the dynamically allocated node's memory. Updating the linked list and erasing the map entry are separate operations; all three are necessary.

#### B3. Cache is not full

```cpp
else {
    curr_cap++;
}
```

Since no eviction is necessary, increment the current capacity.

#### B4. Insert the new node at HEAD

```cpp
curr->next = head;

if (head != nullptr) {
    head->prev = curr;
}
else {
    tail = curr;
}

head = curr;
mp[key] = curr;
```

The new node always becomes MRU.

Notice the null check:

```cpp
if (head != nullptr)
```

This prevents dereferencing a null pointer.

If the cache was empty after eviction, the new node also becomes TAIL.

---

### Case C: Key already exists

```cpp
else {
    Node* curr = mp[key];
    curr->val = value;
```

First, update the value.

Then we must mark this node as MRU.

If it is already HEAD, nothing else is required.

```cpp
if (curr != head) {
```

Otherwise, detach it.

**If the node is TAIL:**

```cpp
if (curr == tail) {
    tail = curr->prev;
    tail->next = nullptr;
}
```

**If the node is in the middle:**

```cpp
else {
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
}
```

Finally, move it to HEAD:

```cpp
curr->prev = nullptr;
curr->next = head;
head->prev = curr;
head = curr;
```

Notice that we do NOT create a new node or modify `curr_cap`.

We are simply updating the existing node.

---

## 7. Complete Dry Run

Consider:

```cpp
LRUCache cache(3);

cache.put(1, 100);
cache.put(2, 200);
cache.put(3, 300);
cache.get(1);
cache.put(4, 400);
```

Let's visualize every operation.

**Operation 1: `put(1, 100)`**

```text
HEAD, TAIL
     ↓
  [1:100]
```

**Operation 2: `put(2, 200)`**

```text
HEAD          TAIL
 ↓              ↓
[2:200] <-> [1:100]
```

**Operation 3: `put(3, 300)`**

```text
HEAD                       TAIL
 ↓                           ↓
[3:300] <-> [2:200] <-> [1:100]
```

**Operation 4: `get(1)`**

Key 1 is accessed. Move it to HEAD.

```text
HEAD                       TAIL
 ↓                           ↓
[1:100] <-> [3:300] <-> [2:200]
```

**Operation 5: `put(4, 400)`**

The cache is full.

The tail node (key 2) is evicted.

Insert key 4 at HEAD.

```text
HEAD                       TAIL
 ↓                           ↓
[4:400] <-> [1:100] <-> [3:300]
```

Final hash map:

```text
1 → Node(1, 100)
3 → Node(3, 300)
4 → Node(4, 400)
```

Key 2 no longer exists.

---

## 8. Complexity Analysis

| Operation | Time Complexity |
|---|---|
| `get()` | O(1) average |
| `put()` – new key | O(1) average |
| `put()` – existing key | O(1) average |
| Eviction | O(1) |

**Space Complexity: O(C)**

Where C is the maximum cache capacity.

We store at most C linked list nodes and C hash map entries.

---

## 9. Implementation-Heavy Concepts to Remember

These are the most important concepts to understand when implementing an LRU Cache independently.

### 1. Detaching a middle node

```cpp
curr->prev->next = curr->next;
curr->next->prev = curr->prev;
```

Understand how both neighboring nodes are connected after removing `curr`.

### 2. Detaching the tail

```cpp
tail = curr->prev;
tail->next = nullptr;
```

The previous node becomes the new tail.

### 3. Moving a node to HEAD

```cpp
curr->prev = nullptr;
curr->next = head;
head->prev = curr;
head = curr;
```

This operation is used in both `get()` and `put()`.

### 4. Eviction and memory management

```cpp
Node* oldTail = tail;
mp.erase(oldTail->key);
delete oldTail;
```

Never leave a dangling pointer inside the hash map.

### 5. Existing key vs new key

- Existing key: Update its value and move the existing node to HEAD.
- New key: Allocate a new node, evict if necessary, and insert at HEAD.

### 6. Handle edge cases

- Capacity = 0.
- Empty cache.
- Only one node.
- Accessing HEAD.
- Accessing TAIL.
- Accessing a middle node.
- Updating an existing key.
- Inserting when the cache is full.

---

## 10. Final Mental Model

Remember these three rules:

```text
             HEAD
              ↓
       MOST RECENTLY USED
              ↓
      [A] <-> [B] <-> [C]
              ↓
        LEAST RECENTLY USED
              ↓
             TAIL
```

1. **Every successful access moves the node to HEAD.**
2. **Every new insertion happens at HEAD.**
3. **Whenever eviction is required, delete TAIL.**

The hash map finds the node; the doubly linked list maintains the order.

That's the entire LRU Cache algorithm.

---

## 11. Further Improvements

The current implementation can be made more maintainable by extracting repeated pointer operations into helper functions:

- `removeNode(Node* node)`
- `insertAtHead(Node* node)`
- `evictLRU()`

This reduces code duplication between `get()` and `put()` and makes pointer manipulation easier to reason about.

A further improvement would be adding a destructor to free any remaining dynamically allocated nodes when the cache is destroyed.