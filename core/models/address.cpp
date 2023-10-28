#pragma once

#include<string>
#include<mutex>
#include "utils/macros.hpp"
#include "utils/postal-code.cpp"

namespace kient::CppERP::core
{
    class Address
    {
        mutable std::mutex mutex;
        static std::size_t next_ID_;
        API_PRIMARY_KEY API_UNIQUE std::size_t ID_;
        std::string country_;
        std::string region_;
        std::string city_;
        std::string street_;
        std::string building_;
        std::string apartment_;
        utils::PostalCode postal_code_;
    public:
        static std::size_t next_ID()
        {
            return next_ID_++;
        }
        Address() = default;
        explicit Address(const std::string& country,
                      const std::string& region,
                      const std::string& city,
                      const std::string& street,
                      const std::string& building,
                      const std::string& apartment,
                      const utils::PostalCode& postal_code)
        : ID_{Address::next_ID()},
          country_{country},
          region_{region},
          city_{city},
          street_{street},
          building_{building},
          apartment_{apartment},
          postal_code_{postal_code} {}

        explicit Address(std::size_t ID,
                      const std::string& country,
                      const std::string& region,
                      const std::string& city,
                      const std::string& street,
                      const std::string& building,
                      const std::string& apartment,
                      const utils::PostalCode& postal_code)
        : ID_{ID},
          country_{country},
          region_{region},
          city_{city},
          street_{street},
          building_{building},
          apartment_{apartment},
          postal_code_{postal_code} {}

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

        API_FLUENT_PROPERTY(ID, std::size_t, Address)
        API_FLUENT_PROPERTY(country, std::string, Address)
        API_FLUENT_PROPERTY(region, std::string, Address)
        API_FLUENT_PROPERTY(city, std::string, Address)
        API_FLUENT_PROPERTY(street, std::string, Address)
        API_FLUENT_PROPERTY(building, std::string, Address)
        API_FLUENT_PROPERTY(apartment, std::string, Address)
        API_FLUENT_PROPERTY(postal_code, utils::PostalCode, Address)
    };
    std::size_t Address::next_ID_ = 1;
}