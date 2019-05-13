/*
 * @lc app=leetcode id=30 lang=cpp
 *
 * [30] Substring with Concatenation of All Words
 */
class Solution {
private:
    class StringProvider {
    private:
        const string& m_str;
        const int m_steps;

        int m_currentPosition;

    public:
        StringProvider(const string& str, int steps)
        : m_str(str), m_steps(steps), m_currentPosition(0) {
        }

        string next() {
            if (isEnd()) {
                return "";
            }

            auto subString = m_str.substr(m_currentPosition, m_steps);
            m_currentPosition += m_steps;

            return subString;
        }

        void setCurrent(int current) {
            m_currentPosition = current;
        }

        bool isEnd() const {
            return m_currentPosition + m_steps > m_str.length();
        }
    };

    class MatchingWords {
    private:
        const vector<string>& m_words;
        const int m_wordLength;
        const int m_wordCount;

        vector<bool> m_marks;

    public:
        MatchingWords(const vector<string>& words)
        : m_words(words),
        m_wordCount(words.size()),
        m_wordLength(words.size() > 0 ? words[0].length() : 0) {
            m_marks = vector<bool>(m_wordCount, false);
        }

        int getWordLength() const {
            return m_wordLength;
        }

        int getWordCount() const {
            return m_wordCount;
        }

        bool mark(const string& word) {
            for (auto iter = m_words.cbegin(); iter != m_words.cend(); iter++) {
                auto index = distance(m_words.cbegin(), iter);
                if (m_marks[index]) {
                    continue;
                }

                if (*iter == word) {
                    m_marks[index] = true;
                    return true;
                }
            }

            return false;
        }

        void resetMarks() {
            for (auto iter = m_marks.begin(); iter != m_marks.end(); iter++) {
                *iter = false;
            }
        }
    };

    bool hasSameWords(
        StringProvider& strProvider,
        MatchingWords& matching) {

        auto isSame = true;
        for (auto i = 0; i < matching.getWordCount(); i++) {
            auto str = strProvider.next();
            if (str.empty()) {
                isSame = false;
                break;
            }

            if (!matching.mark(str)) {
                isSame = false;
                break;
            }
        }

        matching.resetMarks();
        return isSame;
    }

public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> output;

        if (words.size() > 0) {
            MatchingWords matching(words);
            auto wordLength = matching.getWordLength();

            StringProvider strProvider(s, wordLength);

            for (auto offset = 0; offset < wordLength; offset++) {
                strProvider.setCurrent(offset);

                auto current = offset;
                while (true) {
                    if (hasSameWords(strProvider, matching)) {
                        output.push_back(current);
                    } else {
                        if (strProvider.isEnd()) {
                            break;
                        }
                    }

                    current += wordLength;
                    strProvider.setCurrent(current);
                }
            }
        }

        return output;
    }
};

