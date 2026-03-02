#include <iostream>
#include "MyLinkedList.h"

int main()
{
    std::cout << "Hello from CMake demo!" << std::endl;

    MyLinkedList list;
    list.addAtHead(10);
    list.addAtTail(20);
    list.addAtTail(30);

    std::cout << "Linked list: ";
    list.printLinkedList();
    std::cout << "Linked list test ===> ";
    return 0;
}
