/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Ravit Yehudi.

    Date: 17.08.2023

*******************************************************************************

                          Description:

   The SharedPointer tests cover functionality such as copy operations, destructor 
   behavior, dereferencing, and inheritance support. The Base and Derived classes 
   establish a simple inheritance hierarchy with overridden methods. The tests ensure 
   that the SharedPointer correctly manages ownership and polymorphism.

******************************************************************************/
#include <iostream>                          /* cout           */

#include "../../include/assertal.hpp"        /* Tests           */
#include "shared_pointer.hpp"                /* Internal API    */
/*****************************************************************************/
class Base
{
public:
    virtual ~Base() {}
    virtual int GetValue() const
    {
        return 0;
    }
};

class Derived : public Base
{
public:
    Derived(int value) : m_value(value) {}
    int GetValue() const override 
    {
        return m_value;
    }

private:
    int m_value;
};
/*****************************************************************************/
using namespace ilrd_rd141;
void SharedPointerGetPointerTest(void);
void SharedPointerDestructorsTest(void);
void SharedPointerInheritanceTest(void);
void SharedPointerDereferencingTest(void);
void SharedPointerCopyAssignmentTest(void);
void SharedPointerCopyConstructorTest(void);
/*****************************************************************************/
int main(void)
{
    SharedPointerGetPointerTest();
    SharedPointerDestructorsTest();
    SharedPointerInheritanceTest();
    SharedPointerDereferencingTest();
    SharedPointerCopyAssignmentTest();
    SharedPointerCopyConstructorTest();
    std::cout << "All test passed" << std::endl;
    return (0);
}
/*****************************************************************************/
void SharedPointerGetPointerTest(void)
{
    int value = 42;
    SharedPointer<int> ptr(new int(value));
    SharedPointer<int> ptr1(ptr);
    TestEqual(ptr.GetPointer(), ptr.GetPointer(), "Should be equal");
}
/*****************************************************************************/
void SharedPointerDestructorsTest(void)
{
    {    
        int value = 42;
        SharedPointer<int> ptr(new int(value));
    }

}
/*****************************************************************************/
void SharedPointerCopyConstructorTest(void)
{
    int value = 42;
    SharedPointer<int> originalPtr(new int(value));
    SharedPointer<int> copiedPtr(originalPtr);
    TestEqual(copiedPtr.GetPointer(), copiedPtr.GetPointer(), "Should be equal");
    TestEqual(*copiedPtr, value, "Should be equal");
    TestEqual(*originalPtr, value, "Should be equal");
    TestEqual(*originalPtr, *copiedPtr, "Should be equal");
}
/*****************************************************************************/
void SharedPointerDereferencingTest(void)
{
    int value = 42;
    SharedPointer<int> originalPtr(new int(value));
    SharedPointer<int> copiedPtr = originalPtr;
    TestEqual(originalPtr.operator->(), copiedPtr.operator->(), "Should be equal");
    TestEqual(originalPtr.operator*(), copiedPtr.operator*(), "Should be equal");

    struct stru
    {
        int val;
    };

    SharedPointer<stru> s(new stru());
    s->val = 1;

    TestEqual(s->val, 1, "Should be equal");
    TestEqual(s->val, (*s).val, "Should be equal");
}
/*****************************************************************************/
void SharedPointerCopyAssignmentTest(void)
{
    int value = 42;
    SharedPointer<int> originalPtr(new int(value));
    SharedPointer<int> copiedPtr = originalPtr;
    TestEqual(copiedPtr.GetPointer(), copiedPtr.GetPointer(), "Should be equal");
    TestEqual(*copiedPtr, value, "Should be equal");
    TestEqual(*originalPtr, value, "Should be equal");
    TestEqual(*originalPtr, *copiedPtr, "Should be equal");
}
/*****************************************************************************/
void SharedPointerInheritanceTest(void)
{
    SharedPointer<Base> basePtr(new Base);
    TestEqual(basePtr->GetValue(), 0, "Should be equal");

    SharedPointer<Base> derivedPtr(new Derived(42));
    TestEqual(derivedPtr->GetValue(), 42, "Should be equal");

    SharedPointer<Base> copiedPtr = derivedPtr;
    SharedPointer<Base> assignedPtr(new Base);
    assignedPtr = derivedPtr;
    TestEqual(copiedPtr->GetValue(), 42, "Should be equal");
    TestEqual(assignedPtr->GetValue(), 42, "Should be equal");

    SharedPointer<Derived> polymorphicPtr(new Derived(84));
    SharedPointer<Base> baseFromDerived = polymorphicPtr;
    TestEqual(baseFromDerived->GetValue(), 84, "Should be equal");
}
/*****************************************************************************/
