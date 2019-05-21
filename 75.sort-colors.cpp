/*
 * @lc app=leetcode id=75 lang=cpp
 *
 * [75] Sort Colors
 */
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int whiteStart = 0;
        int whiteCount = 0;

        for (int i = 0; i < nums.size(); i++) {
            const int current = nums[i];
            nums[i] = 2;

            switch (current) {
            case 0: {
                if (whiteCount > 0) {
                    nums[whiteStart + whiteCount] = 1;
                }
                nums[whiteStart] = 0;
                whiteStart++;
            }
            break;

            case 1: {
                nums[whiteStart + whiteCount] = 1;
                whiteCount++;
            }
            break;

            case 2:
            break;

            default:
            break;
            }
        }
    }
};

