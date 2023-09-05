#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <cstddef>  // NULL ,size_t
#include <iostream> // ostream, istream 

namespace ilrd_rd141
{

const std::size_t ssoLength = 16;

class String
{
public:

    String(const char *str = "") throw(std::bad_alloc); // Implicit type conversion
    String(const String& other_);
    String& operator=(const String& other_);
    ~String();

    std::size_t Length() const;
    const char *Cstr() const;

private:

    union
    {
        char ssoBuffer[ssoLength];
        char* dynamicBuffer;
    } data;

    std::size_t length;
    bool isDynamic;
    void StrDestroy(void);
    void StrSet(const char *str);
};

std::ostream &operator<<(std::ostream &stream, const String &str);
std::istream &operator>>(std::istream &stream, String &str);
bool operator==(const String &str1 ,const String &str2);
bool operator>(const String &str1 ,const String &str2);
bool operator<(const String &str1 ,const String &str2);

} // ilrd_ol141

#endif /* __STRING_HPP__ */
