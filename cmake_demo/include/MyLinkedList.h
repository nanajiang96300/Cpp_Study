#pragma once

#include <iostream>

class MyLinkedList
{
public:
    struct LinkedNode
    {
        int val;
        LinkedNode *next;
        LinkedNode(int x) : val(x), next(nullptr) {}
    };

    MyLinkedList();
    ~MyLinkedList();

    void addAtHead(int val);
    void addAtTail(int val);
    void printLinkedList() const;

private:
    LinkedNode *_dummyHead;
    int _size;
};
