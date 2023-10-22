#pragma once

#include<array>

namespace CppERP
{
    class PostalCode
    {
        std::array<char, 2> city_;
        std::array<char, 3> local_;
    public:
        PostalCode() = default;
        explicit PostalCode(const std::array<char, 2>& city,
                            const std::array<char, 3>& local)
        : city_{city}, local_{local} {}

        PostalCode& city(const std::array<char, 2>& city)
        {
            city_ = city;
            return *this;
        }
        std::array<char, 2> city() const { return city_; }
        PostalCode& local(const std::array<char, 3>& local)
        {
            local_ = local;
            return *this;
        }
        std::array<char, 3> local() const { return local_; }
        std::string to_string() const
        {
            return std::string{city_[0]} + city_[1] + "-" + local_[0] + local_[1] + local_[2];
        }
    };
}