#ifndef __ILRD_RD141_REACTOR_HPP__
#define __ILRD_RD141_REACTOR_HPP__

#include <unordered_map> // std::unordered_map
#include "function.hpp"  // Function<void(void)> callback API

namespace ilrd_rd141
{

using Handler = ilrd_rd141::Function<void(void)>;

template<typename Monitor> 
class Reactor
{
public:
    Reactor(Monitor *monitor_sptr);
    Reactor(const Reactor &) = delete;
    Reactor &operator=(const Reactor &) = delete;
    ~Reactor();
    void RegisterReadEventHandler(int fd, const Handler &call_back);
    void DeregisterEventHandler(int fd) noexcept;
    void Run(void);

private:
    std::shared_ptr<Monitor> m_monitor;
    std::unordered_map<int, Handler> m_call_backs;
};

template <typename Monitor>
Reactor<Monitor>::Reactor(Monitor *monitor_sptr)
{

}

template <typename Monitor>
Reactor<Monitor>::~Reactor()
{

}

template <typename Monitor>
void Reactor<Monitor>::RegisterReadEventHandler(int fd, const Handler &call_back)
{
    
}

template <typename Monitor>
void Reactor<Monitor>::DeregisterEventHandler(int fd) noexcept
{

}

template <typename Monitor>
void Reactor<Monitor>::Run(void)
{

}

} // ilrd_rd141
#endif /* __ILRD_RD141_REACTOR_H__ */