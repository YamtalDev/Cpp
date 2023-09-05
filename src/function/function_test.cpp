/******************************************************************************

  Writer: Tal Aharon

  Reviewer: Shay Yazdi.

  Date: 31.08.2023

******************************************************************************/
#include <cassert>      /* assert       */
#include <iostream>     /* std::cout    */
#include "function.hpp" /* Internal API */
/*****************************************************************************/
int FreeFunctionInt(int x)
{
    return (x * 2);
}

char FreeFunctionChar(char x)
{
    return (x + 1);
}

void FreeFunctionVoid(int *x)
{
    (*x + 1);
}


double FreeFunctionDouble(double x)
{
    return (x + 3.14);
}

class Object
{
public:
    Object(int val) : m_value(val) 
    {
        // Empty
    }

    int MemberFunction(int x)
    {
        return (m_value + x);
    }

private:
    int m_value;
};

class Object1
{
public:
    Object1(int val) : m_ptr(new int(val)) 
    {
        // Empty
    }

    ~Object1()
    {
        delete (m_ptr);
        m_ptr = 0;
    }

    int MemberFunction(int x)
    {
        return (*m_ptr + x);
    }

private:
    int *m_ptr;
};


int FreeFunctionObject(Object x)
{
    return (x.MemberFunction(5));
}
/*****************************************************************************/
using namespace ilrd_rd141;
void TestFreeFunction(void);
void TestObjectMemberFunctions(void);
/*****************************************************************************/
int main(void)
{
    TestFreeFunction();
    TestObjectMemberFunctions();
    std::cout << "All tests passed" << std::endl;
    return (0);
}
/*****************************************************************************/
void TestFreeFunction(void)
{
    int i = 5;
    int *y = &i;
    char x = '0';
    Object obj(1);
    Function<int(void)> func1(FreeFunctionInt, 5);
    Function<char(void)> func3(FreeFunctionChar, x);
    Function<void(void)> func4(FreeFunctionVoid, y);
    Function<int(void)> func(FreeFunctionObject, obj);
    Function<double(void)> func2(FreeFunctionDouble, 2.0);

    func4();
    assert(6 == func());
    assert(6 == *y);
    assert(func1() == 10);
    assert('1' == func3());
    assert(std::abs(func2() - 5.14) < 1e-6);
}
/*****************************************************************************/
void TestObjectMemberFunctions(void)
{
    Object obj2(7);
    Object obj1(10);
    Object1 obj3(130);

    Function<int(void)> func1(&Object::MemberFunction, &obj1, 5);
    Function<int(void)> func2(&Object::MemberFunction, &obj2, 3);
    Function<int(void)> func3(&Object1::MemberFunction, &obj3, 70);

    assert(15 == func1());
    assert(10 == func2());
    assert(200 == func3());
}
/*****************************************************************************/