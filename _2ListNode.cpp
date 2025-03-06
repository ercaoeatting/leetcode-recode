#include <algorithm>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class lc203 {
public:
    ListNode *removeElements(ListNode *head, int val) {
        ListNode *tmp;
        while (head != nullptr && head->val == val) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        tmp = head;
        while (tmp != nullptr && tmp->next != nullptr) {
            if (tmp->next->val == val) {
                ListNode *tmpp = tmp->next;
                tmp->next = tmp->next->next;
                delete tmpp;
            }
            else
                tmp = tmp->next;
        }
        return head;
    }
    ListNode *removeElements2(ListNode *head, int val) {
        ListNode *dummyHead = new ListNode();
        dummyHead->next = head;
        ListNode *tmp = dummyHead;
        while (tmp->next != nullptr) {
            if (tmp->next->val == val) {
                ListNode *tmpp = tmp->next;
                tmp->next = tmp->next->next;
                delete tmpp;
            }
            else
                tmp = tmp->next;
        }
        head = dummyHead->next;
        delete dummyHead;
        return head;
    }
    ListNode *removeElements3(ListNode *head, int val) {
        if (head == nullptr) return nullptr;
        head->next = removeElements3(head->next, val);
        return (head->val == val) ? head->next : head;
    }
};
class MyLinkedList {
public:
    /**
     * Your MyLinkedList object will be instantiated and called as such:
     * MyLinkedList* obj = new MyLinkedList();
     * int param_1 = obj->get(index);
     * obj->addAtHead(val);
     * obj->addAtTail(val);
     * obj->addAtIndex(index,val);
     * obj->deleteAtIndex(index);
     */
    struct LinkedNode {
        int val;
        LinkedNode *next;
        LinkedNode(int val) : val(val), next(nullptr) {}
    };
    MyLinkedList() {
        _dummyHead = new LinkedNode(0); // 这里定义的头结点 是一个虚拟头结点，而不是真正的链表头结点
        _size = 0;
    }

    int get(int index) {
        if (index > (_size - 1) || index < 0) return -1;
        LinkedNode *cur = _dummyHead->next;
        for (int ii = 0; ii < index; ii++) { cur = cur->next; }
        return cur->val;
    }

    void addAtHead(int val) {
        LinkedNode *newNode = new LinkedNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        ++_size;
    }

    void addAtTail(int val) {
        LinkedNode *newNode = new LinkedNode(val);
        LinkedNode *cur = _dummyHead;
        while (cur->next != nullptr) { cur = cur->next; }
        cur->next = newNode;
        ++_size;
    }

    void addAtIndex(int index, int val) {
        if (index > _size || index < 0) return;
        LinkedNode *newNode = new LinkedNode(val);
        LinkedNode *cur = _dummyHead;
        for (int ii = 0; ii < index; ii++) { cur = cur->next; }
        newNode->next = cur->next;
        cur->next = newNode;
        ++_size;
    }

    void deleteAtIndex(int index) {
        if (index > (_size - 1) || index < 0) return;
        LinkedNode *cur = _dummyHead;
        for (int ii = 0; ii < index; ii++) { cur = cur->next; }
        LinkedNode *tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        tmp = nullptr;
        --_size;
    }

private:
    int _size;
    LinkedNode *_dummyHead;
};

class lc206 {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *pre = nullptr, *cur = head;
        while (cur) {
            ListNode *tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
    ListNode *reverse(ListNode *pre, ListNode *cur) {
        if (cur == NULL) return pre;
        ListNode *temp = cur->next;
        cur->next = pre;
        // 可以和双指针法的代码进行对比，如下递归的写法，其实就是做了这两步
        // pre = cur;
        // cur = temp;
        return reverse(cur, temp);
    }
    ListNode *reverseList_recursion(ListNode *head) {
        // 和双指针法初始化是一样的逻辑
        // ListNode* cur = head;
        // ListNode* pre = NULL;
        return reverse(NULL, head);
    }
};
class lc24 {
public:
    ListNode *swapPairs(ListNode *head) {
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode *cur = dummyHead;
        while (cur->next != nullptr && cur->next->next != nullptr) {
            ListNode *pre = cur->next;
            ListNode *ppre = pre->next;
            ListNode *pppre = ppre->next;
            cur->next = ppre;
            ppre->next = pre;
            pre->next = pppre;
            cur = cur->next->next;
        }
        return dummyHead->next;
    }
};
class lc19 {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode *cur = dummyHead;
        int size = 0;
        while (cur->next != nullptr) {
            cur = cur->next;
            size++;
        }
        int pos = size - n;
        cur = dummyHead;
        while (pos--) { cur = cur->next; }
        ListNode *tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        return dummyHead->next;
    }
    ListNode *removeNthFromEnd2(ListNode *head, int n) {
        ListNode *dummyHead = new ListNode(0);
        ListNode *slow = dummyHead, *fast = dummyHead;
        while (n-- && fast != nullptr) { fast = fast->next; }
        fast = fast->next;
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode *tmp = slow->next;
        slow->next = tmp->next;
        delete tmp;
        return dummyHead->next;
    }
};
class lw0207 {
public:
    int size(ListNode *head) {
        if (head == nullptr) return 0;
        ListNode *cur = head;
        int size = 0;
        while (cur != nullptr) {
            cur = cur->next;
            ++size;
        }
        return size;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int sizeA = size(headA);
        int sizeB = size(headB);
        int dsize = (sizeA > sizeB) ? (sizeA - sizeB) : (sizeB - sizeA);
        if (sizeA < sizeB) { swap(headA, headB); }
        while (dsize--) { headA = headA->next; }
        while (headA != nullptr) {
            if (headA == headB) return headA;
            headA = headA->next;
            headB = headB->next;
        }
        return nullptr;
    }
};
class lc142 {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) {
                ListNode *index1 = head;
                ListNode *index2 = slow;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2;
            }
        }
        return nullptr;
    }
};
int main() {
    ListNode *head = new ListNode(1);
    ListNode *head2 = lc19().removeNthFromEnd(head, 1);
}