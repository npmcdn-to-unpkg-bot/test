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
	// 72%
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1 && !l2) {
            return nullptr;
        }
        ListNode *res = nullptr, *current = nullptr, *p1 = l1, *p2 = l2;
        int up = 0;
        while (true) {
            if (!p1 && !p2 && up == 0) {
                break;
            }

            int sum = up;
            up = 0;
            if (p1) {
                sum += p1->val;
                p1 = p1->next;
            }
            if (p2) {
                sum += p2->val;
                p2 = p2->next;
            }
            if (sum > 9) {
                up = 1;
                sum -= 10;
            }
            ListNode* node = new ListNode(sum);
            if (res) {
                current->next = node;
            } else {
                res = node;
            }
            current = node;
        }
        return res;
    }
};