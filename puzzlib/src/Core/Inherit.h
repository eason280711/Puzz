#pragma once

#include "Core/ref_ptr.h"
#include <utility>
namespace puzz
{

    // template <class ParentClass, class SubClass>
    // class Inherit : public ParentClass
    // {
    // public:
    //     virtual ref_ptr<ParentClass> Clone() override { return ref_ptr<ParentClass>(new SubClass(*static_cast<SubClass *>(this))); }
    // };

    /*
    使用CRTP設計模式實現的繼承模板，參考自：
    https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance/
    */

    ///////////////////////////////////////////////////////////////////////////////

    template <typename T>
    class abstract_method
    {
    };

    ///////////////////////////////////////////////////////////////////////////////

    template <typename T>
    class virtual_inherit_from : virtual public T
    {
        using T::T;
    };

    ///////////////////////////////////////////////////////////////////////////////

    template <typename Derived, typename... Bases>
    class Inherit : public Bases...
    {
    public:
        template <typename... Args>
        Inherit(Args &&...args) : Bases(std::forward<Args>(args)...)... {}

        virtual ~Inherit() = default;

        ref_ptr<Derived> clone() const
        {
            return ref_ptr<Derived>(static_cast<Derived *>(this->clone_impl()));
        }

    protected:
    private:
        virtual Inherit *clone_impl() const override
        {
            return new Derived(static_cast<const Derived &>(*this));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////

    template <typename Derived, typename... Bases>
    class Inherit<abstract_method<Derived>, Bases...> : public Bases...
    {
    public:
        template <typename... Args>
        Inherit(Args &&...args) : Bases(std::forward<Args>(args)...)... {}

        virtual ~Inherit() = default;

        ref_ptr<Derived> clone() const
        {
            return ref_ptr<Derived>(static_cast<Derived *>(this->clone_impl()));
        }

    protected:
    private:
        virtual Inherit *clone_impl() const = 0;
    };

    ///////////////////////////////////////////////////////////////////////////////

    template <typename Derived>
    class Inherit<Derived>
    {
    public:
        virtual ~Inherit() = default;

        ref_ptr<Derived> clone() const
        {
            return ref_ptr<Derived>(static_cast<Derived *>(this->clone_impl()));
        }

    private:
        virtual Inherit *clone_impl() const
        {
            return new Derived(static_cast<const Derived &>(*this));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////

    template <typename Derived>
    class Inherit<abstract_method<Derived>>
    {
    public:
        virtual ~Inherit() = default;

        ref_ptr<Derived> clone() const
        {
            return ref_ptr<Derived>(static_cast<Derived *>(this->clone_impl()));
        }

    private:
        virtual Inherit *clone_impl() const = 0;
    };

    ///////////////////////////////////////////////////////////////////////////////

}