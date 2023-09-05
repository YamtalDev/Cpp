/******************************************************************************

    Writer: Tal Aharon

    Reviewer: First name and family name.

    Date: 03.09.2023

*******************************************************************************

                          Description:

  

******************************************************************************/
#include <iostream>     /* std::        */
#include "reactor.hpp"  /* Internal API */
using namespace ilrd_rd141;

// template<typename Target>
// class Select : public ReactorDispatcher<Target>
// {
// public:
//     Select(): m_max(-1)
//     {
//         FD_ZERO(&m_rset);
//     }

//     virtual ~Select() override
//     {
//         // Empty
//     }

//     virtual void RegisterRead(Target target) noexcept override
//     {
//         FD_SET(target, &m_rset);
//         m_max = std::max(m_max, target);
//     }

//     virtual bool Deregister(Target target) override
//     {
//         if(FD_ISSET(target, &m_rset))
//         {
//             FD_CLR(target, &m_rset);
//             if(target == m_max)
//             {
//                 m_max = -1;
//                 for(int fd = 0; fd < FD_SETSIZE; ++fd)
//                 {
//                     if(FD_ISSET(fd, &m_rset))
//                     {
//                         m_max = std::max(m_max, fd);
//                     }
//                 }
//             }

//             return (true);
//         }

//         return (false);
//     }

//     virtual int WaitForEvents(struct time_out timeout) override
//     {
//         struct timeval tv = {0};
//         tv.tv_sec = timeout.sec;
//         tv.tv_usec = timeout.u_sec;
//         return (select(m_max + 1, &m_rset, nullptr, nullptr, &tv));
//     }

//     virtual bool IsReadable(Target target) override
//     {
//         return (FD_ISSET(target, &m_rset));
//     }

// private:
//     fd_set m_rset;
//     int m_max;
// };

/*****************************************************************************/
int main(void)
{
    return (0);
}
/*****************************************************************************/
