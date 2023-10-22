#pragma once

namespace CppERP
{
    class EMail
    {
        std::string user_;
        std::string domain_;
    public:
        explicit EMail(const std::string& user,
                       const std::string& domain)
        : user_{user}, domain_{domain} {}

        EMail& user(const std::string& user)
        {
            user_ = user;
            return *this;
        }
        std::string user() const { return user_; }
        EMail& domain(const std::string& domain)
        {
            domain_ = domain;
            return *this;
        }
        std::string domain() const { return domain_; }
        std::string to_string() const
        {
            return user_ + "@" + domain_;
        }
    };
}