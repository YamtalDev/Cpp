#ifndef __ILRD_RD141__FUNCTORS__
#define __ILRD_RD141__FUNCTORS__

#include <string>     // std::string

namespace ilrd_rd141
{
const std::size_t WORDSIZE = sizeof(std::size_t) * __CHAR_BIT__;
static const std::size_t lut_size = (1 << __CHAR_BIT__); 
/******************************* Table class *********************************/
class Table
{
public:
    Table() noexcept;
    u_char operator[](u_char byte) const noexcept;
private:
    u_char m_table[lut_size];
};

Table::Table() noexcept
{
    for(std::size_t i = 0; i < lut_size; ++i)
    {
        *(m_table + i) = (i & 1) + *(m_table + i / 2);
    }
}

u_char Table::operator[](u_char byte) const noexcept
{
    return (m_table[byte]);
}

static const Table g_table;

/*************************** Accumulator functor *****************************/
class Accumulator
{
public:
    Accumulator();
    void operator()(const u_char word) noexcept;
    std::size_t sum(void) const;
private:
    std::size_t m_sum;
};

Accumulator::Accumulator(): m_sum(0)
{
    // Empty
}

void Accumulator::operator()(const u_char byte) noexcept
{
    m_sum += g_table[byte];
}

std::size_t Accumulator::sum(void) const
{
    return (m_sum);
}
/**************************** Flipper functor ********************************/
class Flipper
{
public:
    std::size_t operator()(std::size_t word) noexcept;
};

std::size_t Flipper::operator()(std::size_t word) noexcept
{
    return (~word);
}
/**************************** BitwiseAnd functor *****************************/
class BitwiseAnd
{
public:
    std::size_t operator()(std::size_t lhs, std::size_t rhs) const noexcept;
};

std::size_t BitwiseAnd::operator()(std::size_t lhs, std::size_t rhs) const noexcept
{
    return (lhs & rhs);
}
/**************************** BitwiseXor functor *****************************/
class BitwiseXor
{
public:
    std::size_t operator()(std::size_t lhs, std::size_t rhs) const noexcept;
};

std::size_t BitwiseXor::operator()(std::size_t lhs, std::size_t rhs) const noexcept
{
    return (lhs ^ rhs);
}
/**************************** BitwiseOr functor ******************************/
class BitwiseOr
{
public:
    std::size_t operator()(std::size_t lhs, std::size_t rhs) const noexcept;
};

std::size_t BitwiseOr::operator()(std::size_t lhs, std::size_t rhs) const noexcept
{
    return (lhs | rhs);
}
/************************ BitwiseRighttShift functor ***************************/
class BitwiseRightShift
{
public:
    explicit BitwiseRightShift(std::size_t shiftAmount);
    std::size_t operator()(std::size_t val) const noexcept;
private:
    std::size_t m_shiftAmount;
};

BitwiseRightShift::BitwiseRightShift(std::size_t shiftAmount):\
m_shiftAmount(shiftAmount % WORDSIZE)
{
    // Empty
}

std::size_t BitwiseRightShift::operator()(std::size_t val) const noexcept
{
    return (val << m_shiftAmount);
}
/************************ BitwiseRightShift functor **************************/

class BitwiseLeftShift
{
public:
    explicit BitwiseLeftShift(std::size_t shiftAmount);
    std::size_t operator()(std::size_t val) const noexcept;
private:
    std::size_t m_shiftAmount;
};

BitwiseLeftShift::BitwiseLeftShift(std::size_t shiftAmount):\
m_shiftAmount(shiftAmount % WORDSIZE)
{
    // Empty
}

std::size_t BitwiseLeftShift::operator()(std::size_t val) const noexcept
{
    return (val >> m_shiftAmount);
}
/*************************** BinaryToStrConverter functor *****************************/
class BinaryToStrConverter
{
public:
    BinaryToStrConverter(std::size_t num);
    void operator()(char &result);
private:
    std::size_t m_number;
};

BinaryToStrConverter::BinaryToStrConverter(std::size_t num) : m_number(num)
{
    // Empty
}

void BinaryToStrConverter::operator()(char &result)
{
    result = (m_number & 1) + '0';
    m_number >>= 1;
}

class BinaryToStr
{
public:
    void operator()(std::size_t number);
    std::string GetStr(void);
private:
    std::string m_str;
};

void BinaryToStr::operator()(std::size_t number)
{
    char buffer[WORDSIZE + 1] = {'\0'};
    std::for_each(buffer, buffer + WORDSIZE, BinaryToStrConverter(number));
    m_str += buffer;
}

std::string BinaryToStr::GetStr(void)
{
    return (m_str);
}

};
/*****************************************************************************/

#endif // __ILRD_RD141__FUNCTORS__