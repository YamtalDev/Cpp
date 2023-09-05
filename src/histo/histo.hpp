#if __cplusplus <= 201103L // Check if C++11 or below
#define noexcept throw()
#endif

#ifndef __ILRD_RD141_HISTO_HPP__
#define __ILRD_RD141_HISTO_HPP__

#include <map>    // map
#include <string> // string
#include <vector> // vector, push_back

namespace ilrd_rd141
{

class Histo
{

public:

void In(void) noexcept;
void Out(void) noexcept;

private:

std::map<std::string, std::size_t> m_map;
std::vector<std::string> container;
std::string line;

};

}

#endif /* __ILRD_RD141_HISTO_H__ */
