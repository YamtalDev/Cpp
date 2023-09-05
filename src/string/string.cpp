/******************************************************************************
         ▄███████████▄        ░  ░░ ░ ░  ░           ▄▄▄███▄    ░ ░  ░░░░ ░░
   ░░   ░██████████████   ░   ░ ░░░ ░ ░░░░░ ░ ░   ▄███████████░ ░ ░░░░░░░░░░░░░
░ ░ ░░░ ████████████████ ░  ░░░░░░░░▒░░░░░░░░  ░ ██████████████  ░░░▒░▒░▒░▒░░░
 ░░▒▒░ ░████▀▀▀███▀█████░ ░░░░░░░░░░▒▒░▒░░░░░░░ ████████████████░  ░░░▒▒▒▒▒░ ░
 ░▒▒▒░ ▄▄████▀▀▀▀▀▀███▄▄▄░░░░░░░░▒▒░▒▒▒░░░░░░░ ░██████▀███▀█████  ░░▒░▒▒▒░▒░  ░
░▒▒▒▄███▀ ▄▄▄▄   ▄▄▄▄ ▀████▄░░▒▒░▒▒▒▒░▒░▒▒░░░ ░▄█████▀▀▀▀▀▀█████▄░ ░░▒▒▒▒▒░ ░
▒░▒▒░▀▀█▓█████▀▀▀█████▒▓█▀▀░░░▒░▒▒▒▒▒▒▒▒░░░░▄███▀ ▄▄▄▄  ░▄▄▄▄ ▀████▄░░▒▒▒▒▒░▒░
░▒▒▒▒░░█▓▒▀▀▀ ░  ░▀▀▀░▒▓█░ ░▒░▒▒▒▒▒▒▒▒▒▒░▒░░ ▀▀█▓█████▀▀▀█████▒▓█▀▀░░▒▒▒▒▒░░░
░░▒▒░░▒ █▓▒░ ░▄█▄  ░░▒▓█  ░░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░░ █▓▒▀▀▀  ░░ ▀▀▀░▒▓█░ ░░░▒▒▒▒▒▒  ░
▒▒▒▒▒▒░░█▓▒░░   ░ ░ ░▒▓█░░░░░▒░▒░▒▒░░▒▒▒░▒▒░░ ░░█▓▒░ ░ █▄ ░ ░▒▓█░░░░▒▒▒▒▒▒▒░░
 ░▒▒▒░░ ░█▓▒░ ░▀█  ░▒▓█  ░░░░░░░░▒░░▒▒░▒▒░░░░ ░ ░█▓▒░ ░  ░ ░▒▓█░░ ░░░▒▒▒▒░▒░░░
░  ░░ ▒░ ░███▓▒░░▒▓███  ░  ░░░░░░░░░░░░░░░░░░░░ ░ █▓▒░░▄▄░░▒▓█   ░░░▒░▒▒░░░░░ ░
 ▄▄▄▄███▀▀█▓▒▀▀▀▀▀▀▒▓█████▄▄▄▄░ ░░░ ░░░ ░░░░░ ░  ░███▓▒░░▒▓███░ ░░░░░░░░░░░░ ░
██████▓▒░  ▀▄░  ░░▄▄▀░▒▓██████████▄▄ ░ ░ ▄▄▄▄███▀▀█▓▒▀▀▀▀▀▀▒▓█████▄▄▄▄ ░  ░ ░
███████▓▒░ ░ ▀███▀ ░░▒▓███████████████████████▓▒░ ░▀▄░ ░░ ▄▄▀░▒▓██████████▄▄░
████████▓▒░  ░ █ ░ ░▒▓█████████████████████████▓▒░ ░ ▀███▀ ░░▒▓██████████████
█████████▓▒░░ ▐█▌ ░▒▓███████████████████████████▓▒░  ░ █  ░░▒▓████████████████
*******************************************************************************

  Writer: Tal Aharon

  Reviewer: Amitai.

  Date: 04.07.2023

*******************************************************************************

                          Description:

  The implementation defines a C++ String class with dynamic memory allocation.
  It includes constructors, assignment overloads, and comparison operators. 
  C-string functions are utilized for string manipulation. The operator>> 
  function reads input until newline, preserving spaces.

******************************************************************************/
#include <cstring>    /* strlen, strcpy, strcmp, memcpy  */
#include "string.hpp" /* Internal API                    */
/*****************************************************************************/
namespace ilrd_rd141
{
    String::String(const char *str) throw(std::bad_alloc) : length(0), \
    isDynamic(false)
    {
        StrSet(str);
    }

    String::String(const String& other_): length(other_.length), \
    isDynamic(other_.isDynamic)
    {
        StrSet(other_.Cstr());
    }

    String& String::operator=(const String& other_)
    {
        if(this != &other_)
        {
            StrDestroy();
            StrSet(other_.Cstr());
        }

        return (*this);
    }

    String::~String()
    {
        StrDestroy();
    }

    std::size_t String::Length() const
    {
        return (length);
    }

    const char *String::Cstr() const
    {
        return (isDynamic ? data.dynamicBuffer : data.ssoBuffer);
    }

    void String::StrSet(const char *str)
    {
        length = std::strlen(str);
        if(length < ssoLength)
        {
            std::memcpy(data.ssoBuffer, str, length + 1);
            isDynamic = false;
            return;
        }

        data.dynamicBuffer = new char[length + 1];
        std::memcpy(data.dynamicBuffer, str, length + 1);
        isDynamic = true;
    }

    void String::StrDestroy(void)
    {
        if(isDynamic)
        {
            delete[] (data.dynamicBuffer);
        }

        data.dynamicBuffer = NULL;
        isDynamic = false;
        length = 0;
    }

    std::ostream &operator<<(std::ostream &stream, const String &str)
    {
        return (stream << str.Cstr());
    }

    std::istream &operator>>(std::istream &stream, String &str)
    {
        const std::size_t bufferSize = 4096;
        char buffer[bufferSize] = {0};
        stream.getline(buffer, bufferSize);
        str = buffer;
        return (stream);
    }

    bool operator>(const String &str1 ,const String &str2)
    {
        return (0 < strcmp(str1.Cstr(), str2.Cstr()));
    }

    bool operator<(const String &str1 ,const String &str2)
    {
        return (0 > strcmp(str1.Cstr(), str2.Cstr()));
    }

    bool operator==(const String &str1 ,const String &str2)
    {
        return (0 == strcmp(str1.Cstr(), str2.Cstr()));
    }
}
/*****************************************************************************/