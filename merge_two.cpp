#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {

        ListNode *result = nullptr;
        ListNode *root = nullptr;
        int temp;

        while (list1 != nullptr || list2 != nullptr)
        {

            if (list1->val < list2->val)
            {
                temp = list1->val;
                list1 = list1->next;
            }
            else
            {
                temp = list2->val;
                list2 = list2->next;
            }

            if (result == nullptr)
            {
                *root = ListNode(temp);
                result = root;
            }
            else
            {
                result->next = new ListNode(temp);
            }
        }

        if (list1 != nullptr)
        {
            while (list1 != nullptr)
            {
                if (result == nullptr)
                {
                    *root = ListNode(temp);
                    result = root;
                }
                else
                {
                    result->next = new ListNode(temp);
                }

                list1 = list1->next;
            }
        }

        if (list2 != nullptr)
        {
            while (list2 != nullptr)
            {
                if (result == nullptr)
                {
                    *root = ListNode(temp);
                    result = root;
                }
                else
                {
                    result->next = new ListNode(temp);
                }

                list2 = list2->next;
            }
        }

        return result;
    }
};