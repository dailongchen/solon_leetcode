/*
 * @lc app=leetcode id=79 lang=cpp
 *
 * [79] Word Search
 */
class Solution {
private:
    bool check(vector<vector<char>>& board, const string& word, int charIndex, vector<pair<int, int>>& history, int i, int j) {
        if (charIndex >= word.length()) {
            return true;
        }

        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
            return false;
        }

        if (find(history.begin(), history.end(), make_pair(i, j)) != history.end()) {
            return false;
        }

        if (word[charIndex] != board[i][j]) {
            return false;
        }

        history.push_back(make_pair(i, j));

        if (check(board, word, charIndex + 1, history, i + 1, j)) {
            return true;
        }

        if (check(board, word, charIndex + 1, history, i, j + 1)) {
            return true;
        }

        if (check(board, word, charIndex + 1, history, i - 1, j)) {
            return true;
        }

        if (check(board, word, charIndex + 1, history, i, j - 1)) {
            return true;
        }

        history.pop_back();

        return false;
    }

    bool check(vector<vector<char>>& board, const string& word, int i, int j) {
        vector<pair<int, int>> history;

        return check(board, word, 0, history, i, j);
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        if (word.length() == 0) {
            return false;
        }

        if (word.length() > board.size() * board[0].size()) {
            return false;
        }

        for (auto i = 0; i < board.size(); i++) {
            for (auto j = 0; j < board[0].size(); j++) {
                if (board[i][j] == word[0]){
                    if (check(board, word, i, j)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

