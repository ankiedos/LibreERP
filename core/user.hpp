#pragma once

#include<string>

#include "utils/address.hpp"
#include "utils/e-mail.hpp"
#include "utils/macros.hpp"


namespace CppERP
{
    enum class Gender { Male, Female, Unknown };

    class User
    {
        static std::size_t next_ID_;
        API_DATA std::size_t ID;
        std::string name_;
        std::string second_name_;
        std::string surname_;
        Gender gender_;
        std::string password_hash_;
        Address address_;
        EMail e_mail_;
        std::string role_;
    public:
        static std::size_t next_ID()
        {
            return next_ID_++;
        }
        explicit User(const std::string& name,
                      const std::string& second_name,
                      const std::string& surname,
                      Gender gender,
                      const std::string& password_hash,
                      const Address& address,
                      const EMail& e_mail,
                      const std::string& role)
        : ID{User::next_ID()},
          name_{name},
          second_name_{second_name},
          surname_{surname},
          gender_{gender},
          password_hash_{password_hash},
          address_{address},
          e_mail_{e_mail},
          role_{role} {}

        API_FLUENT_CONST_PROPERTY(ID, std::size_t)
        API_FLUENT_PROPERTY(name, std::string, User)
        API_FLUENT_PROPERTY(second_name, std::string, User)
        API_FLUENT_PROPERTY(surname, std::string, User)
        API_FLUENT_PROPERTY(gender, Gender, User)
        API_FLUENT_PROPERTY(password_hash, std::string, User)
        API_FLUENT_PROPERTY(address, Address, User)
        API_FLUENT_PROPERTY(e_mail, EMail, User)
        API_FLUENT_PROPERTY(role, std::string, User)
    };
    std::size_t User::next_ID_ = 1;
}