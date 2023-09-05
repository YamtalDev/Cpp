/******************************************************************************

  Writer: Tal Aharon

  Reviewer: Matias.

  Date: 12.07.2023

*******************************************************************************

                                Description:

  The provided code implements an RCString class, which is a reference-counted 
  string with copy-on-write semantics. It allows efficient sharing and modification 
  of strings by maintaining a reference count and dynamically allocating memory 
  for the string data. The class provides essential functionality such as constructors, 
  destructor, assignment operator, length retrieval, checking for shared ownership, 
  accessing characters by index, conversion to C-style string, and comparison operators. 
  It optimizes copy behavior to minimize unnecessary memory allocations and deallocations. 
  The code is exception-safe and provides a simple interface for working with strings.

******************************************************************************/
#include <iostream>     // >>, <<
#include <cstring>      // strlen, strcpy, strcmp
 
#include "rcstring.hpp" // Internal API
/*****************************************************************************/
namespace ilrd_rd141
{

struct Data
{
    size_t counter;
    char *str;
};

RCString::RCString(const char *str) throw(std::bad_alloc) : m_data(SetData(str))
{}

RCString::RCString(const RCString &other_) : m_data(other_.m_data)
{
    ++(m_data->counter);
}

RCString& RCString::operator=(const RCString& other_)
{
    if(this != &other_)
    {
        ReleaseData();
        m_data = other_.m_data;
        ++(m_data->counter);
    }

    return (*this);
}

RCString::~RCString()
{
    ReleaseData();
}

size_t RCString::Length() const
{
    return (std::strlen(m_data->str));
}

bool RCString::IsShared() const
{
    return (m_data->counter > 1);
}

const char *RCString::ToCstr() const
{
    return (m_data->str);
}

Data_t *RCString::SetData(const char *str)
{
    std::size_t size = sizeof(Data_t) + std::strlen(str) + 1;

    try
    {
        m_data = reinterpret_cast<Data_t *>(new char[size]);
        m_data->str = reinterpret_cast<char *>(m_data + 1);
        std::strcpy(m_data->str, str);
        m_data->counter = 1;
    }
    catch(std::bad_alloc& alloc_err)
    {
        DeAllocate();
        throw(alloc_err);
    }

    return m_data;
}

void RCString::DeAllocate(void)
{
    delete[] (m_data);
    m_data = NULL;
}

void RCString::DetachData(void)
{
    if(IsShared() && --(m_data->counter))
        SetData(this->ToCstr());
}

void RCString::ReleaseData(void)
{
    if(0 == --(m_data->counter))
        DeAllocate();
}

char& RCString::operator[](size_t index) throw(std::bad_alloc)
{
    DetachData();
    return (m_data->str[index]);
}

char RCString::operator[](size_t index) const
{
    return (m_data->str[index]);
}

std::ostream &operator<<(std::ostream &stream, const RCString &str)
{
    return (stream << str.ToCstr());
}

std::istream &operator>>(std::istream &stream, RCString &str)
{
    const size_t bufSiz = 1024;
    char buffer[bufSiz] = {0};
    stream.getline(buffer, bufSiz);
    str = buffer;
    return (stream);
}

bool operator>(const RCString &str1 ,const RCString &str2)
{
    return (0 < std::strcmp(str1.ToCstr(), str2.ToCstr()));
}

bool operator<(const RCString &str1 ,const RCString &str2)
{
    return (0 > std::strcmp(str1.ToCstr(), str2.ToCstr()));
}

bool operator==(const RCString &str1 ,const RCString &str2)
{
    return (0 == std::strcmp(str1.ToCstr(), str2.ToCstr()));
}

bool operator!=(const RCString &lhs ,const RCString &rhs)
{
    return !(lhs == rhs);
}
}
