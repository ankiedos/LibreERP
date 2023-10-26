#pragma once

#include<string>

#include "utils/address.cpp"
#include "utils/e-mail.cpp"
#include "utils/macros.hpp"


namespace kient::CppERP::core
{
    enum class Gender { Male, Female, Unknown };
    std::size_t gender_id(Gender gender)
    {
        switch(gender)
        {
        case Gender::Male: return 0;
        case Gender::Female: return 1;
        case Gender::Unknown: return 2;
        default: return 3; // unreachable
        }
    }

    class User
    {
        static std::size_t next_ID_;
        API_DATA std::size_t ID_;
        std::string name_;
        std::string second_name_;
        std::string surname_;
        Gender gender_;
        std::string password_hash_;
        std::size_t address_ID_;
        std::size_t email_ID_;
        std::string role_;
    public:
        static std::size_t next_ID()
        {
            return next_ID_++;
        }
        User() = default;
        explicit User(const std::string& name,
                      const std::string& second_name,
                      const std::string& surname,
                      Gender gender,
                      const std::string& password_hash,
                      std::size_t address,
                      std::size_t email,
                      const std::string& role)
        : ID_{User::next_ID()},
          name_{name},
          second_name_{second_name},
          surname_{surname},
          gender_{gender},
          password_hash_{password_hash},
          address_ID_{address},
          email_ID_{email},
          role_{role} {}

        explicit User(std::size_t ID,
                      const std::string& name,
                      const std::string& second_name,
                      const std::string& surname,
                      Gender gender,
                      const std::string& password_hash,
                      std::size_t address,
                      std::size_t email,
                      const std::string& role)
        : ID_{ID},
          name_{name},
          second_name_{second_name},
          surname_{surname},
          gender_{gender},
          password_hash_{password_hash},
          address_ID_{address},
          email_ID_{email},
          role_{role} {}

        API_FLUENT_PROPERTY(ID, std::size_t, User)
        API_FLUENT_PROPERTY(name, std::string, User)
        API_FLUENT_PROPERTY(second_name, std::string, User)
        API_FLUENT_PROPERTY(surname, std::string, User)
        API_FLUENT_PROPERTY(gender, Gender, User)
        API_FLUENT_PROPERTY(password_hash, std::string, User)
        API_FLUENT_PROPERTY(address_ID, std::size_t, User)
        API_FLUENT_PROPERTY(email_ID, std::size_t, User)
        API_FLUENT_PROPERTY(role, std::string, User)
    };
    std::size_t User::next_ID_ = 1;
}