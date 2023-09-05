#if __cplusplus < 201103L // Check if C++11 or below
#define noexcept throw()
#endif

#ifndef ILRD_RD141_OOD_HPP
#define ILRD_RD141_OOD_HPP

#include <iosfwd>
#include <vector>
#include <string>
#include <boost/core/noncopyable.hpp>

namespace ilrd_rd141
{
class IEntry : private boost::noncopyable
{
public:
    IEntry(const std::string& filename);
    virtual IEntry *clone() const = 0;
    virtual ~IEntry() noexcept;
    virtual void Print() const noexcept = 0;
protected:
    const std::string& GetFilename() const noexcept;
private:
    std::string m_filename;
};

class File: public IEntry
{
public:
    File(const std::string& filename);
    virtual ~File() noexcept;
    virtual void Print() const noexcept;
    virtual File* clone() const;
};

class Dir: public IEntry
{
public:
    Dir(const std::string& filename);
    virtual ~Dir() noexcept; 
    virtual void Print() const noexcept;
    virtual Dir* clone() const;
    void AddIEntry(const IEntry& entry);
    void RemoveIEntry(std::string entry) noexcept;

private:
    std::vector<const IEntry*> m_content;
};

}

#endif /* ILRD_RD141_OOD_HPP */