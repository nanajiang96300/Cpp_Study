#include "MyLinkedList.h"

MyLinkedList::MyLinkedList()
    : _dummyHead(new LinkedNode(0)), _size(0) {}

MyLinkedList::~MyLinkedList()
{
    LinkedNode *cur = _dummyHead;
    while (cur)
    {
        LinkedNode *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

void MyLinkedList::addAtHead(int val)
{
    LinkedNode *newNode = new LinkedNode(val);
    newNode->next = _dummyHead->next;
    _dummyHead->next = newNode;
    ++_size;
}

void MyLinkedList::addAtTail(int val)
{
    LinkedNode *newNode = new LinkedNode(val);
    LinkedNode *cur = _dummyHead;
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = newNode;
    ++_size;
}

void MyLinkedList::printLinkedList() const
{
    LinkedNode *cur = _dummyHead->next;
    while (cur)
    {
        std::cout << cur->val << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}
