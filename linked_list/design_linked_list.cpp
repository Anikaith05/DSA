#include<bits/stdc++.h>
using namespace std;

class MyLinkedList {
public:
    struct Node{
        int val;
        Node*prev;
        Node*next;

        Node(int v){
            val=v;
            prev=nullptr;
            next=nullptr;
        }
    };
    int tail_index;
    Node*head;
    Node*tail;
    MyLinkedList() {
        tail_index=-1;
        head=nullptr;
        tail=nullptr;
    }
    
    int get(int index) {
        if(index>tail_index){
            return -1;
        }
        if(index==0){
            return head->val;
        }
        if(index==tail_index){
            return tail->val;
        }
        int x=index;
        Node*temp=head;
        while(x--){
            temp=temp->next;
        }
        return temp->val;
    }
    
    void addAtHead(int val) {
        Node*curr=new Node(val);
        tail_index++;
        if(head==nullptr){
            head=curr;
            tail=curr;
            return;
        }
        curr->next=head;
        head->prev=curr;
        head=curr;
        return;
    }
    
    void addAtTail(int val) {
        Node*curr=new Node(val);
        tail_index++;
        if(tail==nullptr){
            head=curr;
            tail=curr;
            return;
        }
        tail->next=curr;
        curr->prev=tail;
        tail=curr;
        return;
    }
    
    void addAtIndex(int index, int val) {
        if(index>tail_index+1){
            return;
        }
        tail_index++;
        Node*curr=new Node(val);
        if(index==0){
            if(head==nullptr){
                head=curr;
                tail=curr;
                return;
            }
            curr->next=head;
            head->prev=curr;
            head=curr;
            return;
        }
        if(index==tail_index){
            tail->next=curr;
            curr->prev=tail;
            tail=curr;
            return;
        }
        int x=index;
        Node*temp=head;
        while(x--){
            temp=temp->next;
        }
        curr->next=temp;
        temp->prev->next=curr;
        curr->prev=temp->prev;
        temp->prev=curr;
    }
    
    void deleteAtIndex(int index) {
        if(index>tail_index) return;
        if(index==0){
            if(head->next!=nullptr){
                head=head->next;
                head->prev=nullptr;
            }else{
                head=nullptr;
                tail=nullptr;
            }
            tail_index--;
            return;
        }
        if(index==tail_index){
            tail=tail->prev;
            tail->next=nullptr;
            tail_index--;
            return;
        }
        Node*temp=head;
        int x=index;
        while(x--){
            temp=temp->next;
        }
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        temp->next=nullptr;
        temp->prev=nullptr;
        delete temp;
        tail_index--;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */