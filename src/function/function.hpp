#ifndef __ILRD_RD141_FUNCTION_HPP__
#define __ILRD_RD141_FUNCTION_HPP__

#include <memory> // std::shared_ptr
namespace ilrd_rd141
{
template<typename>
class Function;

template<typename RET>
class Function<RET(void)>
{

public:
template<typename ARG>
explicit Function(RET (*fun)(ARG), ARG arg);

template<typename OBJ, typename ARG>
explicit Function(RET (OBJ::*fun)(ARG), OBJ *obj, ARG arg);

RET operator()() const;

private:

    class IFunction
    {
    public:
        virtual RET operator()() const = 0;
        virtual ~IFunction() = default;
    };

    template<typename ARG>
    class FreeFunction: public IFunction
    {
    public:
        FreeFunction(RET (*fun)(ARG), ARG arg);
        RET operator()() const;
    private:
        ARG m_arg;
        RET (*m_fun)(ARG);
    };

    template<typename OBJ, typename ARG>
    class ObjectFunction: public IFunction
    {
    public:
        ObjectFunction(RET (OBJ::*fun)(ARG), OBJ *obj, ARG arg);
        RET operator()() const;
    private:
        ARG m_arg;
        OBJ *m_obj;
        RET (OBJ::*m_fun)(ARG);
    };

std::shared_ptr<IFunction> m_fun;
};
/******************************************************************************
 * @brief Constructor for initializing the function object with a free function.
 * @tparam ARG The type of the argument passed to the free function.
 * @param fun A pointer to the free function to be stored.
 * @param arg The argument value to be passed when the stored function is called.
******************************************************************************/
template <typename RET>
template <typename ARG>
Function<RET(void)>::Function(RET (*fun)(ARG), ARG arg):
m_fun(std::make_shared<FreeFunction<ARG>>(fun, arg))
{
    // Empty
}
/******************************************************************************
 * @brief Constructor for initializing the function object with a member function.
 * @tparam OBJ The class type of the object containing the member function.
 * @tparam ARG The type of the argument passed to the member function.
 * @param fun A pointer to the member function to be stored.
 * @param obj A pointer to the object on which the member function will be called.
 * @param arg The argument value to be passed when the stored function is called.
******************************************************************************/
template <typename RET>
template <typename OBJ, typename ARG>
Function<RET(void)>::Function(RET (OBJ::*fun)(ARG), OBJ *obj, ARG arg):
m_fun(std::make_shared<ObjectFunction<OBJ, ARG>>(fun, obj, arg))
{
    // Empty
}
/******************************************************************************
 * @brief Call operator to invoke the stored function.
 * @return The result of calling the stored function.
******************************************************************************/
template <typename RET>
RET Function<RET(void)>::operator()() const
{
    return (*m_fun)();
}
/******************************************************************************
 * @brief Constructor for initializing the free function wrapper.
 * @param fun A pointer to the free function to be stored.
 * @param arg The argument value to be passed when the stored function is called.
******************************************************************************/
template <typename RET>
template <typename ARG>
Function<RET(void)>::FreeFunction<ARG>::FreeFunction(RET (*fun)(ARG), ARG arg):
m_arg(arg), m_fun(fun)
{
    // Empty
}
/******************************************************************************
 * @brief Call operator to invoke the stored free function.
 * @return The result of calling the stored free function.
******************************************************************************/
template <typename RET>
template <typename ARG>
RET Function<RET(void)>::FreeFunction<ARG>::operator()() const
{
    return (m_fun(m_arg));
}
/******************************************************************************
 * @brief Constructor for initializing the member function wrapper.
 * @tparam OBJ The class type of the object containing the member function.
 * @param fun A pointer to the member function to be stored.
 * @param obj A pointer to the object on which the member function will be called.
 * @param arg The argument value to be passed when the stored function is called.
******************************************************************************/
template <typename RET>
template <typename OBJ, typename ARG>
Function<RET(void)>::ObjectFunction<OBJ, ARG>::ObjectFunction(RET (OBJ::*fun)(ARG), OBJ *obj, ARG arg):
m_arg(arg), m_obj(obj), m_fun(fun)
{
    // Empty
}
/******************************************************************************
 * @brief Call operator to invoke the stored member function.
 * @return The result of calling the stored member function.
******************************************************************************/
template <typename RET>
template <typename OBJ, typename ARG>
RET Function<RET(void)>::ObjectFunction<OBJ, ARG>::operator()() const
{
    return ((m_obj->*m_fun)(m_arg));
}
/*****************************************************************************/
};

#endif /* __ILRD_RD141_FUNCTION_H__ */
