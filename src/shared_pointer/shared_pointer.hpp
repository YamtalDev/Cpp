/******************************************************************************
         ▄███████████▄        ░  ░░ ░ ░  ░           ▄▄▄███▄    ░ ░  ░░░░ ░░
   ░░   ░██████████████   ░   ░ ░░░ ░ ░░░░░ ░ ░   ▄███████████░ ░ ░░░░░░░░░░░░░
░ ░ ░░░ ████████████████ ░  ░░░░░░░░▒░░░░░░░░  ░ ██████████████  ░░░▒░▒░▒░▒░░░
 ░░▒▒░ ░████▀▀▀███▀█████░ ░░░░░░░░░░▒▒░▒░░░░░░░ ████████████████░  ░░░▒▒▒▒▒░ ░
 ░▒▒▒░ ▄▄████▀▀▀▀▀▀███▄▄▄░░░░░░░░▒▒░▒▒▒░░░░░░░ ░██████▀███▀█████  ░░▒░▒▒▒░▒░  ░
░▒▒▒▄███▀ ▄▄▄▄   ▄▄▄▄ ▀████▄░░▒▒░▒▒▒▒░▒░▒▒░░░ ░▄█████▀▀▀▀▀▀█████▄░ ░░▒▒▒▒▒░ ░
▒░▒▒░▀▀█▓█████▀▀▀█████▒▓█▀▀░░░▒░▒▒▒▒▒▒▒▒░░░░▄███▀ ▄▄▄▄  ░▄▄▄▄ ▀████▄░░▒▒▒▒▒░▒░
░▒▒▒▒░░█▓▒▀▀▀ ░  ░▀▀▀░▒▓█░ ░▒░▒▒▒▒▒▒▒▒▒▒░▒░░ ▀▀█▓█████▀▀▀█████▒▓█▀▀░░▒▒▒▒▒░░░
░░▒▒░░▒ █▓▒░ ░▄█▄  ░░▒▓█  ░░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░░ █▓▒▀▀▀  ░░ ▀▀▀░▒▓█░ ░░░▒▒▒▒▒▒  ░
▒▒▒▒▒▒░░█▓▒░░   ░ ░ ░▒▓█░░░░░▒░▒░▒▒░░▒▒▒░▒▒░░ ░░█▓▒░ ░ █▄ ░ ░▒▓█░░░░▒▒▒▒▒▒▒░░
 ░▒▒▒░░ ░█▓▒░ ░▀█  ░▒▓█  ░░░░░░░░▒░░▒▒░▒▒░░░░ ░ ░█▓▒░ ░  ░ ░▒▓█░░ ░░░▒▒▒▒░▒░░░
░  ░░ ▒░ ░███▓▒░░▒▓███  ░  ░░░░░░░░░░░░░░░░░░░░ ░ █▓▒░░▄▄░░▒▓█   ░░░▒░▒▒░░░░░ ░
 ▄▄▄▄███▀▀█▓▒▀▀▀▀▀▀▒▓█████▄▄▄▄░ ░░░ ░░░ ░░░░░ ░  ░███▓▒░░▒▓███░ ░░░░░░░░░░░░ ░
██████▓▒░  ▀▄░  ░░▄▄▀░▒▓██████████▄▄ ░ ░ ▄▄▄▄███▀▀█▓▒▀▀▀▀▀▀▒▓█████▄▄▄▄ ░  ░ ░
███████▓▒░ ░ ▀███▀ ░░▒▓███████████████████████▓▒░ ░▀▄░ ░░ ▄▄▀░▒▓██████████▄▄░
████████▓▒░  ░ █ ░ ░▒▓█████████████████████████▓▒░ ░ ▀███▀ ░░▒▓██████████████
█████████▓▒░░ ▐█▌ ░▒▓███████████████████████████▓▒░  ░ █  ░░▒▓████████████████
*******************************************************************************

    Writer: Tal Aharon

    Reviewer: Ravit Yehudi.

    Date: 17.08.2023

*******************************************************************************

                          Description:

  The code defines a `SharedPointer` class template implementing shared ownership 
  for dynamically allocated objects. It manages reference counts to ensure proper 
  deallocation. The class supports copy operations, overloads pointer operators, 
  and includes a swap function for efficient ownership exchange.

******************************************************************************/
#include <cstddef>

#ifndef ILRD_RD141_SHARED_POINTER_HPP
#define ILRD_RD141_SHARED_POINTER_HPP

namespace ilrd_rd141
{

template <typename T>

class SharedPointer
{

public:

    explicit SharedPointer(T *pointer = nullptr);
    SharedPointer(const SharedPointer<T> &other) noexcept;
    SharedPointer<T> &operator=(const SharedPointer<T> &other) noexcept;
    ~SharedPointer() noexcept;

    T &operator*() const;
    T *operator->() const;
    T *GetPointer() const noexcept;

    template <typename U>
    SharedPointer(const SharedPointer<U> &other) noexcept;
    template <typename U>
    SharedPointer<T> &operator=(const SharedPointer<U> &other) noexcept;

private:

    template <typename U>
    friend class SharedPointer;

    T *m_pointer;
    std::size_t *m_counter;

    bool IsShared(void);
    void DecCounter(void);
    void IncCounter(void);
    void Deallocate(void);
    void DeleteResources(void);
    std::size_t *SetCounter(void);
    void Swap(SharedPointer<T> &);
    void CopyNSwap(const SharedPointer<T> &other);

};

template <typename T>
SharedPointer<T>::SharedPointer(T *pointer): \
m_pointer(pointer), m_counter(SetCounter())
{
    // Empty
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T> &other) noexcept :\
m_pointer(other.m_pointer), m_counter(other.m_counter)
{
    IncCounter();
}

template <typename T>
SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer<T> &other) noexcept
{
    CopyNSwap(other);
    return (*this);
}

template <typename T>
SharedPointer<T>::~SharedPointer() noexcept
{
    Deallocate();
}

template <typename T>
T &SharedPointer<T>::operator*() const
{
    return (*m_pointer);
}

template <typename T>
T *SharedPointer<T>::operator->() const
{
    return (m_pointer);
}

template <typename T>
T *SharedPointer<T>::GetPointer() const noexcept
{
    return (m_pointer);
}

template <typename T>
template <typename U>
SharedPointer<T>::SharedPointer(const SharedPointer<U> &other) noexcept :\
m_pointer(other.m_pointer), m_counter(other.m_counter)
{
    IncCounter();
}

template <typename T>
template <typename U>
SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer<U> &other) noexcept
{
    CopyNSwap(other);
    return (*this);
}

template <typename T>
void SharedPointer<T>::Swap(SharedPointer<T> &cpy)
{
    std::size_t *tmp_counter = m_counter;
    m_counter = cpy.m_counter;
    cpy.m_counter = tmp_counter;

    T *tmp_pointer = m_pointer;
    m_pointer = cpy.m_pointer;
    cpy.m_pointer = tmp_pointer;
}

template <typename T>
void SharedPointer<T>::CopyNSwap(const SharedPointer<T> &other)
{
    SharedPointer<T> cpy(other);
    Swap(cpy);
}

template <typename T>
std::size_t *SharedPointer<T>::SetCounter(void)
{
    try
    {
        m_counter = new std::size_t(1);
    }
    catch(const std::bad_alloc& b)
    {
        DeleteResources();
        throw(b);
    }
    
    return (m_counter);
}

template <typename T>
bool SharedPointer<T>::IsShared(void)
{
    return (0 != *m_counter);
}

template <typename T>
void SharedPointer<T>::DecCounter(void)
{
    --(*m_counter);
}

template <typename T>
void SharedPointer<T>::IncCounter(void)
{
    ++(*m_counter);
}

template <typename T>
void SharedPointer<T>::Deallocate(void)
{
    DecCounter();
    if(!IsShared())
    {
        DeleteResources();
    }
}

template <typename T>
void SharedPointer<T>::DeleteResources(void)
{
    delete (m_pointer);
    m_pointer = nullptr;
    delete (m_counter);
    m_counter = nullptr;
}

} // ilrd_rd141
#endif /* ILRD_RD141_SHARED_POINTER_HPP*/