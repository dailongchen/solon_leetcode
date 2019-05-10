/*
 * @lc app=leetcode id=19 lang=cpp
 *
 * [19] Remove Nth Node From End of List
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (n <= 0) {
            return head;
        }

        ListNode *parentNode = nullptr;
        ListNode *nthNode = nullptr;

        auto index = 1;
        auto currentNode = head;
        while (currentNode != nullptr) {
            if (index == n) {
                nthNode = head;
            } else if (index > n) {
                parentNode = nthNode;
                nthNode = nthNode->next;
            }

            currentNode = currentNode->next;
            index++;
        }

        if (nthNode != nullptr) {
            if (parentNode != nullptr) {
                parentNode->next = nthNode->next;
            } else {
                // removed the first node
                return nthNode->next;
            }
        }

        return head;
    }
};

