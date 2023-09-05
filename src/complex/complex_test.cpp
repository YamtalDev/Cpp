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

    Reviewer: Yonatan.

    Date: 06.07.2023

******************************************************************************/
#include <ctime>    // clock
#include <iostream> // cout, endl
#include <cassert>  // assert
#include <cmath>    // fabs

#include "complex.hpp" /* Internal API */
/*****************************************************************************/
const double epsilon = 1e-5;
using namespace ilrd_rd141;
void BenchMarkTest(void);
void ComplexEqualOperatorTest(void);
void ComplexInputOperatorTest(void);
void ComplexOutputOperatorTest(void);
void ComplexAdditionOperatorTest(void);
void ComplexNotEqualOperatorTest(void);
void ComplexDivisionOperatorTest(void);
void ComplexBasicFunctionalityTest(void);
void ComplexSubtractionOperatorTest(void);
void ComplexMultiplicationOperatorTest(void);
void ComplexAssignmentAddingOperatorTest(void);
void ComplexAssignmentDivisionOperatorTest(void);
void ComplexAssignmentSubtractionOperatorTest(void);
void ComplexAssignmentMultiplicationOperatorTest(void);
/*****************************************************************************/
int main(void)
{
    ComplexEqualOperatorTest();
    ComplexInputOperatorTest();
    ComplexOutputOperatorTest();
    ComplexAdditionOperatorTest();
    ComplexNotEqualOperatorTest();
    ComplexDivisionOperatorTest();
    ComplexBasicFunctionalityTest();
    ComplexSubtractionOperatorTest();
    ComplexMultiplicationOperatorTest();
    ComplexAssignmentAddingOperatorTest();
    ComplexAssignmentDivisionOperatorTest();
    ComplexAssignmentSubtractionOperatorTest();
    ComplexAssignmentMultiplicationOperatorTest();

    BenchMarkTest();

    std::cout << "All test pass." << std::endl;
    return (0);
}
/*****************************************************************************/
void ComplexEqualOperatorTest(void)
{
    Complex complex1;
    Complex complex2;
    assert(complex1 == complex2);
    assert(complex2 == complex1);

    assert(0 == complex2);
    assert(0 == complex1);

    assert(complex2 == 0);
    assert(complex1 == 0);

    Complex complex3(1);
    Complex complex4(1);

    assert(complex3 == complex4);
    assert(complex4 == complex3);

    assert(1 == complex3);
    assert(1 == complex4);

    assert(complex4 == 1);
    assert(complex3 == 1);

    Complex complex5(1.2, 1.2);
    Complex complex6(1.2, 1.2);

    assert(complex5 == complex6);
    assert(complex6 == complex5);

    assert(Complex() == Complex());
}
/*****************************************************************************/
void ComplexOutputOperatorTest(void)
{
    Complex complex(-10, 5);
    Complex complex1(5, -20);
    std::cout << complex << std::endl;
    std::cout << complex1 << std::endl;
    std::cout << Complex() << std::endl;
    std::cout << Complex(1) << std::endl;
    std::cout << Complex(1, 1) << std::endl;
    std::cout << Complex(1, 1) + 1 << std::endl;
    std::cout << (complex /= Complex(1, 1)) << std::endl;
    std::cout << (complex *= Complex(1, 1)) << std::endl;
    std::cout << (complex += Complex(1, 1)) << std::endl;
    std::cout << (complex -= Complex(1, 1)) << std::endl;
    std::cout << Complex(1, 1) + Complex(1, 1) << std::endl;
    std::cout << Complex(1, 2) * Complex(1, 2) << std::endl;
    std::cout << Complex(1, 3) / Complex(1, -1) << std::endl;
    std::cout << Complex(1, 1) - Complex(1, 1) << std::endl;
    std::cout << (Complex(1, 1) == Complex(1, 1)) << std::endl;
    std::cout << (Complex(1, 1) != Complex(1, 1)) << std::endl;
}
/*****************************************************************************/
void ComplexInputOperatorTest(void)
{
    Complex complex;
    std::cin >> complex;
    std::cout << complex << std::endl;
}
/*****************************************************************************/
void ComplexAdditionOperatorTest(void)
{
    Complex result;
    Complex complex1(1, 2);
    Complex complex2(1, 2);
    Complex complexTset(2, 4);
    result = complex1 + complex2;

    assert(complexTset == result);

    Complex complex3(-1, -2);
    Complex complex4(-1, -2);
    Complex complexTset1(-2, -4);
    result = complex3 + complex4;

    assert(complexTset1 == result);

    Complex complex5(1, 1);
    Complex complexTset2(2, 1);
    result = complex5 + 1.0;

    assert(complexTset2 == result);

    Complex complex6(1, 1);
    Complex complexTset3(2, 2);
    result = complex6 + Complex(1, 1);

    assert(complexTset3 == result);
}
/*****************************************************************************/
void ComplexNotEqualOperatorTest(void)
{
    Complex complex1;
    Complex complex2(1, 1.001);
    assert(complex1 != complex2);
    assert(complex2 != complex1);

    assert(Complex(0, 0.001) != complex2);
    assert(Complex(0, 0.001) != complex1);

    Complex complex3;
    assert(1 != complex3);
    assert(Complex(0) != Complex(0, 2));
}
/*****************************************************************************/
void ComplexDivisionOperatorTest(void)
{
    Complex result;
    Complex complex1(1, 2);
    Complex complex2(1, 2);
    Complex complexTset(1);
    result = complex1 / complex2;

    assert(complexTset == result);

    Complex complex3(6, -2);
    Complex complex4(-1, 2);
    Complex complexTset1(-2, -2);
    result = complex3 /complex4;

    assert(complexTset1 == result);

    Complex complex5(1, 1);
    result = complex5 / Complex(1, 1);

    assert(1 == result);

    Complex complex6(1, 1);
    result = complex6 / 2;

    assert(Complex(0.5, 0.5) == result);
}
/*****************************************************************************/
void ComplexBasicFunctionalityTest(void)
{
    Complex complex;
    assert(std::fabs(complex.GetImaginary() - 0.0) < epsilon);
    assert((complex.GetReal() - 0.0) < epsilon);

    Complex complex1(5.5);
    assert((complex.GetImaginary() - 0.0) < epsilon);
    assert((complex.GetReal() - 5.5) < epsilon);

    Complex complex2(5.5, 5.5);
    assert((complex2.GetImaginary() - 5.5) < epsilon);
    assert((complex2.GetReal() - 5.5) < epsilon);

    Complex complex3(0.0, 0.0);
    assert((complex3.GetImaginary() - 0.0) < epsilon);
    assert((complex3.GetReal() - 0.0) < epsilon);

    Complex complex4(complex2);
    assert((complex4.GetImaginary() - complex2.GetImaginary()) < epsilon);
    assert((complex4.GetReal() - complex2.GetReal()) < epsilon);

    Complex complex5 = complex4;
    assert((complex5.GetImaginary() - complex4.GetImaginary()) < epsilon);
    assert((complex5.GetReal() - complex4.GetReal()) < epsilon);

    Complex complex6(0.0, 5.5);
    assert((complex6.GetImaginary() - 5.5) < epsilon);
    assert((complex6.GetReal() - 0.0) < epsilon);

    Complex complex7 = Complex(1.1, 1.1);
    assert((complex7.GetImaginary() - 1.1) < epsilon);
    assert((complex7.GetReal() - 1.1) < epsilon);

    Complex complex8 = Complex();

    assert(std::fabs(complex8.GetImaginary() - 0.0) < epsilon);
    assert((complex8.GetReal() - 0.0) < epsilon);

    complex8.SetImaginary(-1.1);
    complex8.SetReal(-1.1);

    assert((complex8.GetImaginary() + 1.1) < epsilon);
    assert((complex8.GetReal() + 1.1) < epsilon);
}
/*****************************************************************************/
void ComplexSubtractionOperatorTest(void)
{
    Complex result;
    Complex complex1(1, 2);
    Complex complex2(1, 2);
    Complex complexTset(0, 0);
    result = complex1 - complex2;

    assert(complexTset == result);

    Complex complex3(-1, 2);
    Complex complex4(-1, -2);
    Complex complexTset1(0, 4);
    result = complex3 - complex4;

    assert(complexTset1 == result);

    Complex complex5(1, 1);
    Complex complexTset2(0, 1);
    result = complex5 - 1.0;

    assert(complexTset2 == result);

    Complex complex6(1, 1);
    Complex complexTset3(0, 0);
    result = complex6 - Complex(1, 1);

    assert(complexTset3 == result);

    Complex complex7(-1, -2);
    Complex complex8(-1, -2);
    Complex complexTset4(0.0, 0.0);

    result = complex7 - complex8;

    assert(complexTset4 == result);

    Complex complex9(10, 5);
    Complex complex10(5, 20);
    Complex complexTset5(5, -15);
    result = complex9 - complex10;

    assert(complexTset5 == result);

    Complex complex11(10, 5);
    Complex complex12(5, 20);
    Complex complexTset6(5, -15);
    result = complex11 - complex12;

    assert(complexTset6 == result);
}
/*****************************************************************************/
void ComplexMultiplicationOperatorTest(void)
{
    Complex result;
    Complex complex1(1, 2);
    Complex complex2(1, 2);
    Complex complexTset(-3, 4);
    result = complex1 * complex2;

    assert(complexTset == result);

    Complex complex3(6, -2);
    Complex complex4(-1, 2);
    Complex complexTset1(-2, 14);
    result = complex3 * complex4;

    assert(complexTset1 == result);

    Complex complex5(1, 1);
    Complex complexTset2(0, 2);
    result = complex5 * Complex(1, 1);

    assert(complexTset2 == result);
}
/*****************************************************************************/
void ComplexAssignmentAddingOperatorTest(void)
{
    Complex complex1(1, 2);
    Complex complex2(1, 2);
    Complex complexTset(2, 4);
    complex1 += complex2;

    assert(complexTset == complex1);

    Complex complex3(-1, -2);
    Complex complex4(-1, -2);
    Complex complexTset1(-2, -4);
    complex3 += complex4;

    assert(complexTset1 == complex3);

    Complex complex5(1, 1);
    Complex complexTset2(2, 1);
    complex5 += 1.0;

    assert(complexTset2 == complex5);

    Complex complex6(1, 1);
    Complex complexTset3(2, 2);
    complex6 += Complex(1, 1);

    assert(complexTset3 == complex6);
}
/*****************************************************************************/
void ComplexAssignmentDivisionOperatorTest(void)
{
    Complex complex1(1, 2);
    Complex complex2(1, 2);
    Complex complexTset(1);
    complex1 /= complex2;

    assert(complexTset == complex1);

    Complex complex3(6, -2);
    Complex complex4(-1, 2);
    Complex complexTset1(-2, -2);
    complex3 /= complex4;

    assert(complexTset1 == complex3);

    Complex complex5(1, 1);
    complex5 /= Complex(1, 1);

    assert(1 == complex5);

    Complex complex6(1, 1);
    complex6 /= 2;

    assert(Complex(0.5, 0.5) == complex6);
}
/*****************************************************************************/
void ComplexAssignmentSubtractionOperatorTest(void)
{
    Complex complex1(1, 2);
    Complex complex2(1, 2);
    Complex complexTset(0, 0);
    complex1 -= complex2;

    assert(complexTset == complex1);

    Complex complex3(-1, 2);
    Complex complex4(-1, -2);
    Complex complexTset1(0, 4);
    complex3 -= complex4;

    assert(complexTset1 == complex3);

    Complex complex5(1, 1);
    Complex complexTset2(0, 1);
    complex5 -= 1.0;

    assert(complexTset2 == complex5);

    Complex complex6(1, 1);
    Complex complexTset3(0, 0);
    complex6 -= Complex(1, 1);

    assert(complexTset3 == complex6);

    Complex complex7(-1, -2);
    Complex complex8(-1, -2);
    Complex complexTset4(0.0, 0.0);

    complex7 -= complex8;

    assert(complexTset4 == complex7);

    Complex complex9(10, 5);
    Complex complex10(5, 20);
    Complex complexTset5(5, -15);
    complex9 -= complex10;

    assert(complexTset5 == complex9);

    Complex complex11(10, 5);
    Complex complex12(5, 20);
    Complex complexTset6(5, -15);
    complex11 -= complex12;

    assert(complexTset6 == complex11);
}
/*****************************************************************************/
void ComplexAssignmentMultiplicationOperatorTest(void)
{
    Complex complex1(1, 2);
    Complex complex2(1, 2);
    Complex complexTset(-3, 4);
    complex1 *= complex2;

    assert(complexTset == complex1);

    Complex complex3(6, -2);
    Complex complex4(-1, 2);
    Complex complexTset1(-2, 14);
    complex3 *= complex4;

    assert(complexTset1 == complex3);

    Complex complex5(1, 1);
    Complex complexTset2(0, 2);
    complex5 *= Complex(1, 1);

    assert(complexTset2 == complex5);
}
/*****************************************************************************/
void BenchMarkTest(void)
{
    Complex complex1;
    Complex complex2(1, 1);
    clock_t start = clock();
    for(size_t i = 0; i < 100000000; ++i)
    {
        complex1 = complex1 + complex2;
    }
    clock_t end = clock();
    double timeTaken = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC) * 1000;
    std::cout << "Time taken: " << timeTaken << " milliseconds" << std::endl;
}
/*****************************************************************************/
