/*
 * @lc app=leetcode id=48 lang=cpp
 *
 * [48] Rotate Image
 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        auto n = matrix.size();

        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n - i; j++) {
                auto toX = n - j - 1;
                auto toY = n - i - 1;

                if (i == toX && j == toY) {
                    continue;
                }

                swap(matrix[i][j], matrix[toX][toY]);
            }
        }

        for (auto i = 0; i < n / 2; i++) {
            auto toX = n - i - 1;

            if (i == toX) {
                continue;
            }

            swap(matrix[i], matrix[toX]);
        }

        // printMatrix(matrix);
    }
};

