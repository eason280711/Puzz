#pragma once
#include <atomic>
#include <cstddef>
#include <cstdlib>

namespace puzz
{
    template <typename T>
    class __declspec(dllexport) ref_ptr
    {
    public:
        ref_ptr(T *ptr = nullptr) : m_ptr(ptr)
        {
            if (m_ptr)
            {
                m_ref_count = new std::atomic<std::size_t>(1);
            }
            else
            {
                m_ref_count = nullptr;
            }
        }

        ref_ptr(const ref_ptr<T> &other) : m_ptr(other.m_ptr), m_ref_count(other.m_ref_count)
        {
            if (m_ptr)
            {
                ++(*m_ref_count);
            }
        }

        ref_ptr(T *ptr, std::atomic<std::size_t> *ref_count) : m_ptr(ptr), m_ref_count(ref_count)
        {
            if (m_ptr)
            {
                ++(*m_ref_count);
            }
        }

        ref_ptr(ref_ptr<T> &&other) noexcept : m_ptr(other.m_ptr), m_ref_count(other.m_ref_count)
        {
            other.m_ptr = nullptr;
            other.m_ref_count = nullptr;
        }

        ref_ptr<T> &operator=(const ref_ptr<T> &other)
        {
            if (this != &other)
            {
                unref();
                m_ptr = other.m_ptr;
                m_ref_count = other.m_ref_count;
                if (m_ptr)
                {
                    ++(*m_ref_count);
                }
            }
            return *this;
        }

        ref_ptr<T> &operator=(ref_ptr<T> &&other) noexcept
        {
            if (this != &other)
            {
                unref();
                m_ptr = other.m_ptr;
                m_ref_count = other.m_ref_count;
                other.m_ptr = nullptr;
                other.m_ref_count = nullptr;
            }
            return *this;
        }

        std::atomic<std::size_t> *get_ref_count() const
        {
            return m_ref_count;
        }

        ~ref_ptr()
        {
            unref();
        }

        T &operator*() const { return *m_ptr; }
        T *operator->() const { return m_ptr; }
        T *get() const { return m_ptr; }

        std::size_t use_count() const
        {
            if (m_ref_count)
            {
                return m_ref_count->load();
            }
            else
            {
                return 0;
            }
        }

        operator bool() const { return m_ptr != nullptr; }

        bool operator==(const ref_ptr<T> &other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const ref_ptr<T> &other) const { return m_ptr != other.m_ptr; }
        bool operator<(const ref_ptr<T> &other) const { return m_ptr < other.m_ptr; }
        bool operator>(const ref_ptr<T> &other) const { return m_ptr > other.m_ptr; }
        bool operator<=(const ref_ptr<T> &other) const { return m_ptr <= other.m_ptr; }
        bool operator>=(const ref_ptr<T> &other) const { return m_ptr >= other.m_ptr; }

    private:
        void unref()
        {
            if (m_ptr)
            {
                if (--(*m_ref_count) == 0)
                {
                    delete m_ptr;
                    delete m_ref_count;
                }
                m_ptr = nullptr;
                m_ref_count = nullptr;
            }
        }

        T *m_ptr;
        std::atomic<std::size_t> *m_ref_count;
    };

    template <typename T, typename U>
    ref_ptr<U> static_pointer_cast(const ref_ptr<T> &r)
    {
        return ref_ptr<U>(static_cast<U *>(r.get()), r.get_ref_count());
    }

    template <typename T, typename U>
    ref_ptr<U> dynamic_pointer_cast(const ref_ptr<T> &r)
    {
        U *ptr = dynamic_cast<U *>(r.get());
        if (ptr != nullptr)
        {
            return ref_ptr<U>(ptr, r.get_ref_count());
        }
        else
        {
            return ref_ptr<U>();
        }
    }
}