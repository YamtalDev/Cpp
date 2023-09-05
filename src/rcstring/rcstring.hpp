#ifndef ILRD_RD141_RCSTRING_HPP
#define ILRD_RD141_RCSTRING_HPP

#include <new>   //std::bad_alloc
#include <iosfwd>//ostream istream

namespace ilrd_rd141
{

typedef struct Data Data_t;

class RCString 
{

public:

    RCString(const char *str = "") throw(std::bad_alloc); // Implicit type conversion
    RCString(const RCString &other_);
    RCString& operator=(const RCString &other_);
    ~RCString();
    
    char operator[](size_t index) const;
    char& operator[](size_t index) throw(std::bad_alloc);

    size_t Length() const;
    const char *ToCstr() const;
    bool IsShared() const;

private:

    Data_t *SetData(const char *str);
    void ReleaseData(void);
    void DetachData(void);
    void DeAllocate(void);
    Data_t *m_data;
    size_t size;
};

std::ostream &operator<<(std::ostream &stream, const RCString &str);
std::istream &operator>>(std::istream &stream, RCString &str);
bool operator==(const RCString &lhs ,const RCString &rhs);
bool operator!=(const RCString &lhs ,const RCString &rhs);
bool operator>(const RCString &lhs ,const RCString &rhs);
bool operator<(const RCString &lhs ,const RCString &rhs);

} // ilrd_ol141

#endif /* ILRD_RD141_RCSTRING_HPP*/
