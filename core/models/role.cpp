#pragma once

#include<string>
#include<mutex>
#include "utils/macros.hpp"

namespace kient::CppERP::core
{
    class Role
    {
        mutable std::mutex mutex;
        API_PRIMARY_KEY API_UNIQUE std::string ID_;
        API_UNIQUE std::string full_name_;
        API_UNIQUE std::string description_;
    public:
        Role() = default;
        explicit Role(const std::string& mod,
                      const std::string& name,
                      const std::string& full_name,
                      const std::string& description)
        : ID_{mod + ":" + name},
          full_name_{full_name},
          description_{description} {}

        Role(const Role& other)
        {
            ID_ = other.ID_;
            full_name_ = other.full_name_;
            description_ = other.description_;
        }
        explicit Role(Role&&) = default;
        Role& operator=(const Role&) = default;

        API_FLUENT_PROPERTY(ID, std::string, Role)
        API_FLUENT_PROPERTY(full_name, std::string, Role)
        API_FLUENT_PROPERTY(description, std::string, Role)
    };
}