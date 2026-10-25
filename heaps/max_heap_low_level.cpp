#include<bits/stdc++.h>
using namespace std;

class Solution{
    private:
    vector<int>heap;
    void heapifyUp(int i){
        while(i>0){
            int parent=(i-1)/2;
            if(heap[i]>heap[parent]){
                swap(heap[i],heap[parent]);
            }
            else{
                break;
            }
            i=parent;
        }
    }

    void heapifyDown(int i){

        int parent=i;
        int left=2*i+1;
        int right=2*i+2;
        int maximum=parent;
        int n=heap.size();

        if(left<n&&heap[left]>heap[maximum]){
            maximum=left;
        }
        if(right<n&&heap[right]>heap[maximum]){
            maximum=right;
        }
        if(maximum==parent){
            return;
        }
        swap(heap[parent],heap[maximum]);

        heapifyDown(maximum);
    }

    public:
        void initializeHeap(){
            heap.clear();
        }

        void insert(int key){
            heap.push_back(key);
            heapifyUp(heap.size()-1);
        }

        void changeKey(int index, int new_val){
            if(heap[index]>new_val){
                heap[index]=new_val;
                heapifyDown(index);
            }
            else{
                heap[index]=new_val;
                heapifyUp(index);
            }
        }

        void extractMax(){
            if(heap.empty())return;
            heap[0]=heap.back();
            heap.pop_back();
            if(!heap.empty()){
            heapifyDown(0);
            }
        }

        bool isEmpty(){
            return heap.empty();
        }

        int getMax(){
            return heap[0];
        }

        int heapSize(){
            return heap.size();
        }
};