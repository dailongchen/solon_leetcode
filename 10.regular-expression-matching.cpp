/*
 * @lc app=leetcode id=10 lang=cpp
 *
 * [10] Regular Expression Matching
 */
class Solution {
private:
    class Pattern {
    private:
        string m_leading;
        char m_optionalChar;
        bool m_repeatOptionalChar;

    public:
        Pattern(const string& leading, bool repeatLastChar) : m_optionalChar('\0'), m_repeatOptionalChar(repeatLastChar) {
            auto lastChar = leading[leading.length() - 1];
            if (repeatLastChar || lastChar == '.') {
                m_leading = leading.substr(0, leading.length() - 1);
                m_optionalChar = lastChar;
            } else {
                m_leading = leading;
            }
        }

        operator string() const {
            stringstream ss;
            ss << "leading: (" << m_leading
               << "), optionalChar: (" << m_optionalChar
               << "), repeat: (" << (m_repeatOptionalChar ? "true" : "false") << ")" << endl;
            return string(ss.str());
        }

        bool operator==(const Pattern& other) const {
            return m_leading == other.m_leading &&
                   m_optionalChar == other.m_optionalChar &&
                   m_repeatOptionalChar == other.m_repeatOptionalChar;
        }

        bool Matching(const string& str, int index, int& optionalFrom, int& optionalTo) const {
            if (m_leading.length() > 0) {
                if (index + m_leading.length() > str.length()) {
                    return false;
                }

                for (auto i = 0; i < m_leading.length(); i++) {
                    if (str[index + i] != m_leading[i]) {
                        return false;
                    }
                }

                index += m_leading.length();
            }

            if (!m_repeatOptionalChar) {
                if (m_optionalChar == '.') {
                    if (index + 1 > str.length()) {
                        return false;
                    }
                    optionalFrom = index + 1;
                    optionalTo = index + 1;
                } else {
                    optionalFrom = index;
                    optionalTo = index;
                }
            } else {
                if (m_optionalChar == '.') {
                    optionalFrom = index;
                    optionalTo = index > str.length() ? index : str.length();
                } else {
                    optionalFrom = index;

                    for (; index < str.length(); index++) {
                        if (str[index] != m_optionalChar) {
                            break;
                        }
                    }
                    optionalTo = index;
                }
            }

            return true;
        }
    };

    vector<Pattern> getPatterns(const string& p) {
        vector<Pattern> patterns;

        auto findPattern = [&patterns](const string& p, bool repeatLastChar) {
            auto index = 0;
            while (index < p.length()) {
                auto pos = p.find_first_of('.', index);

                if (pos == string::npos || pos == p.length() - 1) {
                    patterns.push_back(Pattern(p.substr(index), repeatLastChar));
                    break;
                }

                patterns.push_back(Pattern(p.substr(index, pos - index + 1), false));
                index = pos + 1;
            }
        };

        auto index = 0;
        while (index < p.length()) {
            auto pos = p.find_first_of('*', index);

            if (pos == string::npos) {
                findPattern(p.substr(index), false);
                break;
            }

            findPattern(p.substr(index, pos - index), true);
            index = pos + 1;
        }

        return patterns;
    }

public:
    bool isMatch(string s, string p) {
        auto patterns = getPatterns(p);
        if (patterns.size() == 0) {
            return s.length() == 0;
        }

        // for (auto& item : patterns) {
        //     cout << string(item);
        // }

        typedef struct _PendingItem_ {
            int OptionalFrom;
            int OptionalTo;

            _PendingItem_(int optionalFrom, int optionalTo)
            : OptionalFrom(optionalFrom), OptionalTo(optionalTo) {}
        } PendingItem;

        vector<vector<PendingItem>> pendingItemList(patterns.size());
        auto currentPatternIndex = 0;
        auto currentOptionalFrom = 0;
        auto currentOptionalTo = 0;

        while (true) {
            // cout << currentPatternIndex << " currentOptionalFrom " << currentOptionalFrom << " currentOptionalTo " << currentOptionalTo << endl;
            auto isLastPattern = currentPatternIndex == (patterns.size() - 1);

            auto currentPattern = patterns[currentPatternIndex];

            pendingItemList[currentPatternIndex].clear();

            auto canMatch = false;
            for(auto index = currentOptionalFrom;
                index <= currentOptionalTo;
                index++) {
                int optionalFrom;
                int optionalTo;

                if (currentPattern.Matching(s, index, optionalFrom, optionalTo)) {
                    // cout << currentPatternIndex << " " << index << " " << optionalFrom << " " << optionalTo << endl;
                    if (isLastPattern) {
                        if (optionalTo >= s.length()) {
                            return true;
                        } else {
                            continue;
                        }
                    }

                    pendingItemList[currentPatternIndex].push_back(PendingItem(optionalFrom, optionalTo));
                    canMatch = true;
                }
            }

            if (canMatch) {
                if (!isLastPattern) {
                    currentOptionalFrom = pendingItemList[currentPatternIndex].back().OptionalFrom;
                    currentOptionalTo = pendingItemList[currentPatternIndex].back().OptionalTo;
                    currentPatternIndex++;
                    continue;
                }
            }

            pendingItemList[currentPatternIndex].clear();
            currentPatternIndex--;

            while (currentPatternIndex >= 0) {
                pendingItemList[currentPatternIndex].pop_back();
                if (!pendingItemList[currentPatternIndex].empty()) {
                    currentOptionalFrom = pendingItemList[currentPatternIndex].back().OptionalFrom;
                    currentOptionalTo = pendingItemList[currentPatternIndex].back().OptionalTo;
                    currentPatternIndex++;
                    break;
                }
                currentPatternIndex--;
            }

            if (currentPatternIndex < 0) {
                return false;
            }
        }
    }
};

