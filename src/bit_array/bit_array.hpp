/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Art Ozerski.

    Date: 20.08.2023

*******************************************************************************

                          Description:

  C++ code for a class BitArray within the ilrd_rd141 namespace, The class 
  allows manipulation of fixed-size arrays of bits. The class supports a variety 
  of bitwise operations, such as AND, OR, XOR, left and right shifts, and provides 
  methods for flipping individual bits, counting bits with a specific value, and 
  converting the bit array to a string. The code also includes an inner BitProxy 
  class that enables direct bit-level access and modification within the BitArray. 
  The implementation employs utility classes and functions for efficient bitwise 
  operations and conversions.

******************************************************************************/
#ifndef __ILRD_RD141_BIT_ARRAY_HPP__
#define __ILRD_RD141_BIT_ARRAY_HPP__

// std::size_t
#include <cstddef>
// std::out_of_range
#include <stdexcept> 
// std::for_each, std::transform, std::fill, std::equal
#include <algorithm>

/*
   Internal API: Accumulator, 
   BitwiseRightShift, BitwiseLeftShift, 
   BitwiseOr, BitwiseXor, BitwiseAnd, Flipper, 
   Table, BinaryToStr, BinaryToStrConverter 
*/

#include "bit_array_utils.hpp"
namespace ilrd_rd141
{
template<std::size_t N>
class BitArray
{

const static std::size_t totalWordChucks = (N + (WORDSIZE - 1)) / WORDSIZE;
const static std::size_t unused_bits = (totalWordChucks * WORDSIZE) - N;
private:
    class BitProxy;
public:

    explicit BitArray() noexcept;
    //BitArray(const BitArray &rhs) noexcept; // Generated
    //BitArray &operator=(const BitArray &rhs) noexcept; // Generated
    //~BitArray() noexcept; // Generated

    std::string to_string() const;
    bool get_bit(std::size_t pos) const;
    std::size_t count(bool val) const noexcept;

    void flip(std::size_t pos);
    void flip_all() noexcept;

    void set_all(bool val = true) noexcept;
    void set(std::size_t pos, bool val = true);

    BitArray operator~() const noexcept;
    BitArray operator&(const BitArray &rhs) noexcept;
    BitArray operator^(const BitArray &rhs) noexcept;
    BitArray operator|(const BitArray &rhs) noexcept;
    BitArray operator>>(std::size_t rhs) noexcept;
    BitArray operator<<(std::size_t rhs) noexcept;

    BitArray &operator&=(const BitArray &rhs) noexcept;
    BitArray &operator^=(const BitArray &rhs) noexcept;
    BitArray &operator|=(const BitArray &rhs) noexcept;
    BitArray &operator>>=(std::size_t rhs) noexcept;
    BitArray &operator<<=(std::size_t rhs) noexcept;

    bool operator!=(const BitArray &rhs) const noexcept;
    bool operator==(const BitArray &rhs) const noexcept;

    bool operator[](std::size_t pos) const noexcept;
    BitArray::BitProxy operator[](const std::size_t pos) noexcept;

private:

    class BitProxy
    {
        public:
            BitProxy(std::size_t *bitarray, std::size_t pos) noexcept;
            //BitProxy(const BitProxy &rhs) noexcept; // generated
            //~BitProxy() noexcept; // generated
            BitProxy &operator=(const bool rhs) noexcept;
            BitProxy &operator=(const BitProxy &rhs) noexcept;
            operator bool() const noexcept;
            bool operator!() const noexcept;
        private:
            std::size_t &m_reference;
            std::size_t m_index;
    };

    void check(std::size_t pos) const;
    std::size_t offset(std::size_t val) const noexcept;
    std::size_t mask_unused_bits(const std::size_t *bits) const noexcept;
    std::size_t &get_word(std::size_t pos);
    std::size_t m_bits[totalWordChucks];
};
/************************** Class implementation *****************************/
template <std::size_t N>
BitArray<N>::BitArray() noexcept :m_bits{0}
{
    // Empty
}
/****************************** To String ************************************/
template <std::size_t N>
std::string BitArray<N>::to_string() const
{
    BinaryToStr binaryToStr;
    binaryToStr = std::for_each(m_bits, m_bits + totalWordChucks, binaryToStr);

    std::string result(binaryToStr.GetStr());
    result.erase(N, result.size() - N);

    return (result);
}
/******************************* Get Bit *************************************/
template <std::size_t N>
bool BitArray<N>::get_bit(std::size_t pos) const
{
    return (check(pos), this->operator[](pos));
}
/******************************** Count **************************************/
template <std::size_t N>
std::size_t BitArray<N>::count(bool val) const noexcept
{
    Accumulator accumulator;
    const u_char *start = reinterpret_cast<const u_char *>(m_bits);
    std::size_t range = (N / __CHAR_BIT__) + (0 != N % __CHAR_BIT__) - 1;

    accumulator = std::for_each(start, start + range, accumulator);
    accumulator(*(start + range) >> N % __CHAR_BIT__);
    std::size_t result = accumulator.sum();

    return ((val * result) | !(val) * (N - result));
}
/******************************** Flip ***************************************/
template <std::size_t N>
void BitArray<N>::flip(std::size_t pos)
{
    get_word(pos) ^= (1ul << pos);
}
/****************************** Flip All *************************************/
template <std::size_t N>
void BitArray<N>::flip_all() noexcept
{
    std::transform(m_bits, std::end(m_bits), m_bits, Flipper());
}
/******************************* Set All *************************************/
template <std::size_t N>
void BitArray<N>::set_all(bool val) noexcept
{
    std::fill(m_bits, std::end(m_bits), val * ~(0ul));
}
/********************************* Set ***************************************/
template <std::size_t N>
void BitArray<N>::set(std::size_t pos, bool val)
{
    check(pos), this->operator[](pos) = val;
}
/****************************** operator ~ ***********************************/
template <std::size_t N>
BitArray<N> BitArray<N>::operator~() const noexcept
{
    BitArray<N> bits(*this);
    bits.flip_all();
    return (bits);
}
/****************************** operator & ***********************************/
template <std::size_t N>
BitArray<N> BitArray<N>::operator&(const BitArray<N> &rhs) noexcept
{
    BitArray<N> bits(*this);
    bits &= rhs;
    return (bits);
}
/****************************** operator ^ ***********************************/
template <std::size_t N>
BitArray<N> BitArray<N>::operator^(const BitArray<N> &rhs) noexcept
{
    BitArray<N> bits(*this);
    bits ^= rhs;
    return (bits);
}
/****************************** operator | ***********************************/
template <std::size_t N>
BitArray<N> BitArray<N>::operator|(const BitArray<N> &rhs) noexcept
{
    BitArray<N> bits(*this);
    bits |= rhs;
    return (bits);
}
/****************************** operator >> **********************************/
template <std::size_t N>
BitArray<N> BitArray<N>::operator>>(std::size_t rhs) noexcept
{
    BitArray<N> bits(*this);
    bits >>= rhs;
    return (bits);
}
/****************************** operator << **********************************/
template <std::size_t N>
BitArray<N> BitArray<N>::operator<<(std::size_t rhs) noexcept
{
    BitArray<N> bits(*this);
    bits <<= rhs;
    return (bits);
}
/****************************** operator &= **********************************/
template <std::size_t N>
BitArray<N> &BitArray<N>::operator&=(const BitArray<N> &rhs) noexcept
{
    std::transform(m_bits, std::end(m_bits), rhs.m_bits, m_bits, BitwiseAnd());
    return (*this);
}
/****************************** operator ^= **********************************/
template <std::size_t N>
BitArray<N> &BitArray<N>::operator^=(const BitArray<N> &rhs) noexcept
{
    std::transform(m_bits, std::end(m_bits), rhs.m_bits, m_bits, BitwiseXor());
    return (*this);
}
/****************************** operator |= **********************************/
template <std::size_t N>
BitArray<N> &BitArray<N>::operator|=(const BitArray<N> &rhs) noexcept
{
    std::transform(m_bits, std::end(m_bits), rhs.m_bits, m_bits, BitwiseOr());
    return (*this);
}
/****************************** operator >>= *********************************/
template <std::size_t N>
BitArray<N> &BitArray<N>::operator>>=(std::size_t rhs) noexcept
{
    (void)rhs;
    return (*this);
}
/****************************** operator <<= *********************************/
template <std::size_t N>
BitArray<N> &BitArray<N>::operator<<=(std::size_t rhs) noexcept
{
    (void)rhs;
    return (*this);
}
/****************************** operator != **********************************/
template <std::size_t N>
bool BitArray<N>::operator!=(const BitArray<N> &rhs) const noexcept
{
    return (!(*this == rhs));
}
/****************************** operator == **********************************/
template <std::size_t N>
bool BitArray<N>::operator==(const BitArray<N> &rhs) const noexcept
{
    bool result = std::equal(m_bits, m_bits + (totalWordChucks - 1), rhs.m_bits);
    return (((mask_unused_bits(rhs.m_bits) == mask_unused_bits(m_bits)) & result));
}
/****************************** operator [] **********************************/
template <std::size_t N>
bool BitArray<N>::operator[](std::size_t pos) const noexcept
{
    return ((m_bits[offset(pos)] >> (pos % WORDSIZE)) & 1ul);
}
/****************************** operator [] **********************************/
template <std::size_t N>
typename BitArray<N>::BitProxy BitArray<N>::operator[](const std::size_t pos) noexcept
{
    return BitProxy(&m_bits[offset(pos)] , pos);
}
/******************** Check function to throw an exception *******************/
template <std::size_t N>
void BitArray<N>::check(std::size_t pos) const
{
    if(pos >= N)
    {
        throw (std::out_of_range("Index out of bounds"));
    }
}
/********************************* offset ************************************/
template <std::size_t N>
inline std::size_t BitArray<N>::offset(std::size_t val) const noexcept
{
    return (val / WORDSIZE);
}
/************************** Get an array element *****************************/
template <std::size_t N>
std::size_t &BitArray<N>::get_word(std::size_t pos)
{
    return (check(pos), m_bits[offset(pos)]);
}
/************************** Get an array element *****************************/
template <std::size_t N>
inline std::size_t BitArray<N>::mask_unused_bits(const std::size_t *bits) const noexcept
{
    return (bits[totalWordChucks - 1] << unused_bits);
}
/************************ BitProxy implementation ****************************/
template <std::size_t N>
BitArray<N>::BitProxy::BitProxy(std::size_t *bitarray, std::size_t pos) noexcept: \
m_reference(*bitarray), m_index(pos)
{
    // Empty
}
/****************************** operator = ***********************************/
template <std::size_t N> 
typename BitArray<N>::BitProxy &BitArray<N>::BitProxy::operator=(const bool rhs) noexcept
{
    m_reference = (m_reference & ~(1ul << m_index)) | (rhs * 1ul << m_index);
    return (*this);
}
/****************************** operator = ***********************************/
template <std::size_t N>
typename BitArray<N>::BitProxy &BitArray<N>::BitProxy::operator=(const BitArray<N>::BitProxy &rhs) noexcept
{
    return (*this = static_cast<bool>(rhs));
}
/***************************** operator bool *********************************/
template <std::size_t N>
BitArray<N>::BitProxy::operator bool() const noexcept
{
    return ((m_reference >> m_index) & 1ul);
}
/******************************* operator ! **********************************/
template <std::size_t N>
bool BitArray<N>::BitProxy::operator!() const noexcept
{
    return (!static_cast<bool>(*this));
}
/*****************************************************************************/
}; // ilrd_rd141
#endif // __ILRD_RD141_BIT_ARRAY_HPP__
