=ifndef __ILRD_RD141_IMONITOR_HPP__
#define __ILRD_RD141_IMONITOR_HPP__

namespace ilrd_rd141
{
class IMonitor
{
public:
    virtual ~IMonitor() = default;
    virtual void RegisterRead(int fd) noexcept = 0;
    virtual bool Deregister(int fd) = 0;
    virtual int WaitForEvents() = 0;
    virtual bool IsReadable(int fd) = 0;
};

}

#endif /* __ILRD_RD141_IMONITOR_HPP__ */
