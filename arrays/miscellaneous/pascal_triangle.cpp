#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> pascal;

        // First row of Pascal's Triangle
        pascal.push_back({1});

        // Build remaining rows
        for (int i = 1; i < numRows; i++) {
            vector<int> row;

            // Every row starts with 1
            row.push_back(1);

            // Each middle element is the sum of two elements above it
            for (int j = 1; j < i; j++) {
                row.push_back(pascal[i - 1][j - 1] + pascal[i - 1][j]);
            }

            // Every row ends with 1
            row.push_back(1);

            pascal.push_back(row);
        }

        return pascal;
    }
};