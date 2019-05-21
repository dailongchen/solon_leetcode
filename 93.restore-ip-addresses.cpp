/*
 * @lc app=leetcode id=93 lang=cpp
 *
 * [93] Restore IP Addresses
 */
class Solution {
private:
    bool isValidSubnet(const string& s, size_t from, size_t count) {
        if (from + count > s.size()) {
            return false;
        }

        if (count == 1) {
            return true;
        } else if (count == 2) {
            if (s[from] == '0') {
                return false;
            }

            return true;
        } else if (count == 3) {
            if (s[from] == '0') {
                return false;
            } else if (s[from] != '1' && s[from] != '2') {
                return false;
            } else if (s[from] == '2') {
                if (s[from + 1] - '5' > 0) {
                    return false;
                } else if (s[from + 1] == '5') {
                    if (s[from + 2] - '5' > 0) {
                        return false;
                    }
                }
            }

            return true;
        }

        return false;
    }

    size_t nextPossibleSubnetLength(const string& s, size_t from) {
        size_t c = 0;
        for (size_t i = 1; i <= 3; i++) {
            if (isValidSubnet(s, from, i)) {
                c = i;
                continue;
            }
            break;
        }

        return c;
    }

public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> results;

        auto possibleLength_1 = nextPossibleSubnetLength(s, 0);
        // cout << "possibleLength_1: " << possibleLength_1 << endl;
        if (possibleLength_1 == 0) {
            return results;
        }

        for (size_t a = 1; a <= possibleLength_1; a++) {
            auto possibleLength_2 = nextPossibleSubnetLength(s, a);
            // cout << "possibleLength_2: " << possibleLength_1 << endl;
            if (possibleLength_2 == 0) {
                break;
            }

            for (size_t b = 1; b <= possibleLength_2; b++) {
                auto possibleLength_3 = nextPossibleSubnetLength(s, a + b);
                // cout << "possibleLength_3: " << possibleLength_1 << endl;
                if (possibleLength_3 == 0) {
                    break;
                }

                for (size_t c = 1; c <= possibleLength_3; c++) {
                    size_t from = a + b + c;
                    size_t length = s.size() - from;
                    if (!isValidSubnet(s, from, length)) {
                        continue;
                    }

                    results.push_back(s.substr(0, a) + "." +
                                      s.substr(a, b) + "." +
                                      s.substr(a + b, c) + "." +
                                      s.substr(a + b + c));
                }
            }
        }

        return results;
    }
};

