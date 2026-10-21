#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        int n=orders.size();
        priority_queue<vector<int>>maxHeap;
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>minHeap;

        for(int i=0;i<n;i++){
            if(orders[i][2]==0){
                int amount=orders[i][1];
                while(amount>0&&!minHeap.empty()&&orders[i][0]>=minHeap.top()[0]){
                    int qty=minHeap.top()[1];
                    int val=minHeap.top()[0];
                    minHeap.pop();
                    if(amount>=qty){
                        amount-=qty;
                    }else{
                        qty-=amount;
                        amount=0;
                        minHeap.push({val,qty});
                    }
                }
                if(amount>0){
                    maxHeap.push({orders[i][0],amount});
                }
            }else{
                int amount=orders[i][1];
                while(amount>0&&!maxHeap.empty()&&orders[i][0]<=maxHeap.top()[0]){
                    int qty=maxHeap.top()[1];
                    int val=maxHeap.top()[0];
                    maxHeap.pop();
                    if(amount>=qty){
                        amount-=qty;
                    }
                    else{
                        qty-=amount;
                        amount=0;
                        maxHeap.push({val,qty});
                    }
                }
                if(amount>0){
                    minHeap.push({orders[i][0],amount});
                }
            }

        }
        long long total=0;
        while(!minHeap.empty()){
            total=(total+minHeap.top()[1])%1000000007;
            minHeap.pop();
        }
        while(!maxHeap.empty()){
            total=(total+maxHeap.top()[1])%1000000007;
            maxHeap.pop();
        }
        return (int)total;
    }
};