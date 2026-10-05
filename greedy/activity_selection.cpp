#include<bits/stdc++.h>
using namespace std;

struct item{
    int start;
    int finish;
};
struct Compare{
    bool operator()(const item&a,const item&b){
        return a.finish<b.finish;
    }
};
class Solution {
  public:
    int activitySelection(vector<int> &start, vector<int> &finish) {
        // code here
        vector<struct item>items;
        int n=start.size();
        for(int i=0;i<n;i++){
            item s;
            s.start=start[i];
            s.finish=finish[i];
            items.push_back(s);
        }
        sort(items.begin(),items.end(),Compare());
        
        vector<int>selection;
        for(int i=0;i<n;i++){
            if(selection.size()==0){
                selection.push_back(items[i].finish);
                continue;
            }
            if(items[i].start>selection.back()){
                selection.push_back(items[i].finish);
            }
        }
        return selection.size();
    }
};