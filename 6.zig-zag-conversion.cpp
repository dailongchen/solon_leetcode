/*
 * @lc app=leetcode id=6 lang=cpp
 *
 * [6] ZigZag Conversion
 */
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) {
            return s;
        }

        auto strLength = s.length();
        auto zigzagString = string(strLength, ' ');

        auto current = 0;
        for (auto i = 0; i < numRows; i++) {
            auto index = i;
            auto offset_1 = i * 2;
            auto offset_2 = (numRows - i - 1) * 2;

            for (auto j = 0;; j++) {
                if (index >= strLength) {
                    break;
                }

                zigzagString[current++] = s[index];

                if (offset_2 > 0 && i != 0) {
                    auto midIndex = index + offset_2;

                    if (midIndex >= strLength) {
                        break;
                    }

                    zigzagString[current++] = s[midIndex];
                }

                index += offset_1 + offset_2;
            }
        }

        return zigzagString;
    }
};

