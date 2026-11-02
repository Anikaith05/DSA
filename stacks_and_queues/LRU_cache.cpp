#include<bits/stdc++.h>
using namespace std;

class LRUCache {
private:
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

    unordered_map<int, Node*> mp;
    int cap;
    int curr_cap;
    Node *head;
    Node *tail;

public:
    LRUCache(int capacity) {
        head = nullptr;
        tail = nullptr;
        cap = capacity;
        curr_cap = 0;
    }

    int get(int key) {
        if (mp.find(key) == mp.end()) return -1;

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

    void put(int key, int value) {
        if (cap == 0) return;

        if (mp.find(key) == mp.end()) {
            Node* curr = new Node(key, value);

            if (head == nullptr) {
                head = curr;
                tail = curr;
                mp[key] = curr;
                curr_cap++;
                return;
            }

            if (curr_cap == cap) {
                Node* oldTail = tail;
                mp.erase(oldTail->key);

                if (head == tail) {
                    head = nullptr;
                    tail = nullptr;
                }
                else {
                    tail = tail->prev;
                    tail->next = nullptr;
                }

                delete oldTail;
            }
            else {
                curr_cap++;
            }

            curr->next = head;
            // FIX: Ensure head is not null before assigning prev
            if (head != nullptr) {
                head->prev = curr;
            } else {
                tail = curr;
            }
            head = curr;
            mp[key] = curr;
        }
        else {
            Node* curr = mp[key];
            curr->val = value;

            if (curr != head) {
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
            }
        }
    }
};