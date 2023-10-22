#pragma once

#include<string>
#include "postal-code.cpp"

namespace kient::CppERP::core::utils
{
    class Address
    {
        std::string country_;
        std::string region_;
        std::string city_;
        std::string street_;
        std::string building_;
        std::string apartment_;
        PostalCode postal_code_;
    public:
        explicit Address() = default;
        Address(const Address& other)
        {
            country_ = other.country_;
            region_ = other.region_;
            city_ = other.city_;
            street_ = other.street_;
            building_ = other.building_;
            apartment_ = other.apartment_;
            postal_code_ = other.postal_code_;
        }
        explicit Address(Address&&) = default;
        Address& operator=(const Address&) = default;
    };
}