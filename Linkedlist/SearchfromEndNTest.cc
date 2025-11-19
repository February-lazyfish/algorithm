#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std; 

struct linkedNode{
	int val;
	linkedNode * next;
	linkedNode(int x) :val(x),next(nullptr){}
};

linkedNode * createList(){
	linkedNode * head = new linkedNode(0);
	linkedNode * current = head;
	
	for(int i=0;i<16;i++){
		linkedNode * create = new linkedNode(i);
		current->next=create;
		current=current->next;
	}
	return head;
}

int findKthFromEnd(linkedNode * head,int k){
	linkedNode * fast = head;
	linkedNode * slow = head;
	for(int i = 0;i<k;i++){
		if(fast==nullptr)
			return -1;
		fast=fast->next;
	}	
	
	while(fast!=nullptr){
		fast=fast->next;
		slow=slow->next;
	}
	return slow->val;
}

// 打印链表
void printList(linkedNode* head) {
    linkedNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}
int main(void)
{
	 linkedNode* head = createList();
    
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
