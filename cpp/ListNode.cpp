#include<iostream>
using namespace std;

class MyLinkedList{
public:
    struct LinkedNode{
        int val;
        LinkedNode* next;
        LinkedNode(int x):val(x),next(NULL){}
    };

    MyLinkedList(){
        _dummyHead=new LinkedNode(0);
        _size=0;
    }

    int get(int index){
        if(index>_size-1||index<0){
            return -1;
        }
        LinkedNode* cur=_dummyHead->next;
        while(index--){
            cur=cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val){
        LinkedNode *newNode=new LinkedNode(val);
        newNode->next=_dummyHead->next;
        _dummyHead->next=newNode;
        _size++;
    }

    void addAtTail(int val){
        LinkedNode *newNode=new LinkedNode(val);
        LinkedNode *cur=_dummyHead;
        while(cur->next!=NULL){
            cur=cur->next;
        }
        cur->next=newNode;
        _size++;
    }

    void addAtIndex(int index, int val){
        if(index>_size||index<0){
            return;
        }
        LinkedNode *newNode=new LinkedNode(val);
        LinkedNode *cur=_dummyHead;
        
        while(index--){
            cur=cur->next;
        }
        newNode->next=cur->next;
        cur->next=newNode;
        _size++;
    }

    void deleteAtIndex(int index){
        if(index>_size-1||index<0){
            return;
        }
        LinkedNode *cur=_dummyHead;
        while(index--){
            cur=cur->next;
        }
        LinkedNode *tmp=cur->next;
        cur->next=cur->next->next;
        delete tmp;
        _size--;
    }

    void printLinkedList(){
        LinkedNode *cur=_dummyHead;
        while(cur->next!=NULL){
            cout<<cur->next->val<<" ";
            cur=cur->next;
        }
        cout<<endl;
    }

    LinkedNode* removeElements(LinkedNode* head, int val){
        while(head != NULL && head->val == val){
            LinkedNode *tmp = head;
            head = head->next;
            delete tmp;
        }
        LinkedNode* cur = head;
        while(cur != NULL && cur->next != NULL){
            if(cur->next->val == val){
                LinkedNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }else{
                cur = cur->next;
            }
        }
        return head;
    }

    // LinkedNode* reverseList(LinkedNode* head){
    //     LinkedNode* cur=head;
    //     LinkedNode* pre=NULL;
    //     LinkedNode* temp;
    //     while(cur){
    //         temp=cur->next;
    //         cur->next=pre;
    //         pre=cur;
    //         cur=temp;
    //     }
    //     return pre;
    // }
    LinkedNode* reverse(LinkedNode* pre, LinkedNode* cur){
        if(cur==NULL) return pre;
        LinkedNode* tmp=cur->next;
        cur->next=pre;
        return reverse(cur,tmp);
    }

    LinkedNode* reverseList(LinkedNode* head){
        return reverse(NULL,head);
    }

private:
    LinkedNode* _dummyHead;
    int _size;
};

int main(){
    MyLinkedList list;

    cout << "Initial list: ";
    list.printLinkedList();

    // Test addAtHead
    cout << "Test addAtHead:" << endl;
    list.addAtHead(10);
    list.printLinkedList();
    list.addAtHead(20);
    list.printLinkedList();

    // Test addAtTail
    cout << "Test addAtTail:" << endl;
    list.addAtTail(30);
    list.printLinkedList();
    list.addAtTail(40);
    list.printLinkedList();

    // Test addAtIndex
    cout << "Test addAtIndex:" << endl;
    list.addAtIndex(0, 5);   // 头部插入
    list.printLinkedList();
    list.addAtIndex(2, 15);  // 中间插入
    list.printLinkedList();
    list.addAtIndex(100, 99); // 非法下标，不应改变链表
    list.printLinkedList();

    // Test get
    cout << "Test get:" << endl;
    cout << "get(0) = " << list.get(0) << endl;
    cout << "get(2) = " << list.get(2) << endl;
    cout << "get(100) = " << list.get(100) << endl; // 非法下标，应该为 -1

    // Test deleteAtIndex
    cout << "Test deleteAtIndex:" << endl;
    list.deleteAtIndex(0);   // 删除头结点
    list.printLinkedList();
    list.deleteAtIndex(2);   // 删除中间结点
    list.printLinkedList();
    list.deleteAtIndex(100); // 非法下标，不应改变链表
    list.printLinkedList();

    // printLinkedList is already tested above

    // Test removeElements (separate simple list)
    cout << "Test removeElements:" << endl;
    MyLinkedList::LinkedNode* h1 = new MyLinkedList::LinkedNode(1);
    MyLinkedList::LinkedNode* h2 = new MyLinkedList::LinkedNode(2);
    MyLinkedList::LinkedNode* h3 = new MyLinkedList::LinkedNode(2);
    MyLinkedList::LinkedNode* h4 = new MyLinkedList::LinkedNode(3);
    h1->next = h2;
    h2->next = h3;
    h3->next = h4;

    cout << "Original list: ";
    MyLinkedList::LinkedNode* p = h1;
    while(p){
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;

    MyLinkedList::LinkedNode* newHead = list.removeElements(h1, 2);
    cout << "List after removing value 2: ";
    p = newHead;
    while(p){
        cout << p->val << " ";
        MyLinkedList::LinkedNode* tmp = p;
        p = p->next;
        delete tmp; // 释放测试用链表
    }
    cout << endl;

    return 0;
}

