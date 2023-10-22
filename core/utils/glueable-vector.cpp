#pragma once

#include<vector>


namespace kient::CppERP::core::utils
{
    template<typename T, typename Allocator = std::allocator<T>>
    class IGlueableVector : public std::vector<T, Allocator>
    {
    public:
        virtual ~IGlueableVector() = default;
        virtual T glue(const T& link) = 0;
    };
}