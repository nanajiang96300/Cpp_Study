#include <iostream>

class A
{
public:
    int data;
    A() { std::cout << "A constructor" << std::endl; }
};

// 使用 virtual 继承
class B : virtual public A
{
public:
    B() { std::cout << "B constructor" << std::endl; }
};

// 使用 virtual 继承
class C : virtual public A
{
public:
    C() { std::cout << "C constructor" << std::endl; }
};

// D 现在只包含一个 A 的实例
class D : public B, public C
{
public:
    D() { std::cout << "D constructor" << std::endl; }
};

int main()
{
    D obj;
    obj.data = 100; // ✅ 编译通过！不再有二义性
    std::cout << "Data: " << obj.data << std::endl;
    return 0;
}