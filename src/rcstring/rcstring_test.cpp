/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Matias.

    Date: 12.07.2023

******************************************************************************/
#include <cassert>       // assert
#include <iostream>      // cout, endl
#include <cstring>       // strlen, strcmp

#include "rcstring.hpp"  // Internal API
using namespace ilrd_rd141;
/*****************************************************************************/
void RCStringTest(void);
void RCStringAccessTest(void);
void RCStringInstancesTest(void);
void RCStringOperatorTest(void);
/*****************************************************************************/
int main(void)
{
    // Remove this comments and check valgrined for 3 total 
    // allocations 

    //RCString S("HI");
    //RCString S1(S);
    //RCString S2(S);
    //RCString S3(S);
    //RCString S4(S);
    //RCString S5(S);
    //RCString S6(S);
    //RCString S7(S);
    //RCString S8(S);
    //RCString S9(S);
    //RCString S10(S);
    //RCString S11(S);
    //RCString S12(S);
    //RCString S13(S);
    //RCString S14 = S;
    //RCString S15 = S;
    //RCString S16 = S;
    //RCString S17 = S;
    //RCString S18 = S;
    //RCString S19 = S;
    //RCString S20 = S;
    //RCString S21 = S;
    //RCString S22 = S;
    //RCString S23 = S;
    //RCString S24 = S;
    //RCString S25 = S;
    //RCString S26 = S;

    RCStringOperatorTest();
    RCStringTest();
    RCStringInstancesTest();
    RCStringAccessTest();
    std::cout << "Passed." << std::endl;
    return (0);
}
/*****************************************************************************/
void RCStringTest(void)
{
    RCString str;
    assert(0 == str.Length());
    RCString str1("Tal has created a RCString");
    assert(strlen("Tal has created a RCString") == str1.Length());
    RCString str2(str1);
    assert(strlen("Tal has created a RCString") == str2.Length());
    str = str2;
    assert(strlen("Tal has created a RCString") == str.Length());
    assert(0 == strcmp(str1.ToCstr(), str.ToCstr()));
    RCString str3("Habana");
    str1 = str3;
    assert(0 != strcmp(str1.ToCstr(), str.ToCstr()));
}
/*****************************************************************************/
void RCStringOperatorTest(void)
{
    RCString str1("abc");
    RCString str2("abc");
    assert(str1 == str2);
    assert(str2 == str1);
    assert("abc" == str2);
    assert(!(str1 == "abd"));
    assert(!("abd" == str1));
    RCString str3("abd");
    assert(!(str1 == str3));
    assert(str3 > str1);
    assert(str1 < str3);
    assert("aaa" < str3);
    assert(str1 < "mmm");
    assert("mmm" > str3);
    assert("mmm" > "aaa");

    // Remove comment if you want to test input output.
    //RCString input;
    //RCString output("Please enter a RCString: ");
    //std::cout << output << std::endl;
    //std::cin >> input;
    //std::cout << input << std::endl;
}
/*****************************************************************************/
void RCStringInstancesTest(void)
{
    RCString s1("hello");
    assert(false == s1.IsShared());

    RCString s2(s1);
    assert(true == s1.IsShared());

    RCString s3(s1);
    assert(true == s1.IsShared());

    RCString s4(s1);
    assert(true == s1.IsShared());

    RCString s5("world");

    assert(true == s4.IsShared());
    s4 = s5;
    assert(true == s1.IsShared());

    assert(true == s3.IsShared());
    s3 = s5;
    assert(true == s1.IsShared());

    assert(true == s2.IsShared());
    s2 = s5;
    assert(false == s1.IsShared());
}
/*****************************************************************************/
void RCStringAccessTest(void)
{
    char buffer[6] = "Hello";
    RCString s("Hello");
    for(size_t i = 0; i < s.Length(); ++i)
    {
        assert(buffer[i] ==  s[i]);
    }

    char buffer1[8] = "bbbbbbb";
    RCString s1("aaaaaaa");
    for(size_t i = 0; i < s.Length(); ++i)
    {
        s1[i] = 'b';
        assert(buffer1[i] ==  s1[i]);
    }

    for(size_t i = 0; i < s.Length(); ++i)
    {
        s1[i] = 'k';
    }

    for(size_t i = 0; i < s.Length(); ++i)
    {
        assert('k' ==  s1[i]);
    }

    RCString s2("aa");
    assert(false == s2.IsShared());
    RCString s3(s2);
    assert(true == s2.IsShared());
    assert(true == s3.IsShared());
    RCString s4("bb");
    s4 = s2;
    assert(true == s2.IsShared());
    assert(true == s3.IsShared());
    assert(true == s4.IsShared());
    s2[0] = 'k';
    assert(false == s2.IsShared());
    assert(true == s3.IsShared());
    assert(true == s4.IsShared());
    assert('k' == s2[0] && 'a' == s2[1]);
    assert('a' == s3[0] && 'a' == s3[1]);
    assert('a' == s4[0] && 'a' == s4[1]);
    s3[0] = 'l';
    assert(false == s2.IsShared());
    assert(false == s3.IsShared());
    assert(false == s4.IsShared());
    assert('l' == s3[0] && 'a' == s3[1]);
    assert('a' == s4[0] && 'a' == s4[1]);
    RCString s5 = s4;
    assert(true == s4.IsShared());
    assert(true == s5.IsShared());
}
/*****************************************************************************/
