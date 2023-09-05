#if __cplusplus < 201103L // Check if C++11 or below
#define noexcept throw()
#endif

#ifndef ILRD_RD141_SCOPE_LOCK_HPP
#define ILRD_RD141_SCOPE_LOCK_HPP

#include <boost/noncopyable.hpp>

namespace ilrd_rd141
{

template <typename T>
class ScopeLock : private boost::noncopyable 
{
public:
    explicit ScopeLock(T &lockable): m_lockable(lockable) { lockable.lock();}
    ~ScopeLock() noexcept { m_lockable.unlock();}
private:
    T &m_lockable;
};

} // ilrd_ol141

#endif /* ILRD_RD141_SCOPE_LOCK_HPP */