#include <cassert>       /* assert          */
#include <iostream>      /* std::cout       */
#include <cstring>       /* std::strcmp     */
#include "bit_array.hpp" /* Internal API    */
/*****************************************************************************/
using namespace ilrd_rd141;
void TestSet(void);
void TestFlip(void);
void TestCount(void);
void TestShift(void);
void TestGetBit(void);
void TestToString(void);
void TestBitWiseOr(void);
void TestBitWiseAnd(void);
void TestBitWiseXor(void);
void TestBitEquality(void);
void TestDefaultBehavior(void);
/*****************************************************************************/
int main(void)
{
    TestSet();
    TestFlip();
    TestCount();
    TestGetBit();
    TestToString();
    TestBitWiseOr();
    TestBitWiseAnd();
    TestBitWiseXor();
    TestBitEquality();
    TestDefaultBehavior();
    std::cout << "All tests passed" << std::endl;
    return (0);
}
/*****************************************************************************/
void TestDefaultBehavior(void)
{
    BitArray<300> bits;
    for(std::size_t i = 0; i < 300; ++i)
    {
        assert(bits[i] == false);
    }

    bits[1] = true;
    BitArray<300> bits1(bits);
    assert(bits1 == bits);
    bits[2] = true;
    assert(bits1 != bits);
    BitArray<300> bits2 = bits;
    assert(bits2 == bits);
    bits[3] = true;
    assert(bits2 != bits);
    const std::size_t var = 8;
    BitArray<var> b;
    (void)var;
    (void)b;
}
/*****************************************************************************/
void TestFlip(void)
{
    BitArray<400> bits1;
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits1[i] == false);
    }

    bits1.flip_all();
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits1[i] == true);
    }

    for(std::size_t i = 0; i < 400; ++i)
    {
        bits1.flip(i);
    }

    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(!bits1[i]);
    }

    bits1 = ~bits1;
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits1[i]);
    }

    bits1.flip(31);
    assert(bits1.get_bit(31) == false);
}
/*****************************************************************************/
void TestSet(void)
{
    BitArray<400> bits1;
    bits1.set_all();
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits1[i]);
    }

    for(std::size_t i = 0; i < 400; ++i)
    {
        bits1.set(i, false);
    }

    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(!bits1[i]);
    }

    bits1.set(31, true);
    assert(bits1.get_bit(31) == true);
}
/*****************************************************************************/
void TestBitWiseAnd(void)
{
    BitArray<400> bits1;
    BitArray<400> bits2;
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits2[i] == false);
    }

    bits2.flip_all();
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits2[i] == true);
    }

    bits2 &= bits1;
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits2[i] == false);
    }

    bits1.flip_all();
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits1[i] == true);
    }

    assert(bits1 != bits2);
    for(std::size_t i = 0; i < 400; ++i)
    {
        if(i % 2)
        {
            bits2.flip(i);
        }
    }

    bits1 = bits1 & bits2;
    for(std::size_t i = 0; i < 400; ++i)
    {
        if(i % 2)
        {
            assert(bits1[i] == true);
            assert(bits2[i] == true);
        }
    }

    assert(bits1 == bits2);

    BitArray<4> bits3;
    BitArray<4> bits4;
    bits4.flip(0);

    assert(bits3 != bits4);
    bits4 = bits4 & bits3;
    assert(bits3 == bits4);
}
/*****************************************************************************/
void TestBitWiseOr(void)
{
    BitArray<400> bits1;
    BitArray<400> bits2;
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits2[i] == false);
        assert(bits1[i] == false);
    }

    bits2.flip_all();
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits2[i] == true);
    }

    bits1 |= bits2;
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits1[i] == true);
    }

    bits1.flip_all();
    for(std::size_t i = 0; i < 400; ++i)
    {
        assert(bits1[i] == false);
    }

    assert(bits1 != bits2);
    for(std::size_t i = 0; i < 400; ++i)
    {
        if(i % 2)
        {
            bits2.flip(i);
        }
    }

    bits1 = bits1 | bits2;
    for(std::size_t i = 0; i < 400; ++i)
    {
        if(i % 2)
        {
            assert(bits1[i] == false);
            assert(bits2[i] == false);
        }
        else
        {
            assert(bits1[i] == true);
            assert(bits2[i] == true);
        }
    }

    assert(bits1 == bits2);
}
/*****************************************************************************/
void TestToString(void)
{
    BitArray<8> bits;
    assert("00000000" == bits.to_string());
    bits[0] = true;
    assert("10000000" == bits.to_string());
    bits.flip_all();
    assert("01111111" == bits.to_string());
    bits[2] = false;
    assert("01011111" == bits.to_string());
    BitArray<15000> bits1;
    std::string str(15000, '1');
    std::string str1(15000, '0');
    assert(str1 == bits1.to_string());
    bits1.flip_all();
    assert(str == bits1.to_string());
}
/*****************************************************************************/
void TestBitWiseXor(void)
{
    BitArray<8> bits1;
    BitArray<8> bits2;
    for(std::size_t i = 0; i < 8; ++i)
    {
        assert(bits2[i] == false);
        assert(bits1[i] == false);
    }

    bits2.flip_all();
    for(std::size_t i = 0; i < 8; ++i)
    {
        assert(bits2[i] == true);
    }

    bits2 ^= bits1;
    for(std::size_t i = 0; i < 8; ++i)
    {
        assert(bits2[i] == true);
    }

    bits1 = bits1 ^ bits2;
    for(std::size_t i = 0; i < 8; ++i)
    {
        assert(bits1[i] == true);
    }

    assert(bits1 == bits2);
    for(std::size_t i = 0; i < 8; ++i)
    {
        if(i % 2)
        {
            bits2.flip(i);
        }
        else
        {
            bits1.flip(i);
        }
    }

    bits1 ^= bits2;
    for(std::size_t i = 0; i < 8; ++i)
    {
        assert(bits1[i] == true);
    }

    assert(bits1 != bits2);
}
/*****************************************************************************/
void TestCount(void)
{
    BitArray<8> bits1;
    BitArray<8> bits2;
    BitArray<800> bits3;

    bits2[3] = true;
    assert(bits1.count(false) == 8);
    assert(bits2.count(false) == 7);


    assert(bits1.count(true) == 0);
    bits1[3] = true;
    assert(bits1.count(true) == 1);
    assert(bits2.count(true) == 1);

    assert(bits3.count(false) == 800);
    bits3.flip_all();
    assert(bits3.count(true) == 800);
}
/*****************************************************************************/
void TestGetBit(void)
{
    BitArray<8> bits1;
    BitArray<8> bits2;
    bits2[3] = true;
    assert(bits2.get_bit(3));
    assert(bits1.get_bit(5) == bits2.get_bit(5));
    assert(bits2.get_bit(3) != bits2.get_bit(2));
}
/*****************************************************************************/
void TestBitEquality(void)
{
    BitArray<8> bits1;
    BitArray<8> bits2;
    assert(bits1 == bits2);
    assert(!(bits1 != bits2));
    bits2[3] = true;
    assert(!(bits1 == bits2));
    assert(bits1 != bits2);
    BitArray<100> bits3;
    BitArray<100> bits4;
    bits4[101] = true;
    assert(bits3 == bits4);
}
/*****************************************************************************/
