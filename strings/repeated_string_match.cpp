#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        int n = a.length();
        int m = b.length();
        
        long long p = 31;
        long long mod = 1e9 + 7;
        
        long long hash_b = 0;
        long long hash_a = 0;
        long long p_pow = 1;
        
        for (int i = 0; i < m - 1; i++) {
            p_pow = (p_pow * p) % mod;
        }
        
        for (int i = 0; i < m; i++) {
            hash_b = (hash_b * p + (b[i] - 'a' + 1)) % mod;
            hash_a = (hash_a * p + (a[i % n] - 'a' + 1)) % mod;
        }
        
        for (int i = 0; i < n; i++) {
            
            if (hash_a == hash_b) {
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (a[(i + j) % n] != b[j]) {
                        match = false;
                        break;
                    }
                }
                
                if (match) {
                    return (i + m - 1) / n + 1;
                }
            }

            hash_a = (hash_a - (a[i] - 'a' + 1) * p_pow) % mod;
            if (hash_a < 0) {
                hash_a += mod;
            }
            
            hash_a = (hash_a * p + (a[(i + m) % n] - 'a' + 1)) % mod;
        }
        
        return -1;
    }
};
