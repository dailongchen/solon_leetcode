/*
 * @lc app=leetcode id=416 lang=cpp
 *
 * [416] Partition Equal Subset Sum
 */

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        auto sum = 0;
        for_each(nums.cbegin(), nums.cend(), [&sum](int n) { sum += n; });

        if (sum % 2 != 0) {
            return false;
        }

        sort(nums.begin(), nums.end());

        auto halfSum = sum / 2;

        auto found = false;
        set<int> records;
        for_each(nums.cbegin(), nums.cend(), [halfSum, &records, &found](int n) {
            if (n > halfSum) {
                return;
            }

            if (n == halfSum) {
                found = true;
                return;
            }

            set<int> newRecords;
            newRecords.insert(n);

            for (auto iter = records.cbegin(); iter != records.cend(); iter++) {
                auto record = *iter + n;
                if (record == halfSum) {
                    found = true;
                    return;
                }
                if (record > halfSum) {
                    continue;
                }
                newRecords.insert(record);
            }

            records.insert(newRecords.begin(), newRecords.end());
        });

        return found;
    }
};

