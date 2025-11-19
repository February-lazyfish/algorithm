#include <iostream>
using namespace std;

// 链表节点
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 创建16个节点的链表
ListNode* createList() {
    ListNode* head = new ListNode(1);
    ListNode* current = head;
    
    for (int i = 2; i <= 16; i++) {
        current->next = new ListNode(i);
        current = current->next;
    }
    return head;
}

// 双指针法查找倒数第k个节点
int findKthFromEnd(ListNode* head, int k) {
    if (head == nullptr || k <= 0) {
        return -1; // 错误标识
    }
    ListNode* fast = head;
    ListNode* slow = head;
    // 快指针先走k步
    for (int i = 0; i < k; i++) {
        if (fast == nullptr) {
            return -1; // k超过链表长度
        }
        fast = fast->next;
    }
    
    // 两个指针同时前进，直到快指针到达末尾
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    
    return slow->val;
}

// 打印链表
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    // 创建16个节点的链表
    ListNode* head = createList();
    
    cout << "链表: ";
    printList(head);
    cout << endl;
    
    // 测试查找倒数第k个节点
    int k = 3; // 查找倒数第3个节点
    int result = findKthFromEnd(head, k);
    
    if (result != -1) {
        cout << "倒数第 " << k << " 个节点的值是: " << result << endl;
    } else {
        cout << "查找失败，k值不合法或超过链表长度" << endl;
    }
    
    // 测试其他k值
    int testCases[] = {1, 5, 16};
    for (int k : testCases) {
        int result = findKthFromEnd(head, k);
        cout << "倒数第 " << k << " 个节点的值是: " << result << endl;
    }
    
    return 0;
}


/*fast 必须越界变成 null 的同时，slow 才能正好停在倒数第 k 个节点。
为什么？
因为 fast 比 slow 永远领先 k 个节点。
链表向右移动了k次
 *
 *
 *
 *
 *
 *
 *
 * */
