#pragma once

#include<vector>
#include<mutex>


namespace kient::CppERP::core::utils
{
    template<typename T, typename Allocator = std::allocator<T>>
    class ThreadedVector : public std::vector<T, Allocator>
    {
        mutable std::mutex mutex;
    public:
        ThreadedVector& push_back(const T& t)
        {
            std::lock_guard<std::mutex> lock{mutex};
            push_back(t);
            return *this;
        }
        ThreadedVector& pop_back()
        {
            std::lock_guard<std::mutex> lock{mutex};
            pop_back();
            return *this;
        }
        T& operator [](std::size_t idx)
        {
            std::lock_guard<std::mutex> lock{mutex};
            return operator [](idx);
        }
        T& at(std::size_t idx)
        {
            std::lock_guard<std::mutex> lock{mutex};
            return at(idx);
        }
        const T& operator [](std::size_t idx) const
        {
            std::lock_guard<std::mutex> lock{mutex};
            return operator [](idx);
        }
        const T& at(std::size_t idx) const
        {
            std::lock_guard<std::mutex> lock{mutex};
            return at(idx);
        }
    };
}