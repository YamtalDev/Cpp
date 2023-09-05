/******************************************************************************

  Writer: Tal Aharon

  Reviewer: Yotam.

  Date: 02.08.2023

******************************************************************************/
#include <iostream>      /* cout         */
#include <algorithm>     /* for_each     */
#include "composite.hpp" /* Internal API */
/*****************************************************************************/
namespace ilrd_rd141
{

static void PrintDir(const IEntry *entry);

IEntry::IEntry(const std::string& filename) : m_filename(filename)
{
    // Empty
}

IEntry::~IEntry() noexcept
{
    // Empty
}

const std::string& IEntry::GetFilename() const noexcept
{
    return (m_filename);
}

File::File(const std::string& filename): IEntry(filename)
{
    // Empty
}

File::~File() noexcept
{
    // Empty
}

void File::Print() const noexcept
{
    std::cout << GetFilename() << std::endl;
}

File* File::clone() const
{
    return (new File(GetFilename()));
}

Dir::Dir(const std::string& filename): IEntry(filename)
{
    // Empty
}

Dir::~Dir() noexcept
{
    // Empty
}

void Dir::Print() const noexcept
{
    std::cout << GetFilename() << std::endl;
    std::for_each(m_content.begin(), m_content.end(), PrintDir);
}

Dir* Dir::clone() const
{
    Dir *newDir = new Dir(GetFilename());
    newDir->m_content = this->m_content;
    return (newDir);
}

void Dir::AddIEntry(const IEntry& entry)
{
    m_content.push_back(&entry);
}

void Dir::RemoveIEntry(std::string entry) noexcept
{
    std::vector<const IEntry *>::iterator it = m_content.begin();
    for(; it != m_content.end(); ++it)
    {
        if(reinterpret_cast<const Dir*>(*it)->GetFilename() == entry)
        {
            m_content.erase(it);
            return;
        }
    }
}

static void PrintDir(const IEntry *entry)
{
    entry->Print();
}

}