#include<bits/stdc++.h>
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node==nullptr){
            return NULL;
        }
        unordered_map<Node*,Node*>mp;
        Node* new_node=new Node(node->val);
        mp[node]=new_node;

        queue<Node*>q;
        q.push(node);
        while(!q.empty()){
            Node* vertex=q.front();
            q.pop();
            for(auto nodei:vertex->neighbors){
                if(mp.find(nodei)==mp.end()){
                    Node* new_nodei=new Node(nodei->val);
                    mp[nodei]=new_nodei;
                    q.push(nodei);
                }
            }
        }
        for(auto node:mp){
            Node* orig=node.first;
            Node* clone=node.second;
            for(auto nodei:orig->neighbors){
                clone->neighbors.push_back(mp[nodei]);
            }
        }
        return new_node;
    }
};