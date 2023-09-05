/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Amitai.

    Date: 04.07.2023

******************************************************************************/
#include <cassert>    /* assert         */
#include <iostream>   /* cout, endl     */
#include <cstring>    /* strlen, strcmp */

#include "string.hpp" /* Internal API   */
/*****************************************************************************/
void StringOperatorsTest(void);
void BasicMethodsStringTest(void);
/*****************************************************************************/
using namespace ilrd_rd141;

int main(void)
{
    StringOperatorsTest();
    BasicMethodsStringTest();
    std::cout << "Passed." << std::endl;
    return (0);
}
/*****************************************************************************/
void BasicMethodsStringTest(void)
{
    String str;
    assert(0 == str.Length());
    assert(0 == strcmp("", str.Cstr()));

    String str1("Tal has created a string");
    assert(strlen("Tal has created a string") == str1.Length());
    assert(0 == strcmp("Tal has created a string", str1.Cstr()));

    String str2(str1);
    assert(strlen("Tal has created a string") == str2.Length());
    assert(0 == strcmp("Tal has created a string", str2.Cstr()));

    str = str2;
    assert(strlen("Tal has created a string") == str.Length());
    assert(0 == strcmp(str1.Cstr(), str.Cstr()));

    String str3("Habana");
    str1 = str3;
    assert(0 != strcmp(str1.Cstr(), str.Cstr()));
    assert(strlen("Habana") == str1.Length());

    String str4 = "Tal has created a string";
    assert(strlen("Tal has created a string") == str4.Length());
    assert(0 == strcmp("Tal has created a string", str4.Cstr()));

    String str5 = "";
    assert(0 == str5.Length());
    assert(0 == strcmp("", str5.Cstr()));

    String str6("");
    assert(0 == str6.Length());
    assert(0 == strcmp("", str6.Cstr()));
}

void StringOperatorsTest(void)
{
    String str1("abc");
    String str2("abc");
    assert(str1 == str2);
    assert(str2 == str1);
    assert("abc" == str2);
    assert(!(str1 == "abd"));
    assert(!("abd" == str1));

    String str3("abc");
    String str4("abk");
    assert(!(str3 == str4));
    assert(!(str4 == str3));
    assert(!("abc" == str4));
    assert(!(str3 == "abd"));
    assert(!("abd" == str3));

    String str5("abd");
    assert(str5 > str1);
    assert(str1 < str5);
    assert("aaa" < str5);
    assert(str1 < "mmm");
    assert("mmm" > str5);

// Remove comments to test input and output.

//    String input;
//    String output("Please enter a string: ");
//    std::cout << output << std::endl;
//    std::cin >> input;
//    std::cout << input << std::endl;
}
