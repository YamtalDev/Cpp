/******************************************************************************

  Writer: Tal Aharon

  Reviewer: Yonatan.

  Date: 06.07.2023

*******************************************************************************

                          Description:

  This code defines a Complex class with basic operations and overloaded 
  arithmetic operators. It provides implementations for the member functions 
  and operators. The class represents a complex number with real and imaginary parts. 
  The operators +=, -=, *=, and /= modify the complex number in place. 
  The << and >> operators are overloaded for output and input stream respectively. 
  Finally, the ==, !=, +, -, *, and / operators are defined as non-member functions 
  for arithmetic operations on complex numbers.


******************************************************************************/
#include <cmath>       // pow, fabs, strtod
#include <iostream>    // >>, << operators
#include "complex.hpp" // Internal API 
/*****************************************************************************/

namespace ilrd_rd141
{
    Complex::Complex(double real, double imaginary): \
    m_real(real), m_imaginary(imaginary){}

    void Complex::SetReal(double num)
    {
        m_real = num;
    }

    double Complex::GetReal() const
    {
        return (m_real);
    }

    void Complex::SetImaginary(double num)
    {
        m_imaginary = num;
    }

    double Complex::GetImaginary() const
    {
        return (m_imaginary);
    }

    Complex& Complex::operator+=(const Complex &num)
    {
        m_imaginary += num.GetImaginary();
        m_real += num.GetReal();
        return (*this);
    }

    Complex& Complex::operator-=(const Complex &num)
    {
        m_imaginary -= num.GetImaginary();
        m_real -= num.GetReal();
        return (*this);
    }

    Complex& Complex::operator*=(const Complex &num)
    {
        double real = m_real;
        m_real = (m_real * num.m_real) - (m_imaginary * num.m_imaginary);
        m_imaginary = (real * num.m_imaginary) + (m_imaginary * num.m_real);
        
        return (*this);
    }

    Complex& Complex::operator/=(const Complex &num)
    {
        double real = m_real;
        double denominator = pow(num.m_real, 2) + pow(num.m_imaginary, 2);
    
        m_real = ((m_real * num.m_real) + \
                 (m_imaginary * num.m_imaginary)) / denominator;
    
        m_imaginary = ((m_imaginary * num.m_real) - \
                      (real * num.m_imaginary)) / denominator;
    
        return (*this);
    }

    std::ostream &operator<<(std::ostream &stream, const Complex &num)
    {
        stream << "(" << num.GetReal() << ") + i(" << num.GetImaginary() << ")";
        return (stream);
    }

    std::istream &operator>>(std::istream &stream, Complex &num)
    {
        double real, imaginary;
        stream >> real >> imaginary;
        num = Complex(real, imaginary);
        return (stream);
    }

    bool operator==(const Complex &lhs, const Complex &rhs)
    {
        bool reCmp = std::fabs(lhs.GetReal() - rhs.GetReal()) < 1e-5;
        bool imCmp = std::fabs(lhs.GetImaginary() - rhs.GetImaginary()) < 1e-5;
        return (imCmp && reCmp);
    }

    bool operator!=(const Complex &lhs, const Complex &rhs)
    {
        return (!(lhs == rhs));
    }

    const Complex operator+(const Complex &lhs, const Complex &rhs)
    {
        return (Complex(lhs) += rhs);
    }

    const Complex operator-(const Complex &lhs, const Complex &rhs)
    {
        return (Complex(lhs) -= rhs);
    }

    const Complex operator*(const Complex &lhs, const Complex &rhs)
    {
        return (Complex(lhs) *= rhs);
    }

    const Complex operator/(const Complex &lhs, const Complex &rhs)
    {
        return (Complex(lhs) /= rhs);
    }
}
