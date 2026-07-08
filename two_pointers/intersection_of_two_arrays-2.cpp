#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> frequency1;
        unordered_map<int, int> frequency2;

        for (int num : nums1) {
            frequency1[num]++;
        }

        for (int num : nums2) {
            frequency2[num]++;
        }

        vector<int> result;

        for (const auto& [num, count] : frequency1) {
            if (frequency2.contains(num)) {
                int commonCount = min(count, frequency2[num]);

                for (int i = 0; i < commonCount; i++) {
                    result.push_back(num);
                }
            }
        }

        return result;
    }
};