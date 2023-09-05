#ifndef ILRD_RD141_COMPLEX_HPP
#define ILRD_RD141_COMPLEX_HPP

#include <iosfwd> //ostream istream

namespace ilrd_rd141
{
class Complex
{
public:
    Complex(double real = 0, double imaginary = 0); // Implicit type conversion

    Complex& operator+=(const Complex &num);
    Complex& operator-=(const Complex &num);
    Complex& operator*=(const Complex &num);
    Complex& operator/=(const Complex &num);

    void SetReal(double num) ;
    void SetImaginary(double num) ;
    double GetReal() const;
    double GetImaginary() const;


private:

    double m_real;
    double m_imaginary;

};

std::ostream &operator<<(std::ostream &stream, const Complex &num);
std::istream &operator>>(std::istream &stream, Complex &num);
bool operator==(const Complex &lhs, const Complex &rhs);
bool operator!=(const Complex &lhs, const Complex &rhs);

const Complex operator+(const Complex &lhs, const Complex &rhs);
const Complex operator-(const Complex &lhs, const Complex &rhs);
const Complex operator*(const Complex &lhs, const Complex &rhs);
const Complex operator/(const Complex &lhs, const Complex &rhs);

} // ilrd_ol141

#endif /* ILRD_RD141_SHARED_HPP */
