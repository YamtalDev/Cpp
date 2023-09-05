#include <iostream>    // cout, cin, getline, std::size_t

#include "histo.hpp"   // Internal API
/*****************************************************************************/
namespace ilrd_rd141
{
void Histo::In(void) noexcept
{
    while(std::getline(std::cin, line), "." != line)
    {
        container.push_back(line);
        ++m_map[line];
    }
}

void Histo::Out(void) noexcept
{
    for(std::size_t i = 0; i < container.size(); ++i)
    {
        const std::string& item = container[i];
        if(m_map[item] > 1)
        {
            std::cout << m_map[item] << " x " << item << std::endl;
            m_map[item] = 0;
        }
        else if(m_map[item] == 1)
        {
            std::cout << item << std::endl;
        }
    }
}
}